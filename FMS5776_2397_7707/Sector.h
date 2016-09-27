#ifndef Sector_h
#define Sector_h

#include "DAT.h"

class Sector
{
public:
	// serial number of the sector
	unsigned int sectorNr;
	// data field
	char rawData[1020]{ '\0' };
	Sector();
	~Sector();
};

#endif /* Sector_h */
