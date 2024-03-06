#include <TGraph.h>
#include <TString.h>
#include <TCanvas.h>
#include <Riostream.h>
#include <vector>
#include <iostream>
#include <TMath.h>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"

#include "TFile.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TVectorT.h"
#include "lardataobj/RawData/RawDigit.h"
#include "TLegend.h"
#include "Riostream.h"
#include "TROOT.h"

// too lazy to encapsulate these global variables

const int nchans=11264;
int larsoftch[nchans];
int cryostat[nchans];
int tpc[nchans];
int plane[nchans];
int pwire[nchans];
double wx1[nchans];
double wy1[nchans];
double wz1[nchans];
double wx2[nchans];
double wy2[nchans];
double wz2[nchans];

using namespace art;
using namespace std;

void readfile(TString filename="sbndwireends.txt");

void rmsvswirelen(std::string filename="tpcdecode_data_evb03_run11505_24_20240304T182922.root")
{
  readfile();

  TGraph *rgraph = (TGraph*) new TGraph();
  TGraph *rgraphq = (TGraph*) new TGraph();
  TCanvas *rcanvas = (TCanvas*) new TCanvas("c1","",1500,1100);
  rgraph->SetTitle("Wire Noise vs. Wire Length;Wire Length [cm];RMS [ADC counts]");
  rgraphq->SetTitle("Quad Diff Wire Noise - Discon Wire Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  InputTag rawdigit_tag{ "daq" };
  vector<string> filenames(1, filename);

  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
	const size_t nrawdigits = rawdigits.size();
	double avgdiscon = 0;
	int ndiscon = 0;
	for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	  { 
	    size_t ic = rawdigits[ichan].Channel();
	    double rms = rawdigits[ichan].GetSigma();
	    if (ic >= nchans) continue;
	    double wirelen = TMath::Sqrt( TMath::Sq(wx1[ic] - wx2[ic]) +
					  TMath::Sq(wy1[ic] - wy2[ic]) +
					  TMath::Sq(wz1[ic] - wz2[ic]) );
	    rgraph->AddPoint(wirelen,rms);
	    if (ic == 10030 || ic == 10833 || ic == 5201 || ic == 4398)
	      {
		ndiscon++;
		avgdiscon += rms;
	      }
	  }
	if (ndiscon>0)
	  {
	    avgdiscon /= ((double) ndiscon);
	  }
	for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	  { 
	    size_t ic = rawdigits[ichan].Channel();
	    double rms = rawdigits[ichan].GetSigma();
	    if (ic >= nchans) continue;
	    double wirelen = TMath::Sqrt( TMath::Sq(wx1[ic] - wx2[ic]) +
					  TMath::Sq(wy1[ic] - wy2[ic]) +
					  TMath::Sq(wz1[ic] - wz2[ic]) );
	    rgraphq->AddPoint(wirelen,TMath::Sqrt(TMath::Max(0.0,rms*rms - avgdiscon*avgdiscon)));
	  }
      }
  }
  rgraph->SetMinimum(0);
  rgraph->SetMaximum(4);
  rgraph->Draw("AP");
  rcanvas->Print("rmsvswirelen.png");

  rgraphq->SetMinimum(0);
  rgraphq->SetMaximum(4);
  rgraphq->Draw("AP");
  rcanvas->Print("rmsvswirelen_quaddiff.png");
}

void readfile(TString filename)
{
  ifstream infile;
  infile.open(filename);

  int ichan = 0;
  
  while (1) 
    {
      infile >> larsoftch[ichan] >> cryostat[ichan] >> tpc[ichan] >> plane[ichan] >> pwire[ichan] >> wx1[ichan] >> wy1[ichan] >> wz1[ichan] >> wx2[ichan] >> wy2[ichan] >> wz2[ichan];
      if (!infile.good()) break;
      ichan++;
    }
  if (ichan != nchans)
    {
      std::cout << "bad number of input channels: " << ichan << " != " << nchans << std::endl; 
    }
}
