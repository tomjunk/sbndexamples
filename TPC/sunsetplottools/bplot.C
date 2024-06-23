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

// burst plot for one sunset event -- makes ADC histograms and heatmaps of waveforms

void bplot()
{
  const std::string filename=
    "withBursts_decode_data_evb03_EventBuilder3_art3_run14039_8_20240621T162504_HVFilter-20240622T022004-a68056b6-c465-43b4-949c-bc3609329361.root";
  const std::string inputtag = "daq";
  TString runstr = "14039";

  size_t tickmin = 250;
  size_t tickmax = 350;


  TCanvas *mycanvas = (TCanvas*) new TCanvas("c1","c1",1200,1200);
  gStyle->SetOptStat(0);
  size_t evcounter=0;

  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames(1, filename);

  // ADC histograms

  TH1F *eastu = (TH1F*) new TH1F("eastu","EAST U "+runstr+";ADC",4096,-0.5,4095.5);
  TH1F *eastv = (TH1F*) new TH1F("eastv","EAST V "+runstr+";ADC",4096,-0.5,4095.5);
  TH1F *easty = (TH1F*) new TH1F("easty","EAST Y "+runstr+";ADC",4096,-0.5,4095.5);

  TH1F *westublob = (TH1F*) new TH1F("westu","WEST U Blob "+runstr+";ADC",4096,-0.5,4095.5);
  TH1F *westutypec = (TH1F*) new TH1F("westu","WEST U TypeC "+runstr+";ADC",4096,-0.5,4095.5);
  TH1F *westv = (TH1F*) new TH1F("westv","WEST V "+runstr+";ADC",4096,-0.5,4095.5);
  TH1F *westy = (TH1F*) new TH1F("westy","WEST Y "+runstr+";ADC",4096,-0.5,4095.5);

  eastu->SetDirectory(0);
  eastv->SetDirectory(0);
  easty->SetDirectory(0);
  westublob->SetDirectory(0);
  westutypec->SetDirectory(0);
  westv->SetDirectory(0);
  westy->SetDirectory(0);

  // heat plots for waveforms

  double xl = (double) tickmin - 0.5;
  double xh = (double) tickmax + 0.5;
  size_t nth = tickmax - tickmin + 1;
  size_t nbinsadc = 200;
  
  TH2F *hwfeastu = (TH2F*) new TH2F("hwfeastu","EAST U "+runstr+";tick;ADC",nth,xl,xh,nbinsadc,-0.5,4095.5);
  TH2F *hwfeastv = (TH2F*) new TH2F("hwfeastv","EAST V "+runstr+";tick;ADC",nth,xl,xh,nbinsadc,-0.5,4095.5);
  TH2F *hwfeasty = (TH2F*) new TH2F("hwfeasty","EAST Y "+runstr+";tick;ADC",nth,xl,xh,nbinsadc,-0.5,4095.5);

  TH2F *hwfwestublob = (TH2F*) new TH2F("hwfwestu","WEST U Blob "+runstr+";tick;ADC",nth,xl,xh,nbinsadc,-0.5,4095.5);
  TH2F *hwfwestutypec = (TH2F*) new TH2F("hwfwestu","WEST U TypeC "+runstr+";tick;ADC",nth,xl,xh,nbinsadc,-0.5,4095.5);
  TH2F *hwfwestv = (TH2F*) new TH2F("hwfwestv","WEST V "+runstr+";tick;ADC",nth,xl,xh,nbinsadc,-0.5,4095.5);
  TH2F *hwfwesty = (TH2F*) new TH2F("hwfwesty","WEST Y "+runstr+";tick;ADC",nth,xl,xh,nbinsadc,-0.5,4095.5);

  eastu->SetDirectory(0);
  eastv->SetDirectory(0);
  easty->SetDirectory(0);
  westublob->SetDirectory(0);
  westutypec->SetDirectory(0);
  westv->SetDirectory(0);
  westy->SetDirectory(0);

  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
	const size_t nrawdigits = rawdigits.size();
	for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	  { 
	    size_t thigh = rawdigits[ichan].Samples()-1; // assume uncompressed
	    if (thigh < 350)
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
	    TH2F *hwfth = 0;
	    if (ic < 1984) { th = eastu; hwfth = hwfeastu; }
	    else if (ic < 3968) { th = eastv; hwfth = hwfeastv; }
	    else if (ic < 5632) { th = easty; hwfth = hwfeasty; }
	    else if (ic < 6382) { th = westublob; hwfth = hwfwestublob; }
	    else if (ic < 7616) { th = westutypec; hwfth = hwfwestutypec; } 
	    else if (ic < 9600) { th = westv; hwfth = hwfwestv; }
	    else { th = westy; hwfth = hwfwesty; }

	    for (size_t itick=tickmin;itick<=tickmax;++itick)
	      {
		//std::cout << "filling histo: " << ichan << " " << ic << " " << itick << std::endl;
		th->Fill(rawdigits[ichan].ADC(itick));
		hwfth->Fill(itick,rawdigits[ichan].ADC(itick));
	      }
	  }
      }
    ++evcounter;
  }
  mycanvas->Divide(4,4);

  mycanvas->cd(1);
  gPad->SetLogy(0);
  gPad->SetLogz();
  hwfeastu->Draw("colz");
  mycanvas->cd(2);
  gPad->SetLogy();
  eastu->Draw("hist");

  mycanvas->cd(3);
  gPad->SetLogy(0);
  gPad->SetLogz();
  hwfeastv->Draw("colz");
  mycanvas->cd(4);
  gPad->SetLogy();
  eastv->Draw("hist");

  mycanvas->cd(5);
  gPad->SetLogy(0);
  gPad->SetLogz();
  hwfeasty->Draw("colz");
  mycanvas->cd(6);
  gPad->SetLogy();
  easty->Draw("hist");

  mycanvas->cd(7);
  gPad->SetLogy(0);
  gPad->SetLogz();
  hwfwestublob->Draw("colz");
  mycanvas->cd(8);
  gPad->SetLogy();
  westublob->Draw("hist");

  mycanvas->cd(9);
  gPad->SetLogy(0);
  gPad->SetLogz();
  hwfwestutypec->Draw("colz");
  mycanvas->cd(10);
  gPad->SetLogy();
  westutypec->Draw("hist");

  mycanvas->cd(11);
  gPad->SetLogy(0);
  gPad->SetLogz();
  hwfwestv->Draw("colz");
  mycanvas->cd(12);
  gPad->SetLogy();
  westv->Draw("hist");

  mycanvas->cd(13);
  gPad->SetLogy(0);
  gPad->SetLogz();
  hwfwesty->Draw("colz");
  mycanvas->cd(14);
  gPad->SetLogy();
  westy->Draw("hist");

  mycanvas->Print("sunset_run"+runstr+"planehistos.png");

}
