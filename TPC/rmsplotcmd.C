void rmsplotcmd()
{
  TProfile* rmschan = (TProfile*) new TProfile("rmschan",";Channel;RMS [ADC]",11264,-0.5,11263.5);
  Events->Draw("raw::RawDigits_daq__TPCDECODER.obj.fSigma:raw::RawDigits_daq__TPCDECODER.obj.fChannel>>rmschan","raw::RawDigits_daq__TPCDECODER.obj.fSigma<4");
  rmschan->Draw("hist");
}
