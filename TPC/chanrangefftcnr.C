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
#include <unordered_map>

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
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TVirtualFFT.h"

// too lazy to encapsulate these global variables

const int nchans=11264;

typedef struct ChanInfo {
  unsigned int wireno;          // wire number
  unsigned int plane;           // 0: U,  1: V,  2: Y
  std::string  EastWest;        // "East" or "West"
  std::string  NorthSouth;      // "North" or "South"
  std::string  SideTop;         // "T" or "S"
  std::string  FEMBPosition;    // e.g. "A10"
  std::string  FEMBSerialNum;   // Serial number.  Some contain letters
  unsigned int FEMBOnWIB;       // 0:3
  unsigned int FEMBCh;          // channel on FEMB -- 0:127
  unsigned int asic;            // 0:7
  unsigned int asicchan;        // ASIC channel:  0 to 15
  unsigned int WIBCrate;        // 1:4
  unsigned int WIB;             // 1:6
  unsigned int WIBCh;           // 0:895   (7 FEMBs)
  unsigned int WIBQFSP;         // 1:2
  unsigned int QFSPFiber;       // 1:4
  unsigned int FEMCrate;        // 1:11
  unsigned int FEM;             // 1:16
  unsigned int FEMCh;           // 0:63 channel in a FEM
  unsigned int offlchan;        // in gdml and channel sorting convention
  bool valid;          // true if valid, false if not
} ChanInfo_t;

ChanInfo_t GetChanInfoFromFEMElements(
				      unsigned int femcrate,
				      unsigned int fem,
				      unsigned int femchan);

ChanInfo_t GetChanInfoFromOfflChan(unsigned int offlchan);

// look up channel info by offline channel number
  
std::unordered_map<unsigned int, ChanInfo_t> fChanInfoFromOfflChan;

// look up channel info by FEMCrate, FEM, and FEMCh
  
std::unordered_map<unsigned int,
		   std::unordered_map<unsigned int,
				      std::unordered_map< unsigned int, ChanInfo_t > > > fChanInfoFromFEMInfo;

void readchanmapfile();

using namespace art;
using namespace std;

