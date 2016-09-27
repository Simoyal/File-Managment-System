#include <iostream>
#include "Help.h"
#include "FCB.h"
#include "TestLevel_2.h"
// constructor
FCB::FCB()
{
	// setting all the bitset to false
	FAT.reset();
	currRecNr = CurrRecNrlnBuff = 0;
	currSecNr = 1;
	// d is null
	d = NULL;
	// initialize the opentype
	opentype[0] = '\0';
	// no lock or changment of the file
	change = lock = false;
 
} 

// constructor
FCB::FCB(Disk * disk)
{
	// setting all the bitset to false
	this->FAT.reset();
	// setting our pointer to the address of the receive disk
	d = disk;
	// no lock or changment of the file
	change = lock = false;
	currRecNr = CurrRecNrlnBuff = 0;
	currSecNr = 1;
	currRecNr = fileDesc.maxRecSize;
}

// destructor 
FCB::~FCB()
{
	closefile();
}

void FCB::closefile()
{
	if (lock)
		throw "The file is lock\n";
	// We write the current sector on the buffer
	this->flushfile();
	//d->unmountdisk();
	// Disable this FCB
	d = nullptr;
}

// Function to write the contain of the buffer to the equivalent sector
void FCB::flushfile()
{
	if (!d)
		throw "There is no disk loaded\n";
	d->writeSector(this->Buffer.sectorNr, &this->Buffer);
	fileDesc.maxRecSize = currRecNr;
	d->update(fileDesc);
	d->flush();
	Save_On_FH();
	// Then we read the present sector on the buffer
	change = false;
}

void FCB::readRec(char * record, unsigned int type)
{

	if (!d)
		throw "There is no disk loaded\n";

	// If the previous call to read was been to update the we lock the file
	if (lock)
		throw "Error: file locked!, read";

	// If the current record is the eofRec
	//if (IsEOF())
		//throw "Error: end of file!";

	// If the file opened to add or to output
	if (this->opentype.compare("E") == 0 || this->opentype.compare("O") == 0)
		throw "Error: this file is opened to add or write only!";
	
	int sizeRec = this->fileDesc.actualRecSize;
	memcpy_s((void*)record, sizeRec, (void*)addrOfTheRecOnBuff(), sizeRec);

	// We move the seek to the next record
	if (type == 0)
	{
		// mooving to the next one
		seekRec(1, 1);
	}
	else
	{
		lock = true;
	}
	
}

void FCB::writeRec(char * record, bool update)
{
	if (!d)
		throw "The disk isn't loaded\n";
	
	// If the previous call to read was been to update the we lock the file
	if (!update)
	{
		if (lock)
			throw "Error: file locked!, writeRec";
	}
	// If this file is full
	if (IsFull())
		throw "Error: the file is full!, writeRec";

	// If the file opened to add or to output
	if (this->opentype == "O")
		throw "Error: this file is opened to read only!";

	// If the current record was the eofRec we increment to the new
	if (IsEOF())
		fileDesc.eofRecNr++;

	// change on the buffer
	this->change = true; 

	int sizeRec = this->fileDesc.actualRecSize;
	memcpy_s((void*)addrOfTheRecOnBuff(), sizeRec, (void*)record, sizeRec);
	// mooving to the next one
	if (update)
		lock = false;
	this->flushfile();
	if(!update)
		this->currRecNr++;
	seekRec(1, 1);
}

void FCB::seekRec(unsigned int type, int num)
{
	// If there is locked the file we don't can to seek on
	if (lock)
		throw "Error: file locked!, seekRec";

	// we calcul the number of the record from the beginning of the file
	int addrOfRecOnDisk;
	if (type == 0)
	{
		if (num < 0 || num > this->fileDesc.eofRecNr)
			throw "Error: you can't move at place minus record";
		
		addrOfRecOnDisk = num;
	}
	else if (type == 1)
	{
		addrOfRecOnDisk = (currSecNr - 1) * Number_Of_Record_In_Sector() + CurrRecNrlnBuff + num;
		if (addrOfRecOnDisk > this->fileDesc.eofRecNr || addrOfRecOnDisk < 0)
			throw "Error: you can't move at place minus record";
	}
	if (type == 2)
	{
		if (num > this->fileDesc.eofRecNr || num < 0)
			throw "Error: you can't move at place minus record";
		addrOfRecOnDisk = this->fileDesc.eofRecNr - num;
	}

	unsigned int secOfThisRec = Number_Of_Sector(addrOfRecOnDisk);

	// We check if the next record is on the sector that is on buffer
	if (secOfThisRec != currSecNr)
	{
		flushfile();  // We write the buffer on disk because it will replaced
		unsigned int addrPhy = Number_Of_Sector_Phy(secOfThisRec);
		d->readSector(addrPhy, (Sector*)&this->Buffer); // We read the new buffer
		currSecNr = secOfThisRec;
	}
	CurrRecNrlnBuff = addrOfRecOnDisk % Number_Of_Record_In_Sector();

}

