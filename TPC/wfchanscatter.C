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
#include "Riostream.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TROOT.h"

using namespace art;
using namespace std;


void wfchanscatter(
	    size_t ichanrequest=7163,
            size_t ichanrequest2=8372,
            size_t ievcount=1, 
	    std::string const& filename="decoded_data_evb01_run12007_12_20240319T153432.root", 
            std::string const& inputtag="daq")
{
  gStyle->SetOptStat(0);
  TCanvas *mycanvas = (TCanvas*) new TCanvas("c1","c1",1000,500);

  size_t evcounter=0;

  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames(1, filename);

  TH2F *outhist = (TH2F*) new TH2F("ch","Channel 8372 vs. Channel 7163;Channel 7163 [ADC];Channel 8372 [ADC]",100,1900,2200,100,1900,2200);
  outhist->SetDirectory(0);
  
  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    if (evcounter == ievcount)
      {
	auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
	if (!rawdigits.empty())
	  {
	    const size_t nrawdigits = rawdigits.size();
	    std::vector<int> adcrequest;
	    std::vector<int> adcrequest2;
	    for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	      { 
	        size_t thigh = rawdigits[ichan].Samples()-1; // assume uncompressed
		size_t ic = rawdigits[ichan].Channel();
		
		if ( ic == ichanrequest )
		  {
		    TString title="Channel ";
		    title += ichanrequest;
		    title += ";tick;ADC";
                    for (size_t itick=0;itick<=thigh;++itick)
	              {
			adcrequest.push_back(rawdigits[ichan].ADC(itick));
		      }
		  }
		if (ic == ichanrequest2)
		  {
                    for (size_t itick=0;itick<=thigh;++itick)
	              {
			adcrequest2.push_back(rawdigits[ichan].ADC(itick));
		      }
		  }
	      }
	    for (size_t iwf = 0; iwf < adcrequest.size(); ++ iwf)
	      {
		outhist->Fill(adcrequest.at(iwf),adcrequest2.at(iwf));
	      }
	  }
      }
    ++evcounter;
  }
  outhist->Draw("box");
}


