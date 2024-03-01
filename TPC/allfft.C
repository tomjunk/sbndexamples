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

// gallery script to make an FFT plot for every channel in SBND

// arguments:  filename -- input file, larsoft formatted
// ievcount:  which event to display the FFT for.  This is the tree index in the file and not the event number
// tickmin, tickmax -- to truncate the part of the event to run the FFT on.  Set to big and small numbers for no truncation.
// digifreq:  ADC Sampling frequency in MHz.  Used to label plots.  It's 2 MHz for 35t, DUNE FD MC, and 2.5 MHz for 3x1x1
// inputtag: use "tpcrawdecoder:daq" for input

void allfft(std::string const& filename="tpcdecode_data_evb03_run11395_2_20240227T194156.root",  
            size_t tickmin=0,
            size_t tickmax=3413,  // we have an odd number of ticks, 3415; take only the first 3414 
            std::string const& inputtag="daq", 
            double digifreq=2.0,
            TString outputfilename="allchanfft.root")
{
  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames;

  filenames.push_back("tpcdecode_data_evb01_run10880_10_20240208T183019.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_11_20240208T183119.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_12_20240208T183219.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_13_20240208T183320.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_14_20240208T183420.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_15_20240208T183520.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_16_20240208T183621.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_17_20240208T183721.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_18_20240208T183821.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_19_20240208T183922.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_20_20240208T184022.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_21_20240208T184122.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_2_20240208T182217.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_22_20240208T184223.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_23_20240208T184323.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_24_20240208T184423.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_25_20240208T184524.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_26_20240208T184624.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_27_20240208T184724.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_28_20240208T184825.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_29_20240208T184925.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_30_20240208T185025.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_31_20240208T185126.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_3_20240208T182316.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_32_20240208T185226.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_33_20240208T185327.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_34_20240208T185427.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_35_20240208T185527.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_36_20240208T185628.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_4_20240208T182416.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_5_20240208T182517.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_6_20240208T182617.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_7_20240208T182717.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_8_20240208T182818.root");
  filenames.push_back("tpcdecode_data_evb01_run10880_9_20240208T182918.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_10_20240208T183020.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_11_20240208T183120.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_1_20240208T182117.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_12_20240208T183220.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_13_20240208T183321.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_14_20240208T183421.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_15_20240208T183521.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_16_20240208T183622.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_17_20240208T183722.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_18_20240208T183822.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_19_20240208T183923.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_20_20240208T184023.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_21_20240208T184123.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_2_20240208T182218.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_22_20240208T184224.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_23_20240208T184324.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_24_20240208T184424.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_25_20240208T184525.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_26_20240208T184625.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_27_20240208T184725.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_28_20240208T184826.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_29_20240208T184926.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_30_20240208T185026.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_31_20240208T185127.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_3_20240208T182317.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_32_20240208T185227.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_33_20240208T185328.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_34_20240208T185428.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_35_20240208T185528.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_36_20240208T185629.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_4_20240208T182417.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_5_20240208T182518.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_6_20240208T182618.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_7_20240208T182718.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_8_20240208T182819.root");
  filenames.push_back("tpcdecode_data_evb02_run10880_9_20240208T182919.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_10_20240208T183021.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_11_20240208T183121.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_1_20240208T182118.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_12_20240208T183221.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_13_20240208T183322.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_14_20240208T183422.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_15_20240208T183522.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_16_20240208T183623.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_17_20240208T183723.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_18_20240208T183823.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_19_20240208T183924.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_20_20240208T184024.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_21_20240208T184124.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_2_20240208T182219.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_22_20240208T184225.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_23_20240208T184325.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_24_20240208T184425.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_25_20240208T184526.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_26_20240208T184626.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_27_20240208T184726.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_28_20240208T184827.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_29_20240208T184927.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_30_20240208T185027.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_31_20240208T185128.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_3_20240208T182318.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_32_20240208T185228.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_33_20240208T185329.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_34_20240208T185429.root");

  std::map<size_t,TProfile*> profmap;

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
            size_t ic = rawdigits[ichan].Channel(); 
            if (profmap.find(ic) == profmap.end())
              {
                TString hid = "chan";
                hid += ic;
                TString htitle = "Channel ";
                htitle += ic;
                htitle += ";Frequency (MHz);FFT";

                //std::cout << "creating histo: " << ic << std::endl;
                profmap[ic] = (TProfile*) new TProfile(hid,htitle,nticks/2,0,digifreq/2.0);
                profmap[ic]->SetDirectory(0);
              }
            TProfile *cf1dt = profmap[ic];
                
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
                cf1dt->Fill((i+0.5)*sf,mag); 
              }
          }
        //cout << "Finished fft'ing channels" << endl;
      }  // end check if rawdigits are empty
  } // end loop over events
  TFile outputfile(outputfilename,"RECREATE");
  outputfile.cd();
  for (auto const& iter : profmap)
    {
      iter.second->Write();
    }
  std::cout << "closing output file" << std::endl;
  //outputfile.Close();
}

