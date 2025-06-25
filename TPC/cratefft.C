#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"

#include "TFile.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TProfile.h"
#include "TMath.h"
#include "TVirtualFFT.h"
#include "lardataobj/RawData/RawDigit.h"


// too lazy to encapsulate these global variables

const int nchans=11276;

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

// gallery script to make an FFT range plot for a set of channels for a single input file
// run over files and put plots in a rootfile

// tickmin, tickmax -- to truncate the part of the event to run the FFT on.  Set to big and small numbers for no truncation.
// digifreq:  ADC Sampling frequency in MHz.  Used to label plots.  It's 2 MHz for 35t, DUNE FD MC, and 2.5 MHz for 3x1x1
// inputtag: use "tpcrawdecoder:daq" for input

void cratefftfile(string filename,
                      std::vector<TProfile *> &ffthist,
		      std::vector<int> &cratevec,
                      size_t tickmin,
                      size_t tickmax,
                      std::string const& inputtag,
                      double digifreq);


// main method of this script

void cratefft(TString outputfilename="fftrangetimedep.root",
		  size_t tickmin=0,
		  size_t tickmax=3426,   // we have an odd number of ticks, 3427 -- take the first 3426
                  double digifreq=2.0
		  )
{

  vector<TProfile*> profhistos;
  
  vector<string> filenames;

  filenames.push_back("data_EventBuilder2_p2_art1_run18537_1_strmOffBeamZeroBias_20250624T214951_tpcdecode.root");

  readchanmapfile();
  
  // ranges, names and titles
  vector<TString> rangename;
  vector<TString> rangetitle;
  vector<int> cratevec;
  
  cratevec.push_back(1);
  rangename.push_back("C1");
  rangetitle.push_back("Crate 1");

  cratevec.push_back(2);
  rangename.push_back("C2");
  rangetitle.push_back("Crate 2");

  cratevec.push_back(3);
  rangename.push_back("C3");
  rangetitle.push_back("Crate 3");

  cratevec.push_back(4);
  rangename.push_back("C4");
  rangetitle.push_back("Crate 4");
  
  size_t nticks = tickmax - tickmin + 1;

  for (const auto &filename : filenames)
    {
      // get the run number
      
      size_t rp = filename.find("run");
      size_t next_ = filename.find("_",rp);
      string rnst = filename.substr(rp + 3, next_ - rp -3);

      // get the time string
      
      size_t rt = filename.find("_",next_ + 1);
      next_ = filename.find(".root",rt);
      string tstring = filename.substr(rt+1,next_ - rt - 1);
      
      int irun = stoi(rnst);
      std::vector<TProfile*> ffthistvec;
      for (size_t i=0; i<cratevec.size(); ++i)
	{
          TString hid="fft_";
          hid += rangename.at(i);
	  hid += "_";
          hid += irun;
	  TString htitle="FFT Run ";
	  htitle += irun;
	  htitle += " ";
	  htitle += rangetitle.at(i);
	  htitle += " ";
	  htitle += tstring;
          htitle += ";Frequency [MHz];FFT";
          ffthistvec.push_back((TProfile*) new TProfile(hid,htitle,nticks/2,0,digifreq/2.0));
          ffthistvec.back()->SetDirectory(0);
	  profhistos.push_back(ffthistvec.back());
	}
      cratefftfile(filename,ffthistvec,cratevec,tickmin,tickmax,"daq",digifreq);
    }

  TFile outputfile(outputfilename,"RECREATE");
  outputfile.cd();
  for (auto const& iter : profhistos)
    {
      iter->Write();
    }
  std::cout << "closing output file" << std::endl;


}

// process one file
void cratefftfile(string filename,
                      std::vector<TProfile *> &ffthist,
		      std::vector<int> &cratevec,
                      size_t tickmin,
                      size_t tickmax, 
                      std::string const& inputtag, 
                      double digifreq
		      )
{
  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames;
  filenames.push_back(filename);

  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
        size_t nrawdigits = rawdigits.size();

        size_t tlow = TMath::Max(tickmin, (size_t) 0);
        size_t thigh = TMath::Min(tickmax, (size_t) rawdigits[0].Samples()-1); // assume uncompressed; all channels have the same number of samples
        size_t nticks = thigh - tlow + 1;

        double x[nticks];
        double re=0;
        double im=0;
        double mag=0;
        double sf = digifreq/nticks;

        Int_t nti = nticks;
        TVirtualFFT *fftr2c = TVirtualFFT::FFT(1,&nti,"R2C ES K");
        for (size_t ichan=0;ichan<nrawdigits;++ichan)
          {
            int ic = rawdigits[ichan].Channel(); 
	    if (rawdigits[ichan].GetSigma() > 10) continue;

	    auto p=rawdigits[ichan].GetPedestal();
            for (size_t itick=tlow; itick <= thigh; ++itick)
	      {
		auto a = rawdigits[ichan].ADC(itick);
		auto r = p;
		if (std::abs(a-p) < 6) r = a;   // put in pedestal for samples more than 6 counts away from pedestal.
		x[itick-tlow] = r;
	      }
            //cout << x[0] << " " << x[1] << " " << x[2] << endl;
            fftr2c->SetPoints(x);
            fftr2c->Transform();

	    ChanInfo_t cinfo = GetChanInfoFromOfflChan(ic);
	    
	    for (size_t irange=0; irange<cratevec.size(); ++irange)
	      {
		if (cinfo.WIBCrate == cratevec.at(irange))
		  {
		    // skip the first bin as it has the pedestal
		    for (size_t i=1;i<nticks/2;++i)
		      {
			fftr2c->GetPointComplex(i, re, im);
			mag = TMath::Sqrt(re*re + im*im);
			// cout << mag << endl;
			ffthist.at(irange)->Fill((i+0.5)*sf,mag); 
		      }
		  }
	      }
	  }
	//cout << "Finished fft'ing channels" << endl;
      }  // end check if rawdigits are empty
  } // end loop over events
}


void readchanmapfile()
{
  std::string fullname("SBNDTPCChannelMap_v2.txt");
			     
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
    c.asicchan = c.FEMBCh % 16;
    
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

