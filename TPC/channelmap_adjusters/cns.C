// check Nupur's channel map file against the BNL version

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>

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


int main(int argc, char **argv)
{

  std::vector<ChanInfo_t> civec;
  
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

    civec.push_back(c);
  }
  inFile.close();
  
  std::string bnlfilename("SBND_mapping.dat");
  std::ifstream bnlFile(bnlfilename, std::ios::in);

  while (std::getline(bnlFile,line)) {
    //std::cout << line << std::endl;
    std::stringstream linestream(line);
    std::string apastr;
    std::string cratestr;
    std::string fembstr;
    std::string positionstr;
    std::string wibconnectionstr;
    int crate=0;
    int wib=0;
    int fembloc=0;
    int fembch=0;
    std::string wire_type;
    int wireno;
    
    linestream 
      >> apastr
      >> cratestr
      >> fembstr
      >> positionstr
      >> wibconnectionstr
      >> crate
      >> wib
      >> fembloc
      >> fembch
      >> wire_type
      >> wireno;

    int iplane=0;
    if (wire_type == "U") iplane = 0;
    if (wire_type == "V") iplane = 1;
    if (wire_type == "Y") iplane = 2;

    // dig through civec looking for a matching channel

    //std::cout << "looking for channel: "  << crate << " " << wib << " " << fembloc << " " << fembch << std::endl;

    bool found = false;
    for (const auto& ci : civec)
      {
	if (ci.WIBCrate == crate && ci.WIB == wib && ci.FEMBOnWIB == fembloc && ci.FEMBCh == fembch)
	  {
	    found = true;
	    if (wireno != ci.wireno)
	      {
	        std::cout << "Matching channel: " << crate << " " << wib << " " << fembloc << " " << fembch << std::endl;
	        std::cout << wireno << " " << ci.wireno << " " << ci.offlchan << std::endl;
	      }
	  }
      }
    if (!found)
      {
	std::cout << "Channel not found in spreadsheet: " << crate << " " << wib << " " << fembloc << " " << fembch << std::endl;
      }
  }
  bnlFile.close();
  
}
