#include "RootDir.h"



RootDir & RootDir::operator=(const RootDir & temp)
{
	this->msbSector.sectorNr = temp.msbSector.sectorNr;
	this->lsbSector.sectorNr = temp.msbSector.sectorNr;
	return *this;

}
