#include <TGraph.h>
#include <TString.h>
#include <TCanvas.h>
#include <Riostream.h>
#include <vector>
#include <iostream>
#include <TMath.h>

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"

#include "TFile.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TVectorT.h"
#include "lardataobj/RawData/RawDigit.h"
#include "TLegend.h"
#include "Riostream.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TPaveStats.h"

// too lazy to encapsulate these global variables

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

typedef struct ChanInfo {
  unsigned int wireno;          // wire number
  unsigned int plane;           // 0: U,  1: V,  2: Y
  std::string  EastWest;        // "East" or "West"
  std::string  NorthSouth;      // "North" or "South"
  std::string  SideTop;         // "T" or "S"
  std::string  FEMBPosition;    // e.g. "A10"
  std::string  FEMBSerialNum;   // Serial number.  Some contain letters
  unsigned int FEMBOnWIB;       // 0:3
  unsigned int FEMBCh;          // channel on FEMB -- 0:127
  unsigned int asic;            // 0:7
  unsigned int asicchan;        // ASIC channel:  0 to 15
  unsigned int WIBCrate;        // 1:4
  unsigned int WIB;             // 1:6
  unsigned int WIBCh;           // 0:895   (7 FEMBs)
  unsigned int WIBQFSP;         // 1:2
  unsigned int QFSPFiber;       // 1:4
  unsigned int FEMCrate;        // 1:11
  unsigned int FEM;             // 1:16
  unsigned int FEMCh;           // 0:63 channel in a FEM
  unsigned int offlchan;        // in gdml and channel sorting convention
  bool valid;          // true if valid, false if not
} ChanInfo_t;

ChanInfo_t GetChanInfoFromFEMElements(
				      unsigned int femcrate,
				      unsigned int fem,
				      unsigned int femchan);

ChanInfo_t GetChanInfoFromOfflChan(unsigned int offlchan);

// look up channel info by offline channel number
  
std::unordered_map<unsigned int, ChanInfo_t> fChanInfoFromOfflChan;

// look up channel info by FEMCrate, FEM, and FEMCh
  
std::unordered_map<unsigned int,
		   std::unordered_map<unsigned int,
				      std::unordered_map< unsigned int, ChanInfo_t > > > fChanInfoFromFEMInfo;

void readchanmapfile();

double calcwirelen(int ic)
{
  return TMath::Sqrt( TMath::Sq(wx1[ic] - wx2[ic]) +
		      TMath::Sq(wy1[ic] - wy2[ic]) +
		      TMath::Sq(wz1[ic] - wz2[ic]) );
}

using namespace art;
using namespace std;

void readgeomfile(TString filename="sbndwireends.txt");

