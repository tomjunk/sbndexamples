// macro to draw CNR FFTs overlaid

#include <string.h>
#include "TFile.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TString.h"

void plotfftcnr(TString infilename="fftcnr.root")
{
  TFile infile(infilename); 
  TCanvas* c1 = new TCanvas("c1","c1",1200,800);
  c1->Divide(3,2);

  c1->cd(1);
  auto h1 = (TProfile*) infile.Get("eufft");
  auto h2 = (TProfile*) infile.Get("eufftcnr");
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h1->SetStats(false);
  h2->SetStats(false);
  h1->Draw("hist");
  h2->Draw("hist,same");

  c1->cd(2);
  h1 = (TProfile*) infile.Get("evfft");
  h2 = (TProfile*) infile.Get("evfftcnr");
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h1->SetStats(false);
  h2->SetStats(false);
  h1->Draw("hist");
  h2->Draw("hist,same");

  c1->cd(3);
  h1 = (TProfile*) infile.Get("eyfft");
  h2 = (TProfile*) infile.Get("eyfftcnr");
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h1->SetStats(false);
  h2->SetStats(false);
  h1->Draw("hist");
  h2->Draw("hist,same");

  c1->cd(4);
  h1 = (TProfile*) infile.Get("wufft");
  h2 = (TProfile*) infile.Get("wufftcnr");
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h1->SetStats(false);
  h2->SetStats(false);
  h1->Draw("hist");
  h2->Draw("hist,same");

  c1->cd(5);
  h1 = (TProfile*) infile.Get("wvfft");
  h2 = (TProfile*) infile.Get("wvfftcnr");
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h1->SetStats(false);
  h2->SetStats(false);
  h1->Draw("hist");
  h2->Draw("hist,same");

  c1->cd(6);
  h1 = (TProfile*) infile.Get("wyfft");
  h2 = (TProfile*) infile.Get("wyfftcnr");
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h1->SetStats(false);
  h2->SetStats(false);
  h1->Draw("hist");
  h2->Draw("hist,same");
  
  c1->Print("fftcnrcompare.pdf");
}
