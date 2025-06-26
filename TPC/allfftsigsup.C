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
// input file names now listed in code.  With primitive signal suppression
// for use with running data.

// arguments
// tickmin, tickmax -- to truncate the part of the event to run the FFT on.  Set to big and small numbers for no truncation.
// digifreq:  ADC Sampling frequency in MHz.  Used to label plots.  It's 2 MHz for 35t, DUNE FD MC, and 2.5 MHz for 3x1x1
// inputtag: use "tpcrawdecoder:daq" for input

void allfftsigsup(size_t tickmin=0,
                  size_t tickmax=3425,  // we have an odd number of ticks so take an even-sized subset
                  std::string const& inputtag="daq", 
                  double digifreq=2.0,
                  TString outputfilename="allchanfft.root")
{
  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames;

  filenames.push_back("decode_data_EventBuilder1_art1_run18005_118_strmBNBZeroBias_20241215T125214-90787acb-7da1-45b1-8c80-b03fbb758ef0.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_127_strmBNBZeroBias_20241215T132603-6b2b37b5-9428-4af8-a782-ad9a19f4c870.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_135_strmBNBZeroBias_20241215T135558-1b4aff67-7e0c-487b-839c-4be55be8115e.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_139_strmBNBZeroBias_20241215T141100-ba5e14cd-3c4f-4160-8b87-77e32fe77ca8.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_13_strmOffBeamZeroBias_20241215T073900-2699c704-f9a5-4c87-adb3-1510894677e5.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_15_strmOffBeamZeroBias_20241215T075820-87f177b0-d1b3-498c-8840-5effd44ab1b7.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_17_strmOffBeamZeroBias_20241215T081548-9fbf0b87-bcca-4217-8ad7-a97620454250.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_24_strmBNBZeroBias_20241215T070528-eec3099f-8766-4d1b-bf50-aadc8e1698d6.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_26_strmBNBZeroBias_20241215T071315-47c4bc1d-59f8-4104-a587-f75a06ec7a3e.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_2_strmOffBeamZeroBias_20241215T055210-60d118d5-bb41-4b1a-9180-e780cd377c87.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_31_strmOffBeamZeroBias_20241215T103539-dd11c430-91bb-4bb4-b9c0-405af9017878.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_33_strmOffBeamZeroBias_20241215T105557-1340d24d-ee85-417a-867a-68717a6ba90d.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_34_strmOffBeamZeroBias_20241215T110339-a8937411-c87e-4cd9-9b30-e9e4fb057d63.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_36_strmBNBZeroBias_20241215T075000-25cd5a91-380f-4f62-93a1-5c2260af5a87.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_40_strmBNBZeroBias_20241215T080533-6c1871a3-30ff-4bc8-8610-5c75df03a49c.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_42_strmBNBZeroBias_20241215T081259-8f0f848f-26d4-425c-9c87-f70b90748611.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_44_strmBNBZeroBias_20241215T082012-d4b1913c-c15f-4870-82f1-3a9c9d4b2fdf.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_49_strmBNBZeroBias_20241215T083911-82d1b088-c87d-4d06-849f-0df90ac8d95d.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_50_strmBNBZeroBias_20241215T084248-99229b5d-4873-46c8-9b99-6596c5a629c9.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_55_strmOffBeamZeroBias_20241215T142344-87e58a75-cbb7-49de-9eb9-448c06e7ccca.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_69_strmBNBZeroBias_20241215T095246-179ecd46-4221-4099-b870-0e071dd8fc8c.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_87_strmBNBZeroBias_20241215T105829-12ce8c09-1d3c-4ec5-81c7-63bc2dad09dd.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_8_strmCrossingMuon_20241215T073706-fb3fc13d-18ae-4f39-a3b9-d02e6b0cd870.root");
  filenames.push_back("decode_data_EventBuilder1_art1_run18005_90_strmBNBZeroBias_20241215T110926-441972ab-59f7-4987-8a08-143fa8e88571.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_105_strmBNBZeroBias_20241215T120419-dd87dfe9-1bc7-4ca0-83a6-a1c147d98cd7.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_107_strmBNBZeroBias_20241215T121150-87f52709-472a-4704-9d57-2b8dfea76dca.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_125_strmBNBZeroBias_20241215T131906-9bcf2531-58f9-487f-80d4-09022804fb7d.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_21_strmBNBZeroBias_20241215T065417-187655ae-c828-4a49-ba33-841bf4f5266a.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_28_strmOffBeamZeroBias_20241215T100733-0f30f534-8873-40ce-8ac5-b218edefff93.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_30_strmOffBeamZeroBias_20241215T102602-71772787-07ad-4e5f-961a-21a2aff25da0.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_31_strmOffBeamZeroBias_20241215T103453-f2b29482-4ed3-464a-8758-7e754dc58f3e.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_34_strmOffBeamZeroBias_20241215T110506-5fd658e4-d047-4b48-b8c4-2f493849a387.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_3_strmBNBZeroBias_20241215T054808-2a7d93b3-685a-4d14-b785-42cf371efa87.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_47_strmBNBZeroBias_20241215T083111-8808d8fb-adbb-4eb6-b87b-ae1d48e561d2.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_49_strmBNBZeroBias_20241215T083825-4487d511-1067-4078-b0fe-cdaded4f77a4.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_50_strmOffBeamZeroBias_20241215T133916-838df2e7-20e6-4e00-85ff-d870aa701138.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_53_strmBNBZeroBias_20241215T085310-378c15d3-6d8f-4b26-878a-ae467923391c.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_62_strmBNBZeroBias_20241215T092506-d9d7f632-687c-4d67-8906-0685ecf79f4c.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_87_strmBNBZeroBias_20241215T105729-5b732d8c-88a2-41b5-bfa7-18df1172cc50.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_8_strmCrossingMuon_20241215T074527-1441d214-714b-4883-9987-93abbd04dbab.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_99_strmBNBZeroBias_20241215T114303-cb98f775-0c13-4184-8648-0ab4d3b98587.root");
  filenames.push_back("decode_data_EventBuilder1_art2_run18005_9_strmBNBZeroBias_20241215T061036-6dda7515-be71-484a-ba40-b87958a2a765.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_105_strmBNBZeroBias_20241215T120929-dc9cb473-8769-4972-b406-7048c58635d2.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_10_strmOffBeamZeroBias_20241215T070423-81714379-c6c2-466b-b894-82a885e879a6.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_111_strmBNBZeroBias_20241215T123104-8798f865-fe89-435e-b5f2-f6475f21a682.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_12_strmCrossingMuon_20241215T085139-30ce1fd6-ccdd-424e-a7b2-52fa87a45cfe.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_142_strmBNBZeroBias_20241215T142506-9d8be85b-04fd-4e87-a90b-853ecb13b2d4.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_16_strmOffBeamZeroBias_20241215T080136-14443738-0c4a-4a41-9517-56296d980d87.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_17_strmOffBeamZeroBias_20241215T081050-0ff8871c-4458-427c-ab8c-64b0345ab136.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_29_strmOffBeamZeroBias_20241215T100409-987b601c-6a5f-4f62-87ee-c42d7030573c.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_31_strmBNBZeroBias_20241215T073354-8ee1f977-9702-4b61-8779-d256c398e51c.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_35_strmBNBZeroBias_20241215T074913-a27d932b-03e3-4e27-87b7-0961435f950c.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_3_strmCrossingMuon_20241215T061529-8d887215-0d2f-43e9-9686-9ae28baf1974.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_40_strmBNBZeroBias_20241215T080753-1ea95e0f-5f59-49bf-87c8-86ee53a1f918.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_45_strmBNBZeroBias_20241215T082615-1d5bb2f1-3488-4635-be95-adffdaaa878e.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_51_strmBNBZeroBias_20241215T084830-9ccb1415-1a6c-4176-87de-70662e9a10ef.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_52_strmBNBZeroBias_20241215T085209-2aa91c81-a87c-43f8-9bcc-7bd80779cc85.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_55_strmOffBeamZeroBias_20241215T140733-73df7a8a-9187-43d6-81a0-95283c347424.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_56_strmBNBZeroBias_20241215T090614-a0971347-a534-4f87-b63c-f3828279e837.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_5_strmOffBeamZeroBias_20241215T061619-ccf677b0-5258-4c8b-8b98-6339ca9b8c87.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_69_strmBNBZeroBias_20241215T095523-e9926b98-fad4-4b59-bcd1-ce787f6cbafc.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_79_strmBNBZeroBias_20241215T103254-2b970e6b-7aaf-4bee-8f88-5dbd887b5edf.root");
  filenames.push_back("decode_data_EventBuilder2_art1_run18005_87_strmBNBZeroBias_20241215T110324-761878c9-cdcd-4a4a-aeba-691e9e3f1dd8.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_109_strmBNBZeroBias_20241215T122247-90f0bfa1-40af-4877-9866-1080db2a7e07.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_123_strmBNBZeroBias_20241215T131431-8796f5ef-6872-44f5-a349-9c8a805a4956.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_127_strmBNBZeroBias_20241215T132858-f9a1e0a9-5746-458c-87fc-209fda2be52b.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_135_strmBNBZeroBias_20241215T135958-5d8493fb-8773-4905-9a45-2b3a939e7187.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_16_strmBNBZeroBias_20241215T063614-c8b1f97d-cb68-487b-a594-38ab5410acb8.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_18_strmCrossingMuon_20241215T103746-cb1bc8cc-8287-4642-98f2-17fea652f8fc.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_19_strmBNBZeroBias_20241215T064818-7265ccbd-9018-4c4b-ac89-0687b962c69f.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_21_strmBNBZeroBias_20241215T065615-0b02f240-dbd5-4c4f-93d0-587bbb67b9c3.root");
  filenames.push_back("decode_data_EventBuilder2_art2_run18005_21_strmOffBeamZeroBias_20241215T084954-5ca76135-3ce9-4546-87fe-8336380d3836.root");

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
	    if (rawdigits[ichan].GetSigma() > 10) continue;
	    auto p=rawdigits[ichan].GetPedestal();
	    
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

