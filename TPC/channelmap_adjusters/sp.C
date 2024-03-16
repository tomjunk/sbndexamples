#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdlib.h>

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

int main(int argc, char **argv)
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
  
  std::cout << sizeof(ChanInfo_t) << " " << 11264*sizeof(ChanInfo_t) << std::endl;
  ChanInfo_t c;
  c.EastWest = "East";
  c.NorthSouth = "North";
  c.SideTop = "T";
  c.FEMBPosition = "A15";
  c.FEMBSerialNum = "S20";

  std::cout << sizeof(c) << " " << 11264*sizeof(c) << std::endl;
  std::cout << sizeof(std::string) << std::endl;

  for (size_t j=0; j<10000; ++j)
    {
      for (size_t i=0; i<11264; ++i)
	{
	  auto ci = GetChanInfoFromOfflChan(i);
	  auto ci2 = GetChanInfoFromFEMElements(ci.FEMCrate, ci.FEM, ci.FEMCh);
	  if (ci2.offlchan != i)
	    {
	      std::cout << "map inconsistency: " << i << " " << ci2.offlchan << std::endl;
	    }
	}
    }
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
