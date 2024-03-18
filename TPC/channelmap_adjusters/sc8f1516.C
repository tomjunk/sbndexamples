// Swap FEMs 15 and 16 in FEM Crate 8

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>

typedef struct ChanInfo {
  unsigned int wireno;          // wire number
  std::string  plane;           // U, V, Y
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
  std::string  WIBQFSP;         // DAQ1 or DAQ2
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

  // start with the once-modified map
  
  std::string fullname("SBNDTPCChannelMap_v1_3rot_3264.txt");
			     
  //  std::cout << "SBND TPC Channel Map: Building TPC wiremap from file " << fullname << std::endl;
  std::ifstream inFile(fullname, std::ios::in);
  std::string line;

  while (std::getline(inFile,line)) {
    std::stringstream linestream(line);
    
    ChanInfo_t c;
    linestream 
      >> c.wireno
      >> c.plane
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
      >> c.WIBQFSP 
      >> c.QFSPFiber 
      >> c.FEMCrate
      >> c.FEM
      >> c.FEMCh
      >> c.offlchan;

    civec.push_back(c);
  }
  inFile.close();

  for (const auto &c : civec)
    {
      ChanInfo_t cs = c;

      if (c.FEMCrate == 8)
	{
	  if (c.FEM == 16) cs.FEM = 15;
	  if (c.FEM == 15) cs.FEM = 16;
	}

      // print out adjusted info
      
      std::cout 
	<< cs.wireno
	<< " " << cs.plane
	<< " " << cs.EastWest
	<< " " << cs.NorthSouth
	<< " " << cs.SideTop
	<< " " << cs.FEMBPosition
	<< " " << cs.FEMBSerialNum
	<< " " << cs.FEMBOnWIB
	<< " " << cs.FEMBCh
	<< " " << cs.asic
	<< " " << cs.WIBCrate
	<< " " << cs.WIB
	<< " " << cs.WIBCh 
	<< " " << cs.WIBQFSP 
	<< " " << cs.QFSPFiber 
	<< " " << cs.FEMCrate
	<< " " << cs.FEM
	<< " " << cs.FEMCh
	<< " " << cs.offlchan
	<< std::endl;
    }  
}