void chanrangefftcnr(std::string filename="tpcdecode_data_evb03_run11505_24_20240304T182922.root", int debuglevel=0)
{
  readchanmapfile();
  
  InputTag rawdigit_tag{ "daq" };
  vector<string> filenames(1, filename);

  double digifreq = 2.0;  // hardcode 2 MHz for now
  int ntickseven = 3414;  // take the first 3414 even though there are 3415

  TProfile *eufft = (TProfile*) new TProfile("eufft","East U Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *evfft = (TProfile*) new TProfile("evfft","East V Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *eyfft = (TProfile*) new TProfile("eyfft","East Y Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *wufft = (TProfile*) new TProfile("wufft","West U Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *wvfft = (TProfile*) new TProfile("wvfft","West V Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *wyfft = (TProfile*) new TProfile("wyfft","West Y Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);

  TProfile *eufftcnr = (TProfile*) new TProfile("eufftcnr","CNR East U Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *evfftcnr = (TProfile*) new TProfile("evfftcnr","CNR East V Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *eyfftcnr = (TProfile*) new TProfile("eyfftcnr","CNR East Y Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *wufftcnr = (TProfile*) new TProfile("wufftcnr","CNR West U Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *wvfftcnr = (TProfile*) new TProfile("wvfftcnr","CNR West V Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);
  TProfile *wyfftcnr = (TProfile*) new TProfile("wyfftcnr","CNR West Y Channels;Frequency [MHz];FFT",ntickseven/2,0,digifreq/2.0);

  TH1F *eurms = (TH1F*) new TH1F("eurms","East U Channels;RMS",100,0.,4.);
  TH1F *evrms = (TH1F*) new TH1F("evrms","East V Channels;RMS",100,0.,4.);
  TH1F *eyrms = (TH1F*) new TH1F("eyrms","East Y Channels;RMS",100,0.,4.);
  TH1F *wurms = (TH1F*) new TH1F("wurms","West U Channels;RMS",100,0.,4.);
  TH1F *wvrms = (TH1F*) new TH1F("wvrms","West V Channels;RMS",100,0.,4.);
  TH1F *wyrms = (TH1F*) new TH1F("wyrms","West Y Channels;RMS",100,0.,4.);

  TH1F *eurmscnr = (TH1F*) new TH1F("eurmscnr","CNR East U Channels;RMS",100,0.,4.);
  TH1F *evrmscnr = (TH1F*) new TH1F("evrmscnr","CNR East V Channels;RMS",100,0.,4.);
  TH1F *eyrmscnr = (TH1F*) new TH1F("eyrmscnr","CNR East Y Channels;RMS",100,0.,4.);
  TH1F *wurmscnr = (TH1F*) new TH1F("wurmscnr","CNR West U Channels;RMS",100,0.,4.);
  TH1F *wvrmscnr = (TH1F*) new TH1F("wvrmscnr","CNR West V Channels;RMS",100,0.,4.);
  TH1F *wyrmscnr = (TH1F*) new TH1F("wyrmscnr","CNR West Y Channels;RMS",100,0.,4.);

  int ievent = 0;
  
  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
	ievent++;
	const size_t nrawdigits = rawdigits.size();

	// make a big map of median ADC values for each plane and FEMB for each tick.
	// for correlated noise removing
	// first index -- femb, second index, plane, third index: tick

	unordered_map<int, unordered_map<int, unordered_map<int, int>>> medianmap;
	size_t nticks = rawdigits.at(0).Samples();

	for (size_t itick=0; itick<nticks; ++itick)
	  {
	    // on this tick, make a map of ADC vectors, one per FEMB per plane
	    unordered_map<int, unordered_map<int, vector<int>>> adcvmap;
	    
	    for (size_t ichan=0; ichan<nrawdigits; ++ichan)
	      {
		unsigned int ic = rawdigits[ichan].Channel();
		auto ci = GetChanInfoFromOfflChan(ic);
		int fembident = 100*ci.WIBCrate + 10*ci.WIB + ci.FEMBOnWIB;
		// to do -- remove ROIs with signals
		adcvmap[fembident][ci.plane].push_back(rawdigits[ichan].ADC(itick) - rawdigits[ichan].GetPedestal());
	      }
	    
	    for (const auto& fp : adcvmap)  // loop over FEMBs
	      {
		for (const auto& pp : fp.second)  // loop over planes
		  {
		    int adcmed = TMath::Median(pp.second.size(),pp.second.data());
		    medianmap[fp.first][pp.first][itick] = adcmed;
		    if (debuglevel>1)
		      {
			cout << "Median on FEMBID: " << fp.first << " Plane: " << pp.first << " Tick: " << itick << " " << adcmed << endl; 
		      }
		  }
	      }
	  }

	Int_t nti = ntickseven;
	TVirtualFFT *fftr2c = TVirtualFFT::FFT(1,&nti,"R2C ES K");
	double re=0;
        double im=0;
        double mag=0;
        double sf = digifreq/ntickseven;
	
	for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	  { 
	    unsigned int ic = rawdigits[ichan].Channel();
	    auto ci = GetChanInfoFromOfflChan(ic);
	    int fembident = 100*ci.WIBCrate + 10*ci.WIB + ci.FEMBOnWIB;  // must match definition above
	    int iplane = ci.plane;
	    std::vector<int> adcsub;
	    std::vector<int> adcnonsub;
	    std::vector<double> adcsubdouble;
	    std::vector<double> adcnonsubdouble;
	    
	    for (size_t itick=0; itick<nticks; ++itick)
	      {
		adcnonsub.push_back(rawdigits[ichan].ADC(itick) - rawdigits[ichan].GetPedestal());
		adcsub.push_back(adcnonsub.back() - medianmap[fembident][iplane][itick]);
		if (debuglevel > 1)
		  {
		    if (ievent == 1 && ic == 1000)
		      {
			cout << "debug chan 1000: " << itick << " " << adcnonsub.back() << " " << adcsub.back() << " " << medianmap[fembident][iplane][itick] << endl;
		      }
		  }
		adcsubdouble.push_back(adcsub.back());
		adcnonsubdouble.push_back(adcnonsub.back());
	      }
	    
	    TProfile *unsubprof = 0;
	    TProfile *subprof = 0;

	    TH1F *unsubrms = 0;
	    TH1F *subrms = 0;
	    
	    if (ic<1984)
	      {
		unsubprof = eufft;
		subprof = eufftcnr;
		unsubrms = eurms;
		subrms = eurmscnr;
	      }
	    else if (ic < 3968)
	      {
		unsubprof = evfft;
		subprof = evfftcnr;
		unsubrms = evrms;
		subrms = evrmscnr;
	      }
	    else if (ic < 5632)
	      {
		unsubprof = eyfft;
		subprof = eyfftcnr;
		unsubrms = eyrms;
		subrms = eyrmscnr;
	      }
	    else if (ic < 7616)
	      {
		unsubprof = wufft;
		subprof = wufftcnr;
		unsubrms = wurms;
		subrms = wurmscnr;
	      }
	    else if (ic < 9600)
	      {
		unsubprof = wvfft;
		subprof = wvfftcnr;
		unsubrms = wvrms;
		subrms = wvrmscnr;
	      }
	    else
	      {
		unsubprof = wyfft;
		subprof = wyfftcnr;
		unsubrms = wyrms;
		subrms = wyrmscnr;
	      }

            double rmsval = TMath::RMS(adcnonsub.size(),adcnonsub.data());
	    unsubrms->Fill(rmsval);

	    fftr2c->SetPoints(adcnonsubdouble.data());
	    fftr2c->Transform();
	    for (int i=1; i<ntickseven/2; ++i)
	      {
		fftr2c->GetPointComplex(i, re, im);
		mag = TMath::Sqrt(re*re + im*im);
		// cout << mag << endl;
		unsubprof->Fill((i+0.5)*sf,mag); 
	      }
	    
            rmsval = TMath::RMS(adcsub.size(),adcsub.data());
	    subrms->Fill(rmsval);

	    fftr2c->SetPoints(adcsubdouble.data());
	    fftr2c->Transform();
	    for (int i=1; i<ntickseven/2; ++i)
	      {
		fftr2c->GetPointComplex(i, re, im);
		mag = TMath::Sqrt(re*re + im*im);
		// cout << mag << endl;
		subprof->Fill((i+0.5)*sf,mag); 
	      }

	  } // end loop over channels
      }  // end check for empty raw digits
  } // end loop over events

  TFile outputfile("fftcnr.root","RECREATE");
  outputfile.cd();
  eufft->Write();
  eufftcnr->Write();
  evfft->Write();
  evfftcnr->Write();
  eyfft->Write();
  eyfftcnr->Write();
  wufft->Write();
  wufftcnr->Write();
  wvfft->Write();
  wvfftcnr->Write();
  wyfft->Write();
  wyfftcnr->Write();

  eurms->Write();
  eurmscnr->Write();
  evrms->Write();
  evrmscnr->Write();
  eyrms->Write();
  eyrmscnr->Write();
  wurms->Write();
  wurmscnr->Write();
  wvrms->Write();
  wvrmscnr->Write();
  wyrms->Write();
  wyrmscnr->Write();
  std::cout << "closing output file" << std::endl;
}

void readchanmapfile()
{
  std::string fullname("SBNDTPCChannelMap_v1.txt");
			     
  std::cout << "SBND TPC Channel Map: Building TPC wiremap from file " << fullname << std::endl;
  std::ifstream inFile(fullname, std::ios::in);
  std::string line;

  while (std::getline(inFile,line)) {
    std::stringstream linestream(line);
    std::string planestr;
    std::string qfspstr;
    
    ChanInfo_t c;
    linestream 
      >> c.wireno
      >> planestr
      >> c.EastWest
      >> c.NorthSouth
      >> c.SideTop
      >> c.FEMBPosition
      >> c.FEMBSerialNum
      >> c.FEMBOnWIB
      >> c.FEMBCh
      >> c.asic
      >> c.WIBCrate
      >> c.WIB
      >> c.WIBCh 
      >> qfspstr 
      >> c.QFSPFiber 
      >> c.FEMCrate
      >> c.FEM
      >> c.FEMCh
      >> c.offlchan;

    c.valid = true;
    c.plane = 10;
    if (planestr == "U") c.plane = 0;
    if (planestr == "V") c.plane = 1;
    if (planestr == "Y") c.plane = 2;
    if (c.plane == 10) c.valid = false;
    c.WIBQFSP = atoi(qfspstr.substr(3,1).c_str());

    fChanInfoFromFEMInfo[c.FEMCrate][c.FEM][c.FEMCh] = c;
    fChanInfoFromOfflChan[c.offlchan] = c;
  }
  inFile.close();
}



ChanInfo_t GetChanInfoFromFEMElements(unsigned int femcrate,
				      unsigned int fem,
				      unsigned int femchan) {

  ChanInfo_t badinfo{};
  badinfo.valid = false;

  // look up one map at a time in order to handle cases where the item is not found
  // without throwing and catching exception which can make debugging hard
  
  auto fm1 = fChanInfoFromFEMInfo.find(femcrate);
  if (fm1 == fChanInfoFromFEMInfo.end()) {
    unsigned int substituteCrate = 1;  // a hack -- ununderstood crates get mapped to crate 1
    fm1 = fChanInfoFromFEMInfo.find(substituteCrate);
    if (fm1 == fChanInfoFromFEMInfo.end()) {
      return badinfo;
    }
  }
  auto& m1 = fm1->second;
  auto fm2 = m1.find(fem);
  if (fm2 == m1.end()) return badinfo;
  auto& m2 = fm2->second;
  auto fm3 = m2.find(femchan);
  if (fm3 == m2.end()) return badinfo;    
  return fm3->second;
}


ChanInfo_t GetChanInfoFromOfflChan(unsigned int offlineChannel) {
  ChanInfo_t badinfo{};
  badinfo.valid = false;
  auto fm = fChanInfoFromOfflChan.find(offlineChannel);
  if (fm == fChanInfoFromOfflChan.end()) return badinfo;
  return fm->second;
}
