#ifndef VolumeHeader_h
#define VolumeHeader_h

#include <iostream>
#include <cstring>

using namespace std;

class Volume_Header
{
public:
	// serial number of the sector
	unsigned int sectorNr;
	unsigned int ClusQty;
	unsigned int dataClusQty;
	unsigned int addrDAT;
	unsigned int addrRootDir;
	unsigned int addrDATcpy;
	unsigned int addrRootDircpy;
	unsigned int addrDataStart;

	char prodDate[11]{'\0'};
	char formatDate[11]{'\0'};
	char diskName[12];
	char diskOwner[12];
	char emptyArea[942]{ '\0' };

	bool isFormated;

	Volume_Header();
	Volume_Header & operator = (const Volume_Header & vhd_temp);
	void setVolumeheader(unsigned int sectorNr, const char diskName[12], const char diskOwner[12], char prodDate[10], unsigned int ClusQty, unsigned int dataClusQty, unsigned int addrDAT,
		unsigned int addrRootDir, unsigned int addrRootDirCpy, unsigned int addrDATcpy, unsigned int addrDataStart, char formatDate[10], bool isformated);
	
};



#endif /* VolumeHeader_h */
