#include "TH1F.h"
#include "TMath.h"

{
TH1F rmshist("rmshist","rmshist",100,1,3);

TH1F rmshistemptychans("rmshistemptychans","rmshistemptychans",100,1,3);

Events->Draw("raw::RawDigits_daq__TPCDECODER.obj.fSigma>>rmshist","raw::RawDigits_daq__TPCDECODER.obj.fPedestal<1000 && raw::RawDigits_daq__TPCDECODER.obj.fChannel != 10030 && raw::RawDigits_daq__TPCDECODER.obj.fChannel != 10833 && raw::RawDigits_daq__TPCDECODER.obj.fChannel != 5201 && raw::RawDigits_daq__TPCDECODER.obj.fChannel != 4398 && raw::RawDigits_daq__TPCDECODER.obj.fSigma<3");

Events->Draw("raw::RawDigits_daq__TPCDECODER.obj.fSigma>>rmshistemptychans","raw::RawDigits_daq__TPCDECODER.obj.fPedestal<1000 && (raw::RawDigits_daq__TPCDECODER.obj.fChannel == 10030 || raw::RawDigits_daq__TPCDECODER.obj.fChannel == 10833 || raw::RawDigits_daq__TPCDECODER.obj.fChannel == 5201 || raw::RawDigits_daq__TPCDECODER.obj.fChannel == 4398) && raw::RawDigits_daq__TPCDECODER.obj.fSigma<3");

 double crms = rmshist.GetMean();
 double dcrms = rmshist.GetRMS();
 dcrms /= TMath::Sqrt(rmshist.GetEntries());
 double erms = rmshistemptychans.GetMean(); 
 double derms = rmshistemptychans.GetRMS();
 derms /= TMath::Sqrt(rmshistemptychans.GetEntries()); 
 
 double ddiff = TMath::Sqrt(TMath::Max(0.0, TMath::Sq(crms) - TMath::Sq(erms)));
 double dddiff = (1.0/(2.0*ddiff))*TMath::Sqrt( TMath::Sq(2.0*crms*dcrms) + TMath::Sq(2.0*erms*derms) );
 
 std::cout << "Noise Y chans: " << crms << " +- " << dcrms << " ADC counts" << std::endl;
 std::cout << "Noise disconnected Y chans: " << erms << " +- " << derms << " ADC counts" << std::endl;
 std::cout << "Quadrature diff: " << ddiff << " +- " << dddiff << " ADC counts" << std::endl;
 
}
