#ifndef RootDir_h
#define RootDir_h
#include "SectorDir.h"

class RootDir
{
public:
	SectorDir msbSector;
	SectorDir lsbSector;

	RootDir()
	{
		msbSector.sectorNr = 3198;
		lsbSector.sectorNr = 3199;

	}
	~RootDir() {};
	RootDir & operator =(const RootDir &);
};



#endif /* RootDir_h */
