// printplots.C
// based on Stefan Schmitt's hadd.C in tutorials/io
// makes a single PDF file with 
// to execute non-interactively:  root -b -l -q 'printplots.C("rawtpcmonitor.root");'

#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include "TCanvas.h"
#include "stdio.h"
#include "TProfile.h"

TFile *Target;
TCanvas *c1;

int plotno = 0;

void mpa (TDirectory *dir);

void printplots(TString infile="adchistos_run10376.root")
{
  c1 = new TCanvas("c1","c1",1200,800);
  c1->Divide(3,2);
  plotno = 0;
  
  TFile *f = new TFile(infile,"READ");
  TDirectory *current_sourcedir = gDirectory;
  mpa(current_sourcedir);
  c1->Print("combhistos.pdf)");
}

void mpa(TDirectory *current_sourcedir)
{


  // loop over all keys in this directory
  TIter nextkey( current_sourcedir->GetListOfKeys() );
  TKey *key, *oldkey=0;
  while ( (key = (TKey*)nextkey())) 
    {
      //plot only the highest cycle number for each key
      if (oldkey && !strcmp(oldkey->GetName(),key->GetName())) continue;

      // read object from  source file
      TObject *obj = key->ReadObj();

      if ( obj->IsA()->InheritsFrom( TH1::Class() ) ) 
	{
	  // descendant of TH1 -> make a plot

	  TH1 *h1 = (TH1*)obj;

	  plotno++;
	  if (plotno == 7)
	    {
	      plotno = 1;
	      c1->Print("combhistos.pdf(");
	    }
	  c1->cd(plotno);
	  if (h1->GetNbinsY()==1)
	    {
	      h1->SetStats(true);
	      if (obj->IsA()->InheritsFrom( TProfile::Class() ) )
		{
		  h1->SetStats(false);
		} 
	      h1->Draw("hist,e0");
	    }
	  else
	    {
	      h1->SetStats(false);
	      h1->Draw("colz");
	    }
	}
      else if ( obj->IsA()->InheritsFrom( TDirectory::Class() ) ) 
	{
	  // it's a subdirectory

	  //cout << "Found subdirectory " << obj->GetName() << endl;

	  current_sourcedir->cd(obj->GetName());
	  TDirectory *subdir = gDirectory;
	  mpa(subdir);
	  current_sourcedir->cd("..");
	} 
      else 
	{

	  // object is of no type that we know or can handle
	  cout << "Unknown object type, name: "
	       << obj->GetName() << " title: " << obj->GetTitle() << endl;
	}
    }
}
