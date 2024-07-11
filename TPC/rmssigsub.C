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

using namespace art;
using namespace std;

void allrmssigsub();

void rmssigsub(std::string const& filename="/home/trj/saut/triggerdecoder/sbndc4/work/run12007/decoded_data_evb02_run12007_1_20240319T152330.root",
	       TString outputfilename="rms35kv.png",
	       TString inputtitle="Run 12007 HV=35 kV") 
{
  std::string const& inputtag="daq";

  gStyle->SetOptStat(0);

  size_t evcounter=0;

  TCanvas *mycanvas = (TCanvas*) new TCanvas("c1","c1",1600,600);

  TString ht = inputtitle;
  ht += ";Channel;RMS [ADC]";
  TProfile *rmschan = (TProfile*) new TProfile("rmschan",ht,11264,-0.5,11263.5);
  rmschan->SetDirectory(0);
  
  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames(1, filename);

  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
	const size_t nrawdigits = rawdigits.size();
	for (size_t ichan=0;ichan<nrawdigits; ++ichan)
	  {
	    size_t ic = rawdigits[ichan].Channel();
	    std::vector<float> wfm;
	    for (size_t itick=0;itick<rawdigits[ichan].Samples();++itick)
	      {
		float asub = (float) rawdigits[ichan].ADC(itick) - rawdigits[ichan].GetPedestal();
		if (TMath::Abs(asub) < 10.0)
		  {
		    wfm.push_back(asub);
		  }
	      }
	    if (wfm.size() > 1)
	      {
		rmschan->Fill(ic,TMath::RMS(wfm.size(),wfm.data()));
	      }
	  }
      }
    ++evcounter;
  }
  rmschan->Draw("hist");
  mycanvas->Print(outputfilename);
  float sum = 0;
  float ntot = 0;
  for (int i=1;i<=rmschan->GetNbinsX();++i)
    {
      float val = rmschan->GetBinContent(i);
      if (val >0)
	{
	  sum += val;
	  ntot += 1.0;
	}
    }
  float avg = sum/ntot;
  std::cout << "Average: " << avg << std::endl;
}

void allrmssigsub()
{
  rmssigsub("/home/trj/saut/triggerdecoder/sbndc4/work/run12007/decoded_data_evb02_run12007_1_20240319T152330.root","rms35kv.png","Run 12007 HV=35 kV");
  rmssigsub("/home/trj/saut/triggerdecoder/sbndc2/work/tempdep/tpcdecode_data_evb03_run11505_24_20240304T182922.root","rms0kv.png","Run 11505 HV=0 kV");
  rmssigsub("/home/trj/saut/triggerdecoder/sbndc4/work/run14700/decode_data_evb03_EventBuilder3_art3_run14700_3_20240710T141711-d50db43b-f316-41d1-9a4a-a36382b94099.root","rms100kv.png","Run 14700 HV=100 kV");
} 
