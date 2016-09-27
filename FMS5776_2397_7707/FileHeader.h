#ifndef FileHeader_h
#define FileHeader_h
#include "DAT.h"
#include "DirEntry.h"

class FileHeader
{

public:
	unsigned int sectorNr;  // id sector.
	DATtype FAT;          // tell wich cluster is used by the file.
	DirEntry fileDesc;     // descripting the file.
	char emptyArea[744];

	FileHeader(){ FAT.reset(); }
	FileHeader(unsigned int, DirEntry, DATtype)
	{
		
	}
	~FileHeader();
};


#endif /* FileHeader_h */