void rmsvswirelen(std::string filename="tpcdecode_data_evb03_run11505_24_20240304T182922.root", bool cnr=true, int debuglevel=0)
{
  readgeomfile();
  readchanmapfile();
  
  TGraph *rgraph = (TGraph*) new TGraph();
  TGraph *rgraphq = (TGraph*) new TGraph();
  TGraph *rgraphqe = (TGraph*) new TGraph();
  TGraph *rgraphqw = (TGraph*) new TGraph();
  TGraph *rgraphqeu = (TGraph*) new TGraph();
  TGraph *rgraphqwu = (TGraph*) new TGraph();
  TGraph *rgraphqev = (TGraph*) new TGraph();
  TGraph *rgraphqwv = (TGraph*) new TGraph();

  TGraph *rgraphcnr = (TGraph*) new TGraph();
  TGraph *rgraphecnr = (TGraph*) new TGraph();
  TGraph *rgraphwcnr = (TGraph*) new TGraph();
  TGraph *rgrapheucnr = (TGraph*) new TGraph();
  TGraph *rgraphwucnr = (TGraph*) new TGraph();
  TGraph *rgraphevcnr = (TGraph*) new TGraph();
  TGraph *rgraphwvcnr = (TGraph*) new TGraph();

  TGraph *qrgraphcnr = (TGraph*) new TGraph();
  TGraph *qrgraphecnr = (TGraph*) new TGraph();
  TGraph *qrgraphwcnr = (TGraph*) new TGraph();
  TGraph *qrgrapheucnr = (TGraph*) new TGraph();
  TGraph *qrgraphwucnr = (TGraph*) new TGraph();
  TGraph *qrgraphevcnr = (TGraph*) new TGraph();
  TGraph *qrgraphwvcnr = (TGraph*) new TGraph();
  
  TH1F *yrms = (TH1F*) new TH1F("yrms","Y Wire RMS",100,0,4);
  TH1F *yrmscnr = (TH1F*) new TH1F("cnryrms","CNR Y Wire RMS",100,0,4);
  TH1F *urms = (TH1F*) new TH1F("urms","U Wire RMS",100,0,4);
  TH1F *urmscnr = (TH1F*) new TH1F("cnrurms","CNR U Wire RMS",100,0,4);
  TH1F *vrms = (TH1F*) new TH1F("vrms","V Wire RMS",100,0,4);
  TH1F *vrmscnr = (TH1F*) new TH1F("cnrvrms","CNR V Wire RMS",100,0,4);

  TH1D *yadcminusmed = (TH1D*) new TH1D("yadcminusmed","Y Wires;ADC-median",41,-20.5,20.5);
  TH1D *uadcminusmed = (TH1D*) new TH1D("uadcminusmed","U Wires;ADC-median",41,-20.5,20.5);
  TH1D *vadcminusmed = (TH1D*) new TH1D("vadcminusmed","V Wires;ADC-median",41,-20.5,20.5);
  
  TCanvas *rcanvas = (TCanvas*) new TCanvas("c1","",1500,1100);
  rgraph->SetTitle("Wire Noise vs. Wire Length;Wire Length [cm];RMS [ADC counts]");
  rgraphq->SetTitle("Quad Diff Wire Noise - Discon Wire Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  rgraphqe->SetTitle("East Wires Quad Diff Noise - Discon Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  rgraphqw->SetTitle("West Wires Quad Diff Wire Noise - Discon Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  rgraphqeu->SetTitle("East U Wires Quad Diff Noise - Discon Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  rgraphqwu->SetTitle("West U Wires Quad Diff Noise - Discon Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  rgraphqev->SetTitle("East V Wires Quad Diff Noise - Discon Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  rgraphqwv->SetTitle("West V Wires Quad Diff Noise - Discon Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");

  rgraphcnr->SetTitle("CNR Noise vs. Wire Length;Wire Length [cm];RMS [ADC counts]");
  rgraphecnr->SetTitle("CNR East Noise vs. Wire Length;Wire Length [cm]; RMS [ADC counts]");
  rgraphwcnr->SetTitle("CNR West Noise vs. Wire Length;Wire Length [cm]; RMS [ADC counts]");
  rgrapheucnr->SetTitle("CNR East U Noise vs. Wire Length;Wire Length [cm]; RMS [ADC counts]");
  rgraphwucnr->SetTitle("CNR West U Noise vs. Wire Length;Wire Length [cm]; RMS [ADC counts]");
  rgraphevcnr->SetTitle("CNR East V Noise vs. Wire Length;Wire Length [cm]; RMS [ADC counts]");
  rgraphwvcnr->SetTitle("CNR West V Noise vs. Wire Length;Wire Length [cm]; RMS [ADC counts]");

  qrgraphcnr->SetTitle("Quad Diff CNR Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  qrgraphecnr->SetTitle("Quad Diff CNR East Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  qrgraphwcnr->SetTitle("Quad Diff CNR West Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  qrgrapheucnr->SetTitle("Quad Diff CNR East U Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  qrgraphwucnr->SetTitle("Quad DiffCNR West U Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  qrgraphevcnr->SetTitle("Quad Diff CNR East V Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  qrgraphwvcnr->SetTitle("Quad Diff CNR West V Noise vs. Wire Length;Wire Length [cm];Quad Diff RMS [ADC counts]");
  
  InputTag rawdigit_tag{ "daq" };
  vector<string> filenames(1, filename);

  int ievent = 0;
  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) {
    auto const& rawdigits = *ev.getValidHandle<vector<raw::RawDigit>>(rawdigit_tag);
    if (!rawdigits.empty())
      {
	ievent++;
	const size_t nrawdigits = rawdigits.size();

	// compute average noise on disconnected channels
	
	double avgdiscon = 0;
	int ndiscon = 0;
	for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	  { 
	    size_t ic = rawdigits[ichan].Channel();
	    double rms = rawdigits[ichan].GetSigma();
	    if (ic >= nchans) continue;
	    if ( (ic>=3968 && ic<5632) || (ic>=9600))
	      {
		yrms->Fill(rms);
	      }
	    else if ( (ic<1984) || (ic>=5632 && ic<7616))
	      {
		urms->Fill(rms);
	      }
	    else
	      {
		vrms->Fill(rms);
	      }
	    double wirelen = calcwirelen(ic);
	    rgraph->AddPoint(wirelen,rms);  // raw RMS value
	    if (ic == 10030 || ic == 10833 || ic == 5201 || ic == 4398)
	      {
		ndiscon++;
		avgdiscon += rms;
	      }
	  }
	if (ndiscon>0)
	  {
	    avgdiscon /= ((double) ndiscon);
	  }


	// make a big map of median ADC values for each plane and FEMB for each tick.
	// for correlated noise removing
	// first index -- femb, second index, plane, third index: tick

	unordered_map<int, unordered_map<int, unordered_map<int, int>>> medianmap;
	size_t nticks = rawdigits.at(0).Samples();

	if (cnr)
	  {    
	    for (size_t itick=0; itick<nticks; ++itick)
	      {
		// on this tick, make a map of ADC vectors, one per FEMB per plane
		unordered_map<int, unordered_map<int, vector<int>>> adcvmap;
	    
		for (size_t ichan=0; ichan<nrawdigits; ++ichan)
		  {
		    unsigned int ic = rawdigits[ichan].Channel();
		    auto ci = GetChanInfoFromOfflChan(ic);
		    int fembident = 100*ci.WIBCrate + 10*ci.WIB + ci.FEMBOnWIB;
		    // to do -- remove ROIs with signals
		    adcvmap[fembident][ci.plane].push_back(rawdigits[ichan].ADC(itick) - rawdigits[ichan].GetPedestal());
		  }
		for (const auto& fp : adcvmap)  // loop over FEMBs
		  {
		    for (const auto& pp : fp.second)  // loop over planes
		      {
			int adcmed = TMath::Median(pp.second.size(),pp.second.data());
			medianmap[fp.first][pp.first][itick] = adcmed;
			if (debuglevel>1)
			  {
			    cout << "Median on FEMBID: " << fp.first << " Plane: " << pp.first << " Tick: " << itick << " " << adcmed << endl; 
			  }
		      }
		  }
	      }
	  }

	// non-CNR subtracted RMS values
	
	for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	  { 
	    size_t ic = rawdigits[ichan].Channel();
	    double rms = rawdigits[ichan].GetSigma();
	    if (ic >= nchans) continue;
	    double wirelen = calcwirelen(ic);
	    double qdn = TMath::Sqrt(TMath::Max(0.0,rms*rms - avgdiscon*avgdiscon));
	    rgraphq->AddPoint(wirelen,qdn);
	    ((ic < 5632) ? rgraphqe : rgraphqw)->AddPoint(wirelen,qdn);
	    if (ic<1984)
	      {
		rgraphqeu->AddPoint(wirelen,qdn);
	      }
	    else if (ic < 3968)
	      {
		rgraphqev->AddPoint(wirelen,qdn);
	      }
	    else if (ic < 5632)
	      {
	      }
	    else if (ic < 7616)
	      {
		rgraphqwu->AddPoint(wirelen,qdn);
	      }
	    else if (ic < 9600)
	      {
		rgraphqwv->AddPoint(wirelen,qdn);
	      }	      
	  }  // end loop over channels -- non CNR plot making


	// make CNR-subtracted RMS plots

	if (cnr)
	  {
	    unordered_map<unsigned int, double> rmsvalmap;
	    
	    for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	      { 
		unsigned int ic = rawdigits[ichan].Channel();
		auto ci = GetChanInfoFromOfflChan(ic);
		int fembident = 100*ci.WIBCrate + 10*ci.WIB + ci.FEMBOnWIB;  // must match definition above
		int iplane = ci.plane;
		std::vector<int> adcsub;
		for (size_t itick=0; itick<nticks; ++itick)
		  {
		    adcsub.push_back(rawdigits[ichan].ADC(itick) - rawdigits[ichan].GetPedestal() - medianmap[fembident][iplane][itick]);
		    if (debuglevel > 1)
		      {
			if (ievent == 1 && ic == 1000)
			  {
			    cout << "debug chan 1000: " << itick << " " << adcsub.back() << " " << medianmap[fembident][iplane][itick] << endl;
			  }
		      }

		    if (iplane == 0)
		      {
			uadcminusmed->Fill(adcsub.back());
		      }
		    else if (iplane == 1)
		      {
			vadcminusmed->Fill(adcsub.back());
		      }
		    else
		      {
			yadcminusmed->Fill(adcsub.back());
		      }
		  }
		double rmsval = TMath::RMS(adcsub.size(),adcsub.data());
		rmsvalmap[ic] = rmsval;
	      }
	    double avgdisconrms = (rmsvalmap[10030] + rmsvalmap[10833] + rmsvalmap[5201] + rmsvalmap[4398])/4.0;
	    
	    for (size_t ichan=0;ichan<nrawdigits; ++ichan) 
	      { 	    
		unsigned int ic = rawdigits[ichan].Channel();
		double rmsval = rmsvalmap[ic];
		double qsubrmsval = TMath::Sqrt(TMath::Max(0.0,rmsval*rmsval - avgdisconrms*avgdisconrms));
		
	        if ( (ic>=3968 && ic<5632) || (ic>=9600))
	          {
		    yrmscnr->Fill(rmsval);
	          }
		else if ( (ic<1984) || (ic>=5632 && ic<7616))
		  {
		    urmscnr->Fill(rmsval);
		  }
		else
		  {
		    vrmscnr->Fill(rmsval);
		  }

	        double wirelen = calcwirelen(ic);
		
		rgraphcnr->AddPoint(wirelen,rmsval);
		qrgraphcnr->AddPoint(wirelen,rmsval);
		((ic < 5632) ? rgraphecnr : rgraphwcnr)->AddPoint(wirelen,rmsval);
		((ic < 5632) ? qrgraphecnr : qrgraphwcnr)->AddPoint(wirelen,qsubrmsval);
		if (ic<1984)
		  {
		    rgrapheucnr->AddPoint(wirelen,rmsval);
		    qrgrapheucnr->AddPoint(wirelen,qsubrmsval);
		  }
		else if (ic < 3968)
		  {
		    rgraphevcnr->AddPoint(wirelen,rmsval);
		    qrgraphevcnr->AddPoint(wirelen,qsubrmsval);
		  }
		else if (ic < 5632)
		  {
		  }
		else if (ic < 7616)
		  {
		    rgraphwucnr->AddPoint(wirelen,rmsval);
		    qrgraphwucnr->AddPoint(wirelen,qsubrmsval);
		  }
		else if (ic < 9600)
		  {
		    rgraphwvcnr->AddPoint(wirelen,rmsval);
		    qrgraphwvcnr->AddPoint(wirelen,qsubrmsval);
		  }	      

	      }
	  }
      }  // end check for empty raw digits
  } // end loop over events

  
  rgraph->SetMinimum(0);
  rgraph->SetMaximum(4);
  rgraph->Draw("AP");
  rcanvas->Print("rmsvswirelen.png");

  rgraphq->SetMinimum(0);
  rgraphq->SetMaximum(4);
  rgraphq->Draw("AP");
  rcanvas->Print("rmsvswirelen_quaddiff.png");

  rgraphqe->SetMinimum(0);
  rgraphqe->SetMaximum(4);
  rgraphqe->Draw("AP");
  rcanvas->Print("eastrmsvswirelen_quaddiff.png");

  rgraphqw->SetMinimum(0);
  rgraphqw->SetMaximum(4);
  rgraphqw->Draw("AP");
  rcanvas->Print("westrmsvswirelen_quaddiff.png");

  rgraphqeu->SetMinimum(0);
  rgraphqeu->SetMaximum(4);
  rgraphqeu->Draw("AP");
  rcanvas->Print("eastUrmsvswirelen_quaddiff.png");

  rgraphqwu->SetMinimum(0);
  rgraphqwu->SetMaximum(4);
  rgraphqwu->Draw("AP");
  rcanvas->Print("westUrmsvswirelen_quaddiff.png");

  rgraphqev->SetMinimum(0);
  rgraphqev->SetMaximum(4);
  rgraphqev->Draw("AP");
  rcanvas->Print("eastVrmsvswirelen_quaddiff.png");

  rgraphqwv->SetMinimum(0);
  rgraphqwv->SetMaximum(4);
  rgraphqwv->Draw("AP");
  rcanvas->Print("westVrmsvswirelen_quaddiff.png");

  yrms->SetLineColor(1);
  yrmscnr->SetLineColor(2);
  yrmscnr->Draw("hist");
  yrms->Draw("hist,SAMES");
  rcanvas->Print("yrmscnr.png");

  urms->SetLineColor(1);
  urmscnr->SetLineColor(2);
  urmscnr->Draw("hist");
  urms->Draw("hist,SAMES");
  rcanvas->Print("urmscnr.png");

  vrms->SetLineColor(1);
  vrmscnr->SetLineColor(2);
  vrmscnr->Draw("hist");
  vrms->Draw("hist,SAMES");
  rcanvas->Print("vrmscnr.png");

  yadcminusmed->Draw("hist");
  rcanvas->Print("yadcminusmed.png");
  uadcminusmed->Draw("hist");
  rcanvas->Print("uadcminusmed.png");
  vadcminusmed->Draw("hist");
  rcanvas->Print("vadcminusmed.png");

  rgraphcnr->SetMinimum(0);
  rgraphcnr->SetMaximum(4);
  rgraphcnr->Draw("AP");
  rcanvas->Print("rmsvswirelen_cnr.png");
  
  rgraphecnr->SetMinimum(0);
  rgraphecnr->SetMaximum(4);
  rgraphecnr->Draw("AP");
  rcanvas->Print("rmsvswireleneast_cnr.png");

  rgrapheucnr->SetMinimum(0);
  rgrapheucnr->SetMaximum(4);
  rgrapheucnr->Draw("AP");
  rcanvas->Print("rmsvswireleneastU_cnr.png");

  rgraphevcnr->SetMinimum(0);
  rgraphevcnr->SetMaximum(4);
  rgraphevcnr->Draw("AP");
  rcanvas->Print("rmsvswireleneastV_cnr.png");
  
  rgraphwcnr->SetMinimum(0);
  rgraphwcnr->SetMaximum(4);
  rgraphwcnr->Draw("AP");
  rcanvas->Print("rmsvswirelenwest_cnr.png");

  rgraphwucnr->SetMinimum(0);
  rgraphwucnr->SetMaximum(4);
  rgraphwucnr->Draw("AP");
  rcanvas->Print("rmsvswirelenwestU_cnr.png");

  rgraphwvcnr->SetMinimum(0);
  rgraphwvcnr->SetMaximum(4);
  rgraphwvcnr->Draw("AP");
  rcanvas->Print("rmsvswirelenwestV_cnr.png");

  qrgraphcnr->SetMinimum(0);
  qrgraphcnr->SetMaximum(4);
  qrgraphcnr->Draw("AP");
  rcanvas->Print("qdiffrmsvswirelen_cnr.png");
  
  qrgraphecnr->SetMinimum(0);
  qrgraphecnr->SetMaximum(4);
  qrgraphecnr->Draw("AP");
  rcanvas->Print("qdiffrmsvswireleneast_cnr.png");

  qrgrapheucnr->SetMinimum(0);
  qrgrapheucnr->SetMaximum(4);
  qrgrapheucnr->Draw("AP");
  rcanvas->Print("qdiffrmsvswireleneastU_cnr.png");

  qrgraphevcnr->SetMinimum(0);
  qrgraphevcnr->SetMaximum(4);
  qrgraphevcnr->Draw("AP");
  rcanvas->Print("qdiffrmsvswireleneastV_cnr.png");
  
  qrgraphwcnr->SetMinimum(0);
  qrgraphwcnr->SetMaximum(4);
  qrgraphwcnr->Draw("AP");
  rcanvas->Print("qdiffrmsvswirelenwest_cnr.png");

  qrgraphwucnr->SetMinimum(0);
  qrgraphwucnr->SetMaximum(4);
  qrgraphwucnr->Draw("AP");
  rcanvas->Print("qdiffrmsvswirelenwestU_cnr.png");

  qrgraphwvcnr->SetMinimum(0);
  qrgraphwvcnr->SetMaximum(4);
  qrgraphwvcnr->Draw("AP");
  rcanvas->Print("qdiffrmsvswirelenwestV_cnr.png");
  

}

void readgeomfile(TString filename)
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


void readchanmapfile()
{
  std::string fullname("SBNDTPCChannelMap_v1.txt");
			     
  std::cout << "SBND TPC Channel Map: Building TPC wiremap from file " << fullname << std::endl;
  std::ifstream inFile(fullname, std::ios::in);
  std::string line;

  while (std::getline(inFile,line)) {
    std::stringstream linestream(line);
    std::string planestr;
    std::string qfspstr;
    
    ChanInfo_t c;
    linestream 
      >> c.wireno
      >> planestr
      >> c.EastWest
      >> c.NorthSouth
      >> c.SideTop
      >> c.FEMBPosition
      >> c.FEMBSerialNum
      >> c.FEMBOnWIB
      >> c.FEMBCh
      >> c.asic
      >> c.WIBCrate
      >> c.WIB
      >> c.WIBCh 
      >> qfspstr 
      >> c.QFSPFiber 
      >> c.FEMCrate
      >> c.FEM
      >> c.FEMCh
      >> c.offlchan;

    c.valid = true;
    c.plane = 10;
    if (planestr == "U") c.plane = 0;
    if (planestr == "V") c.plane = 1;
    if (planestr == "Y") c.plane = 2;
    if (c.plane == 10) c.valid = false;
    c.WIBQFSP = atoi(qfspstr.substr(3,1).c_str());

    fChanInfoFromFEMInfo[c.FEMCrate][c.FEM][c.FEMCh] = c;
    fChanInfoFromOfflChan[c.offlchan] = c;
  }
  inFile.close();
}



ChanInfo_t GetChanInfoFromFEMElements(unsigned int femcrate,
				      unsigned int fem,
				      unsigned int femchan) {

  ChanInfo_t badinfo{};
  badinfo.valid = false;

  // look up one map at a time in order to handle cases where the item is not found
  // without throwing and catching exception which can make debugging hard
  
  auto fm1 = fChanInfoFromFEMInfo.find(femcrate);
  if (fm1 == fChanInfoFromFEMInfo.end()) {
    unsigned int substituteCrate = 1;  // a hack -- ununderstood crates get mapped to crate 1
    fm1 = fChanInfoFromFEMInfo.find(substituteCrate);
    if (fm1 == fChanInfoFromFEMInfo.end()) {
      return badinfo;
    }
  }
  auto& m1 = fm1->second;
  auto fm2 = m1.find(fem);
  if (fm2 == m1.end()) return badinfo;
  auto& m2 = fm2->second;
  auto fm3 = m2.find(femchan);
  if (fm3 == m2.end()) return badinfo;    
  return fm3->second;
}


ChanInfo_t GetChanInfoFromOfflChan(unsigned int offlineChannel) {
  ChanInfo_t badinfo{};
  badinfo.valid = false;
  auto fm = fChanInfoFromOfflChan.find(offlineChannel);
  if (fm == fChanInfoFromOfflChan.end()) return badinfo;
  return fm->second;
}
