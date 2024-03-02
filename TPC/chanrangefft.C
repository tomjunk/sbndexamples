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

using namespace art;
using namespace std;

// gallery script to make an FFT range plot for a set of channels for a single input file
// run over files and put plots in a rootfile

// tickmin, tickmax -- to truncate the part of the event to run the FFT on.  Set to big and small numbers for no truncation.
// digifreq:  ADC Sampling frequency in MHz.  Used to label plots.  It's 2 MHz for 35t, DUNE FD MC, and 2.5 MHz for 3x1x1
// inputtag: use "tpcrawdecoder:daq" for input

void chanrangefftfile(string filename="tpcdecode_data_evb03_run11395_2_20240227T194156.root",
                      TProfile *ffthist=0,
		      int chanmin=0,
		      int chanmax=1983,
                      size_t tickmin=0,
                      size_t tickmax=3413,
                      std::string const& inputtag="daq", 
                      double digifreq=2.0);


// main method of this script

void chanrangefft(TString outputfilename="fftrangetimedep.root",
		  size_t tickmin=0,
		  size_t tickmax=3413,   // we have an odd number of ticks, 3415; take only the first 3414
                  double digifreq=2.0
		 )
{

  vector<TProfile*> profhistos;
  
  vector<string> filenames;
  filenames.push_back("tpcdecode_data_evb01_run10931_49_20240212T185526.root");
  filenames.push_back("tpcdecode_data_evb01_run11035_3_20240214T192232.root");
  filenames.push_back("tpcdecode_data_evb01_run11186_46_20240220T144942.root");
  filenames.push_back("tpcdecode_data_evb01_run11214_56_20240220T215847.root");
  filenames.push_back("tpcdecode_data_evb01_run11239_3_20240221T200641.root");
  filenames.push_back("tpcdecode_data_evb01_run11333_24_20240225T182536.root");
  filenames.push_back("tpcdecode_data_evb02_run10959_8_20240213T152038.root");
  filenames.push_back("tpcdecode_data_evb02_run11112_2_20240216T004821.root");
  filenames.push_back("tpcdecode_data_evb02_run11266_57_20240222T202218.root");
  filenames.push_back("tpcdecode_data_evb03_run11058_5_20240215T192031.root");
  filenames.push_back("tpcdecode_data_evb03_run11141_57_20240217T020310.root");
  filenames.push_back("tpcdecode_data_evb03_run11171_52_20240218T015927.root");
  filenames.push_back("tpcdecode_data_evb03_run11174_64_20240219T020714.root");
  filenames.push_back("tpcdecode_data_evb03_run11175_47_20240219T144903.root");
  filenames.push_back("tpcdecode_data_evb03_run11306_11_20240223T194916.root");
  filenames.push_back("tpcdecode_data_evb03_run11353_6_20240226T210932.root");
  filenames.push_back("tpcdecode_data_evb03_run11395_2_20240227T194156.root");
  filenames.push_back("tpcdecode_data_evb03_run11421_19_20240228T182245.root");

  // ranges, names and titles
  vector<int> clow;
  vector<int> chigh;
  vector<TString> rangename;
  vector<TString> rangetitle;

  clow.push_back(0);
  chigh.push_back(1983);
  rangename.push_back("UE");
  rangetitle.push_back("East U Channels");

  clow.push_back(1984);
  chigh.push_back(3967);
  rangename.push_back("VE");
  rangetitle.push_back("East V Channels");

  clow.push_back(3968);
  chigh.push_back(5631);
  rangename.push_back("YE");
  rangetitle.push_back("East Y Channels");

  clow.push_back(5632);
  chigh.push_back(7615);
  rangename.push_back("UW");
  rangetitle.push_back("West U Channels");

  clow.push_back(7616);
  chigh.push_back(9599);
  rangename.push_back("VW");
  rangetitle.push_back("West V Channels");

  clow.push_back(9600);
  chigh.push_back(11263);
  rangename.push_back("YW");
  rangetitle.push_back("West Y Channels");

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
      for (size_t i=0; i<clow.size(); ++i)
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
          TProfile* ffthist = (TProfile*) new TProfile(hid,htitle,nticks/2,0,digifreq/2.0);
          ffthist->SetDirectory(0);
	  profhistos.push_back(ffthist);
	  chanrangefftfile(filename,ffthist,clow.at(i),chigh.at(i),tickmin,tickmax);
	}
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
void chanrangefftfile(string filename,
                      TProfile *ffthist,
		      int chanmin,
		      int chanmax,
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
	    if (ic < chanmin || ic > chanmax) continue;
	    if (rawdigits[ichan].GetSigma() > 10) continue;
	    
            for (size_t itick=tlow; itick <= thigh; ++itick) x[itick-tlow] = rawdigits[ichan].ADC(itick); 
            //cout << x[0] << " " << x[1] << " " << x[2] << endl;
            fftr2c->SetPoints(x);
            fftr2c->Transform();
	    // skip the first bin as it has the pedestal
            for (size_t i=1;i<nticks/2;++i)
              {
                fftr2c->GetPointComplex(i, re, im);
                mag = TMath::Sqrt(re*re + im*im);
                // cout << mag << endl;
                ffthist->Fill((i+0.5)*sf,mag); 
              }
          }
        //cout << "Finished fft'ing channels" << endl;
      }  // end check if rawdigits are empty
  } // end loop over events
}

