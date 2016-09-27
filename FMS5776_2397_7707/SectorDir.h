#ifndef SectorDir_h
#define SectorDir_h

#include "DirEntry.h"

class SectorDir
{
public:
	int sectorNr;
	DirEntry dirEntry[14];
	char unUse[12];
	SectorDir();
	~SectorDir();
};

#endif /* SectorDir_h */
