#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"

#include "TFile.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TColor.h"
#include "TMath.h"
#include "TVectorT.h"
#include "TCanvas.h"
#include "lardataobj/RawData/RawDigit.h"
#include "TLegend.h"
#include <vector>
#include <set>
#include <map>
#include "Riostream.h"
#include "TString.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TROOT.h"

using namespace art;
using namespace std;


void phist(
	   std::string const& filename="decoded_data_evb01_run12007_19_20240319T154135.root", 
	   std::string const& inputtag="daq")
{
  TCanvas *mycanvas = (TCanvas*) new TCanvas("c1","c1",1200,600);
  gStyle->SetOptStat(0);
  size_t evcounter=0;

  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames(1, filename);

  TH1F *eastu = (TH1F*) new TH1F("eastu","EAST U 12007;ADC",4096,-0.5,4095.5);
  TH1F *eastv = (TH1F*) new TH1F("eastv","EAST V 12007;ADC",4096,-0.5,4095.5);
  TH1F *easty = (TH1F*) new TH1F("easty","EAST Y 12007;ADC",4096,-0.5,4095.5);

  TH1F *westublob = (TH1F*) new TH1F("westu","WEST U Blob 12007;ADC",4096,-0.5,4095.5);
  TH1F *westutypec = (TH1F*) new TH1F("westu","WEST U TypeC 12007;ADC",4096,-0.5,4095.5);
  TH1F *westv = (TH1F*) new TH1F("westv","WEST V 12007;ADC",4096,-0.5,4095.5);
  TH1F *westy = (TH1F*) new TH1F("westy","WEST Y 12007;ADC",4096,-0.5,4095.5);

  eastu->SetDirectory(0);
  eastv->SetDirectory(0);
  easty->SetDirectory(0);
  westublob->SetDirectory(0);
  westutypec->SetDirectory(0);
  westv->SetDirectory(0);
  westy->SetDirectory(0);

  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& evaux = ev.eventAuxiliary();
    int runno = evaux.run();
    int subrunno = evaux.subRun();
    int eventno = evaux.event();
    std::cout << "Run, subrun, event: " << runno << " " <<
           subrunno << " " << eventno << std::endl;
    if (eventno != 1116) continue;

    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
	const size_t nrawdigits = rawdigits.size();
	for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	  { 
	    size_t thigh = rawdigits[ichan].Samples()-1; // assume uncompressed
	    if (thigh < 1600)
	      {
		std::cout << "only " << thigh << "ticks.";
		return;
	      }
	    size_t ic = rawdigits[ichan].Channel();
	    if (rawdigits[ichan].GetSigma() > 1000) 
	      {
		std::cout << "skipping channel: " << ic << std::endl;
		continue;
	      }
	    TH1F *th = 0;
	    if (ic < 1984) th = eastu;
	    else if (ic < 3968) th = eastv;
	    else if (ic < 5632) th = easty;
	    else if (ic < 6382) th = westublob;
	    else if (ic < 7616) th = westutypec;
	    else if (ic < 9600) th = westv;
	    else th = westy;

	    for (size_t itick=1400;itick<=1500;++itick)
	      {
		//std::cout << "filling histo: " << ichan << " " << ic << " " << itick << std::endl;
		th->Fill(rawdigits[ichan].ADC(itick));
	      }
	  }
      }
    ++evcounter;
  }
  mycanvas->Divide(4,2);
  mycanvas->cd(1);
  gPad->SetLogy();
  eastu->Draw("hist");
  mycanvas->cd(2);
  gPad->SetLogy();
  eastv->Draw("hist");
  mycanvas->cd(3);
  gPad->SetLogy();
  easty->Draw("hist");
  mycanvas->cd(4);
  gPad->SetLogy();
  westublob->Draw("hist");
  mycanvas->cd(5);
  gPad->SetLogy();
  westutypec->Draw("hist");
  mycanvas->cd(6);
  gPad->SetLogy();
  westv->Draw("hist");
  mycanvas->cd(7);
  gPad->SetLogy();
  westy->Draw("hist");

  mycanvas->Print("run12007planehistos.png");

}