// to do , mooving back all the record, and swapping the requested one to the end and hide it
void FCB::deleteRec()
{	
	if (currRecNr == 0)
		throw "Empty file\n";
	/*if (!lock)
		throw "The file isn't lock\n";*/
	long ZERO = 0;
	memcpy(this->Buffer.rawData + CurrRecNrlnBuff * fileDesc.actualRecSize + fileDesc.keyOffset, &ZERO, fileDesc.keySize);
	this->currRecNr--;
	lock = false;
	this->flushfile();

}

void FCB::updateRecCancel()
{
	if (!lock || this->opentype == "I" || this->opentype == "E" || this->opentype == "O")
		throw "Error: the file must be opened for update first!";
	lock = false;
}

void FCB::updateRec(char* record)
{
	if (this->opentype == "I" || this->opentype == "E" || this->opentype == "O")
		throw "Error: the file must be opened for update first!";
	
	// We open the file to write on
	memcpy_s((void*)addrOfTheRecOnBuff(), this->fileDesc.actualRecSize, (void*)record, this->fileDesc.actualRecSize);
	this->flushfile();
	lock = false; 
}

// We send at parameters the logic address of sector and the function return the physic address
unsigned int FCB::Number_Of_Sector_Phy(unsigned int nSec, DATtype * f)
{
	// If f = null then we take the file header of this file
	if (f == NULL)
		f = &(this->FAT);

	unsigned int pos = 0;

	// The position on the fat, of the first cluster of the file
	while (!f->test(pos))
		pos++;

	// If the sector that we search is on the first cluster (nSec < N_SECTOR_ON_CLUSTER) then we return 
	// (pos * N_SECTOR_ON_CLUSTER) + (pos % N_SECTOR_ON_CLUSTER)
	//  The first sector  on the cluster + the number of sector to add to come at the sector that we want
	if (nSec < N_SECTOR_ON_CLUSTER)
		return (pos * N_SECTOR_ON_CLUSTER) + nSec;

	// Else we check the cluster that the sector is there
	unsigned int inWhichClusterIsTheSector = ceil((double)nSec / N_SECTOR_ON_CLUSTER);

	for (int i = 0; i < inWhichClusterIsTheSector; i++)
	{
		pos++; // to progress because the last is 1 surely
		while (!f->test(pos)) pos++;
	}
	// We return the (pos * N_SECTOR_ON_CLUSTER) + (nSec % N_SECTOR_ON_CLUSTER)
	return (pos * N_SECTOR_ON_CLUSTER) + (nSec % N_SECTOR_ON_CLUSTER);
}

// How much record for each sector
unsigned int FCB::Number_Of_Record_In_Sector()
{
	// How much record on sector
	// ( The size of data ) / ( The size of record )
	return (int)((SIZE_OF_SECTOR - 4) / this->fileDesc.actualRecSize);
}

// The maximum of record on this file
unsigned int FCB::Max_Record_Allowed()
{
	// The number of record on file is:
	// ( (Numbers of sector on file -1) * (Record per sector)
	// -1 because there is one sector for the file header and the rest for data
	return ((this->fileDesc.fileSize - 1) * Number_Of_Record_In_Sector());
}

// If The current record is the End of file
bool FCB::IsEOF()
{
	return (this->currRecNr >= this->fileDesc.eofRecNr);
}

// checking if the file is full
bool FCB::IsFull()
{
	// If the last record adress is greater than the maxRecord allowed
	return (this->fileDesc.eofRecNr >= Max_Record_Allowed());
}

// This function return the number of the sector where is the record
unsigned int FCB::Number_Of_Sector(int num)
{
	return (unsigned int)ceil((double)(num / Number_Of_Record_In_Sector())) + 1;
}

// Return the pointer of the current record on buffer
char * FCB::addrOfTheRecOnBuff()
{
	int sizeRec = this->fileDesc.actualRecSize;

	// The address of the current record on the buffer is 
	// (addr of buffer) + (sizeRec * currRecNrInBuff)
	return ((char*)(&this->Buffer.rawData)) + (sizeRec * CurrRecNrlnBuff);
}

void FCB::Save_On_FH()
{
	// The position of the fileheader
	unsigned int pos = Number_Of_Sector_Phy(0);

	FileHeader tmp;
	tmp.FAT = FAT;
	tmp.fileDesc = fileDesc;
	tmp.sectorNr = fileDesc.fileAddr;

	// We write it on disk
	d->writeSector(pos, (Sector*)&tmp);
}

char ** FCB::getfile()
{
	if (fileDesc.eofRecNr == 0)
		return NULL;
	char ** file;
	if (fileDesc.eofRecNr > 1)
		file = new char *[currRecNr];
	else
		throw "Unable to read one record\n";
	unsigned int a = this->currRecNr;
	this->seekRec(0, 0);
	for (unsigned int i = 0; i < a; i++)
	{
			file[i] = new char[fileDesc.actualRecSize];
			this->readRec(file[i], 1);
			this->lock = false;
	}
	this->currRecNr = a;
	return file;
}