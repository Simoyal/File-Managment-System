#ifdef _MSC_VER
#define  _CRT_SECURE_NO_WARNINGS 1
#endif 

#include "VolumeHeader.h"
#include <cstring>
#include <ctime>
#include "Help.h"

using namespace std;

Volume_Header::Volume_Header()
{
	sectorNr = 0;
	ClusQty = 0;
	dataClusQty = 0;
	addrDAT = 0;
	addrDATcpy = 0;
	addrRootDircpy = 0;
	addrRootDir = 0;
	addrDataStart = 0;
	isFormated = false;
	
}

void Volume_Header::setVolumeheader(unsigned int sectorNr, const char diskName[11], const char diskOwner[11],  char prodDate[10], unsigned int ClusQty, unsigned int dataClusQty, unsigned int addrDAT,
	unsigned int addrRootDir, unsigned int addrRootDirCpy, unsigned int addrDATcpy, unsigned int addrDataStart, char formatDate[10], bool isformated)
{
	this->sectorNr = sectorNr;
	strcpy(this->diskName, diskName);
	strcpy(this->diskOwner, diskOwner);
	DateNow(this->prodDate);
	this->prodDate[10] = '\0';
	this->ClusQty = ClusQty;
	this->dataClusQty = dataClusQty;
	this->addrDAT = addrDAT;
	this->addrRootDir = addrRootDir;
	this->addrRootDircpy = addrRootDirCpy;
	this->addrDATcpy = addrDATcpy;
	this->addrDataStart = addrDataStart;
	isFormated = isformated;
}

Volume_Header & Volume_Header::operator=(const Volume_Header & vhd_temp)
{
	this->addrDAT = vhd_temp.addrDAT;
	this->addrDataStart = vhd_temp.addrDataStart;
	this->addrDATcpy = vhd_temp.addrDATcpy;
	this->addrRootDir = vhd_temp.addrRootDir;
	this->addrRootDircpy = vhd_temp.addrRootDircpy;
	this->ClusQty = vhd_temp.dataClusQty;
	this->dataClusQty = vhd_temp.dataClusQty;
	this->isFormated = vhd_temp.isFormated;
	strcpy(this->prodDate, vhd_temp.prodDate);
	this->sectorNr = vhd_temp.sectorNr;
	return *this;
}
