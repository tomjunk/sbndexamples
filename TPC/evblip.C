#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"

#include "TFile.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TMath.h"
#include "lardataobj/RawData/RawDigit.h"

using namespace art;
using namespace std;

// gallery script to print out run and event numbers for blips in East V


void evblip()
{
  std::string const& inputtag="daq";
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
  filenames.push_back("tpcdecode_data_evb03_run10880_35_20240208T185529.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_36_20240208T185630.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_4_20240208T182418.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_5_20240208T182519.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_6_20240208T182619.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_7_20240208T182719.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_8_20240208T182820.root");
  filenames.push_back("tpcdecode_data_evb03_run10880_9_20240208T182920.root");

  std::map<size_t,TProfile*> profmap;

  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
        size_t nrawdigits = rawdigits.size();
	size_t nsamples = rawdigits[0].Samples();

	bool printed = false;
        for (size_t ichan=0;ichan<nrawdigits;++ichan)
          {
            size_t ic = rawdigits[ichan].Channel();
	    if (ic < 1984 || ic > 3967) continue;
	    float pedestal = rawdigits[ichan].GetPedestal();
            for (size_t itick=0; itick < nsamples; ++itick)
	      {
		float s = TMath::Abs(rawdigits[ichan].ADC(itick) - pedestal);
		if (s > 50)
		  {
		    auto const& evaux = ev.eventAuxiliary();
                    int runno = evaux.run();
	            //int subrunno = evaux.subRun();
                    int eventno = evaux.event();
                    std::cout << "Found Blip East V: " << runno << " " << " " << eventno << std::endl;
		    printed = true;
		    break;
		  }
	      }
	    if (printed) break;
          }
      }  // end check if rawdigits are empty
  } // end loop over events
}

