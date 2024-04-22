#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"

#include "TFile.h"
#include "TProfile2D.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TMath.h"
#include "lardataobj/RawData/RawDigit.h"


using namespace art;
using namespace std;

// gallery script to make a 2D profile histogram of RMS vs channel and
// event number


void rchanevt()
{
  std::string const& inputtag="daq";
  InputTag rawdigit_tag{ inputtag };
  vector<string> filenames;

  filenames.push_back("decoded_data_evb01_run12007_10_20240319T153232.root");
  filenames.push_back("decoded_data_evb01_run12007_11_20240319T153332.root");
  filenames.push_back("decoded_data_evb01_run12007_12_20240319T153432.root");
  filenames.push_back("decoded_data_evb01_run12007_13_20240319T153533.root");
  filenames.push_back("decoded_data_evb01_run12007_14_20240319T153633.root");
  filenames.push_back("decoded_data_evb01_run12007_15_20240319T153734.root");
  filenames.push_back("decoded_data_evb01_run12007_16_20240319T153834.root");
  filenames.push_back("decoded_data_evb01_run12007_17_20240319T153934.root");
  filenames.push_back("decoded_data_evb01_run12007_18_20240319T154035.root");
  filenames.push_back("decoded_data_evb01_run12007_19_20240319T154135.root");
  filenames.push_back("decoded_data_evb01_run12007_20_20240319T154235.root");
  filenames.push_back("decoded_data_evb01_run12007_21_20240319T154336.root");
  filenames.push_back("decoded_data_evb01_run12007_2_20240319T152430.root");
  filenames.push_back("decoded_data_evb01_run12007_22_20240319T154436.root");
  filenames.push_back("decoded_data_evb01_run12007_23_20240319T154536.root");
  filenames.push_back("decoded_data_evb01_run12007_24_20240319T154637.root");
  filenames.push_back("decoded_data_evb01_run12007_25_20240319T154737.root");
  filenames.push_back("decoded_data_evb01_run12007_26_20240319T154837.root");
  filenames.push_back("decoded_data_evb01_run12007_27_20240319T154938.root");
  filenames.push_back("decoded_data_evb01_run12007_28_20240319T155038.root");
  filenames.push_back("decoded_data_evb01_run12007_29_20240319T155138.root");
  filenames.push_back("decoded_data_evb01_run12007_30_20240319T155239.root");
  filenames.push_back("decoded_data_evb01_run12007_31_20240319T155339.root");
  filenames.push_back("decoded_data_evb01_run12007_3_20240319T152529.root");
  filenames.push_back("decoded_data_evb01_run12007_4_20240319T152630.root");
  filenames.push_back("decoded_data_evb01_run12007_5_20240319T152730.root");
  filenames.push_back("decoded_data_evb01_run12007_6_20240319T152830.root");
  filenames.push_back("decoded_data_evb01_run12007_7_20240319T152931.root");
  filenames.push_back("decoded_data_evb01_run12007_8_20240319T153031.root");
  filenames.push_back("decoded_data_evb01_run12007_9_20240319T153131.root");
  filenames.push_back("decoded_data_evb02_run12007_10_20240319T153233.root");
  filenames.push_back("decoded_data_evb02_run12007_11_20240319T153333.root");
  filenames.push_back("decoded_data_evb02_run12007_1_20240319T152330.root");
  filenames.push_back("decoded_data_evb02_run12007_12_20240319T153433.root");
  filenames.push_back("decoded_data_evb02_run12007_13_20240319T153534.root");
  filenames.push_back("decoded_data_evb02_run12007_14_20240319T153634.root");
  filenames.push_back("decoded_data_evb02_run12007_15_20240319T153735.root");
  filenames.push_back("decoded_data_evb02_run12007_16_20240319T153835.root");
  filenames.push_back("decoded_data_evb02_run12007_17_20240319T153935.root");
  filenames.push_back("decoded_data_evb02_run12007_18_20240319T154036.root");
  filenames.push_back("decoded_data_evb02_run12007_19_20240319T154136.root");
  filenames.push_back("decoded_data_evb02_run12007_20_20240319T154236.root");
  filenames.push_back("decoded_data_evb02_run12007_21_20240319T154337.root");
  filenames.push_back("decoded_data_evb02_run12007_2_20240319T152431.root");
  filenames.push_back("decoded_data_evb02_run12007_22_20240319T154437.root");
  filenames.push_back("decoded_data_evb02_run12007_23_20240319T154537.root");
  filenames.push_back("decoded_data_evb02_run12007_24_20240319T154638.root");
  filenames.push_back("decoded_data_evb02_run12007_25_20240319T154738.root");
  filenames.push_back("decoded_data_evb02_run12007_26_20240319T154838.root");
  filenames.push_back("decoded_data_evb02_run12007_27_20240319T154939.root");
  filenames.push_back("decoded_data_evb02_run12007_28_20240319T155039.root");
  filenames.push_back("decoded_data_evb02_run12007_29_20240319T155139.root");
  filenames.push_back("decoded_data_evb02_run12007_30_20240319T155240.root");
  filenames.push_back("decoded_data_evb02_run12007_31_20240319T155340.root");
  filenames.push_back("decoded_data_evb02_run12007_3_20240319T152530.root");
  filenames.push_back("decoded_data_evb02_run12007_4_20240319T152631.root");
  filenames.push_back("decoded_data_evb02_run12007_5_20240319T152731.root");
  filenames.push_back("decoded_data_evb02_run12007_6_20240319T152831.root");
  filenames.push_back("decoded_data_evb02_run12007_7_20240319T152932.root");
  filenames.push_back("decoded_data_evb02_run12007_8_20240319T153032.root");
  filenames.push_back("decoded_data_evb02_run12007_9_20240319T153132.root");
  filenames.push_back("decoded_data_evb03_run12007_10_20240319T153234.root");
  filenames.push_back("decoded_data_evb03_run12007_11_20240319T153334.root");
  filenames.push_back("decoded_data_evb03_run12007_1_20240319T152331.root");
  filenames.push_back("decoded_data_evb03_run12007_12_20240319T153435.root");
  filenames.push_back("decoded_data_evb03_run12007_13_20240319T153535.root");
  filenames.push_back("decoded_data_evb03_run12007_14_20240319T153635.root");
  filenames.push_back("decoded_data_evb03_run12007_15_20240319T153736.root");
  filenames.push_back("decoded_data_evb03_run12007_16_20240319T153836.root");
  filenames.push_back("decoded_data_evb03_run12007_17_20240319T153936.root");
  filenames.push_back("decoded_data_evb03_run12007_18_20240319T154037.root");
  filenames.push_back("decoded_data_evb03_run12007_19_20240319T154137.root");
  filenames.push_back("decoded_data_evb03_run12007_20_20240319T154237.root");
  filenames.push_back("decoded_data_evb03_run12007_21_20240319T154338.root");
  filenames.push_back("decoded_data_evb03_run12007_2_20240319T152432.root");
  filenames.push_back("decoded_data_evb03_run12007_22_20240319T154438.root");
  filenames.push_back("decoded_data_evb03_run12007_23_20240319T154538.root");
  filenames.push_back("decoded_data_evb03_run12007_24_20240319T154639.root");
  filenames.push_back("decoded_data_evb03_run12007_25_20240319T154739.root");
  filenames.push_back("decoded_data_evb03_run12007_26_20240319T154839.root");
  filenames.push_back("decoded_data_evb03_run12007_27_20240319T154940.root");
  filenames.push_back("decoded_data_evb03_run12007_28_20240319T155040.root");
  filenames.push_back("decoded_data_evb03_run12007_29_20240319T155141.root");
  filenames.push_back("decoded_data_evb03_run12007_30_20240319T155241.root");
  filenames.push_back("decoded_data_evb03_run12007_31_20240319T155341.root");
  filenames.push_back("decoded_data_evb03_run12007_3_20240319T152531.root");
  filenames.push_back("decoded_data_evb03_run12007_4_20240319T152632.root");
  filenames.push_back("decoded_data_evb03_run12007_5_20240319T152732.root");
  filenames.push_back("decoded_data_evb03_run12007_6_20240319T152832.root");
  filenames.push_back("decoded_data_evb03_run12007_7_20240319T152933.root");
  filenames.push_back("decoded_data_evb03_run12007_8_20240319T153033.root");
  filenames.push_back("decoded_data_evb03_run12007_9_20240319T153134.root");

  TProfile2D *p2d = (TProfile2D*) new TProfile2D("rc","rmschanevt;chan;event",1000,-0.5,11263.5,2000,-0.5,1999.5);

  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {

    auto const& evaux = ev.eventAuxiliary();
    int runno = evaux.run();
    int subrunno = evaux.subRun();
    int eventno = evaux.event();

    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
        size_t nrawdigits = rawdigits.size();
	size_t nsamples = rawdigits[0].Samples();

	bool printed = false;
        for (size_t ichan=0;ichan<nrawdigits;++ichan)
          {
            size_t ic = rawdigits[ichan].Channel();
	    double rms = rawdigits[ichan].GetSigma();
	    p2d->Fill(ic,eventno,rms);
          }
      }  // end check if rawdigits are empty
  } // end loop over events
  TFile outfile("rmschanvent_12007.root","RECREATE");
  p2d->Write();
  outfile.Close();
}

