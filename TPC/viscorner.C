#include <TGraph2D.h>
#include <TString.h>
#include <TCanvas.h>
#include <Riostream.h>
#include <vector>
#include <iostream>
#include <TMath.h>
#include <TAnnotation.h>

// too lazy to encapsulate these -- global variables

const int nchans=11264;
int larsoftch[nchans];
int cryostat[nchans];
int tpc[nchans];
int plane[nchans];
int pwire[nchans];
double wx1[nchans];
double wy1[nchans];
double wz1[nchans];
double wx2[nchans];
double wy2[nchans];
double wz2[nchans];

void viscorner(int icorner=0);
void readfile(TString filename);
void viscorneraux(int itpc=0, double xlow=-210, double xhigh=-195, double ylow=-205, double yhigh=-195, double zlow=245, double zhigh=255);

void viscorner(int icorner)
{
  if (icorner == 0)
    {
      viscorneraux(0,-210,-195,-202,-195,4,10);
    }
  else if (icorner == 1)
    {
      viscorneraux(0,-210,-195,-205,-195,245,255);
    }
}

void viscorneraux(int itpc, double xlow, double xhigh, double ylow, double yhigh, double zlow, double zhigh)
{
  TCanvas *c1 = (TCanvas*) new TCanvas("c1","c1",1000,1000);

  readfile("sbndwireends.txt");
  
  // Loop through wire segments to see which ones have endpoints in the desired range

  auto gbound = new TGraph2D(4);
  gbound->SetPoint(0,zlow,xlow,ylow);
  gbound->SetPoint(1,zlow,xhigh,ylow);
  gbound->SetPoint(2,zlow,xhigh,yhigh);
  gbound->SetPoint(3,zhigh,xhigh,yhigh);
  gbound->GetXaxis()->SetTitle("Z");
  gbound->GetYaxis()->SetTitle("X");
  gbound->GetZaxis()->SetTitle("Y");
  gbound->GetXaxis()->CenterTitle();
  gbound->GetYaxis()->CenterTitle();
  gbound->GetZaxis()->CenterTitle();
  gbound->GetXaxis()->SetTitleOffset(1.8);
  gbound->GetYaxis()->SetTitleOffset(2.2);
  gbound->GetZaxis()->SetTitleOffset(1.2);
  gbound->GetXaxis()->SetTitleColor(4);
  gbound->GetYaxis()->SetTitleColor(4);
  gbound->GetZaxis()->SetTitleColor(4);
  gbound->SetTitle("");
  gbound->Draw("LINE");
  
  for (int i=0; i<nchans; ++i)
    {
      if (tpc[i] == itpc &&
	  ( (wy1[i] > ylow && wy1[i] < yhigh && wz1[i] > zlow && wz1[i] < zhigh) ||
	    (wy2[i] > ylow && wy2[i] < yhigh && wz2[i] > zlow && wz2[i] < zhigh) ) )
	{
	  double wirelength = TMath::Sqrt( TMath::Sq( wx1[i] - wx2[i] ) + TMath::Sq( wy1[i] - wy2[i] ) + TMath::Sq(wz1[i] - wz2[i] ));
	  std::cout << "chan: " << larsoftch[i] << " tpc:  " << tpc[i] << " plane: " << plane[i] << " (" << wx1[i] << " , " << wy1[i] << " , " << wz1[i] << " )   ( " << wx2[i] << " , " << wy2[i] << " , " << wz2[i] << " )   length = " << wirelength << std::endl;
	  auto g = new TGraph2D(2);
	  TString namestr;
	  namestr = i;
          g->SetName(namestr);
	  g->SetPoint(0,wz1[i],wx1[i],wy1[i]);
	  g->SetPoint(1,wz2[i],wx2[i],wy2[i]);
	  g->Draw("SAME,LINE");

	  auto ta1 = new TAnnotation(wz1[i],wx1[i],wy1[i],Form("%d",larsoftch[i]));
          ta1->SetTextFont(42);
          ta1->SetTextSize(0.01);
          ta1->Draw();

	  auto ta2 = new TAnnotation(wz2[i],wx2[i],wy2[i],Form("%d",larsoftch[i]));
          ta2->SetTextFont(42);
          ta2->SetTextSize(0.01);
          ta2->Draw();
	}
    }
}

void readfile(TString filename)
{
  ifstream infile;
  infile.open(filename);

  int ichan = 0;
  
  while (1) 
    {
      infile >> larsoftch[ichan] >> cryostat[ichan] >> tpc[ichan] >> plane[ichan] >> pwire[ichan] >> wx1[ichan] >> wy1[ichan] >> wz1[ichan] >> wx2[ichan] >> wy2[ichan] >> wz2[ichan];
      if (!infile.good()) break;
      ichan++;
    }
  if (ichan != nchans)
    {
      std::cout << "bad number of input channels: " << ichan << " != " << nchans << std::endl; 
    }
}
