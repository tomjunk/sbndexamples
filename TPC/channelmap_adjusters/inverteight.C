// invert groups of eight FEMCh numbers

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
  
  std::string fullname("SBNDTPCChannelMap_v1_orig.txt");
			     
  //  std::cout << "SBND TPC Channel Map: Building TPC wiremap from file " << fullname << std::endl;
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

    int j = c.FEMCh / 8;
    int invfemch = 8*(j + 1) - (c.FEMCh % 8) - 1;
    
    std::cout 
      << c.wireno
      << " " << planestr
      << " " << c.EastWest
      << " " << c.NorthSouth
      << " " << c.SideTop
      << " " << c.FEMBPosition
      << " " << c.FEMBSerialNum
      << " " << c.FEMBOnWIB
      << " " << c.FEMBCh
      << " " << c.asic
      << " " << c.WIBCrate
      << " " << c.WIB
      << " " << c.WIBCh 
      << " " << qfspstr 
      << " " << c.QFSPFiber 
      << " " << c.FEMCrate
      << " " << c.FEM
      << " " << invfemch
      << " " << c.offlchan
      << std::endl;
      
  }
  inFile.close();
  
}
