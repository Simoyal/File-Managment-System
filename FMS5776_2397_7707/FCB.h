#pragma once
#include <iostream>
#include "Disk.h"

class Disk;

class FCB
{
	string LastErrorMessage;
public:
	Disk * d;
	DirEntry fileDesc;
	DATtype FAT;
	Sector Buffer;
	unsigned int currRecNr;
	unsigned int currSecNr;
	unsigned int CurrRecNrlnBuff;

	string opentype;
	bool lock;
	bool change;

	FCB(); // ok
	FCB(Disk * disk); // ok
	~FCB();   // ok

	void closefile(); // ok
	void flushfile(); // ok
	void readRec(char *, unsigned int = 0); // ok
	void writeRec(char *, bool); // ok
	void seekRec(unsigned int, int); // ok
	void updateRecCancel(); // ok
	void deleteRec();  // ok
	void updateRec(char *);	// ok

	// return the number of the sector on the disk 
	unsigned int Number_Of_Sector_Phy(unsigned int nSec, DATtype * f = NULL);
	// Function to write the FileHeader of the file on the disk
	void Save_On_FH();
	// checking if the file is full or not
	bool IsFull();
	// Checking if the current record is EOF
	bool IsEOF();
	// Function to get the maximum record on the file
	unsigned int Max_Record_Allowed(); 
	// Function to get the number of record per sector
	unsigned int Number_Of_Record_In_Sector();
	// Return the pointer of the current record on buffer
	char * addrOfTheRecOnBuff();
	// This function return the number of the sector where is the record
	unsigned int Number_Of_Sector(int num);

	char ** getfile();
	/*************** END LEVEL 3***************************/

	/********************** LEVEL 4 ************************/
	string & GetLastErrorMessage()
	{
		return LastErrorMessage;
	}
	void SetLastErrorMessage(string lastErrorMessage)
	{
		this->LastErrorMessage = lastErrorMessage;
	}
	DirEntry *getFileDesc()
	{
		return &fileDesc;
	}
	string getType()
	{
		return opentype;
	}
};

