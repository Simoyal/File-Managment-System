//********************************************************************************************
// @author Moyal Simon 1177707
// @author Shimshon Attal 209552397
// @file Disk.cpp
// @description: implementation of all the methods the class Disk.
//********************************************************************************************
#pragma once
#ifdef _MSC_VER
#define  _CRT_SECURE_NO_WARNINGS 1
#endif 

#include <iostream>
#include <string>
#include <bitset>
#include <ctime>
#include <fstream>

#include "Disk.h"
#include "Sector.h"
#include "DAT.h"
#include "DirEntry.h"
#include "VolumeHeader.h"
#include "SectorDir.h"
#include "FileHeader.h"
#include "RootDir.h"
#include "FCB.h"
#include "Help.h"
#include "TestLevel_2.h"

class TestLevel_2;

using namespace std;

enum choice
{
	First_fit = 1, Best_fit, Worst_fit
};
/**************************************** LEVEL 0 **********************************************/
// constructor
Disk::Disk()
{
	this->mounted = false;
	currDiskSectorNr = 0;
}

// default constructor
Disk::Disk(string & file_name, string & disk_owner, char code)
{
	// code 'c' : createdisk + mountdisk
	if (code == 'c')
	{
		if (!checkFile(file_name))
		{
			createdisk(file_name, disk_owner);
			mountdisk(file_name);
		}
		else
			throw "A file already exist";
		currDiskSectorNr = 0;
	}
	// code 'm' : mountdisk
	else if (code == 'm')
	{  
		if (checkFile(file_name))
			mountdisk(file_name);
		else 
			throw "the file not exist";
	}
	else 
		throw "Unknow code\n";
	this->mounted = false;
}

// destructor
Disk::~Disk()
{
	// if the disk is already mount so ounmout it
	if (mounted)
		unmountdisk();
}

// create disk
void Disk::createdisk(string disk_name, string disk_owner)
{

	// set volume header with specific data
	vhd.setVolumeheader(0, disk_name.c_str(), disk_owner.c_str(), '\0', 1600, 1596, 1, 1, 1000, 800, 2, '\0', false);

	if (ifstream(disk_name.c_str()))
		throw "The disk already exist";

	// open the file
	dskfl.open(disk_name, ios::binary | ios::out);
	if (!this->dskfl.is_open())
	{
		throw "can not create the disk";
	}
	this->mounted = true;
	Sector* tmp = new Sector();
	// writing index in all the sectors.
	for (int i = 0; i < 3200; i++)
	{
		(*tmp).sectorNr = i;
		writeSector(i, tmp);
	}
	dat.Dat.reset();
	// all 1.
	dat.Dat.flip();
	// Setting to busy that place
	dat.Dat.set(0, false);
	dat.Dat.set(1, false);
	dat.Dat.set(1598, false);
	dat.Dat.set(1599, false);
	this->mounted = false;
	delete tmp;
	tmp = nullptr;
	// writing data
	seekToSector(0);
	
	// vhd
	dskfl.write((char *)&vhd, sizeof(Sector));
	seekToSector(1);
	
	// dat
	dskfl.write((char *)&dat, sizeof(Sector));
	
	// close the file
	dskfl.close();
}

// recreate the disk
void Disk::recreatedisk(string & disk_owner)
{
	// checking the owner of the disk
	if (vhd.diskOwner != disk_owner)
		throw "Error no matching owner !";
	
	// checking if the disk isn't already mounted 
	if (mounted)
		throw "Error , the disk is already mounted!";

	// checking if the file exist
	if (!checkFile(disk_owner))
		throw "the file doesn't exist anymore";

	dskfl.open(disk_owner, ios::out | ios::binary);
	this->seekToSector(0);
	Sector* tmpSec = new Sector();
	// writing index in all the sectors.
	for (int i = 0; i < SECTOR_QUANTITY / N_SECTOR_ON_CLUSTER; i++)
	{
		(*tmpSec).sectorNr = i;
		this->writeSector(i, tmpSec);
	}
	// writing data
	seekToSector(0);

	// vhd
	dskfl.write((char *)&vhd, sizeof(Sector));
	seekToSector(1);

	// dat
	dskfl.write((char *)&dat, sizeof(Sector));
	seekToSector(3198);

	dskfl.write((char *)&rootdir, sizeof(RootDir));
	currDiskSectorNr = 3199 ;
}

void Disk::unmountdisk()
{
	this->flush();
	dskfl.close();
	this->mounted = false;
}

fstream * Disk::getdskfl()
{
	string tmp(vhd.diskName);
	// checking if the file exist
	if (checkFile(tmp))
		return &dskfl;

	return NULL;
}

void Disk::seekToSector(unsigned int requested_number)
{
	// checking the file
	if (!dskfl.is_open())
		throw "Error the File is close, Disk::seekToSector\n";
	
	this->dskfl.seekg(ios::beg);
	this->dskfl.seekp(ios::beg);
	
	// define the place we should "jump"
	int nr = requested_number * sizeof(Sector);
	// checking overflow
	if (nr > 3200 * sizeof(Sector))
		throw  exception("Error overflow, seektosector");

	currDiskSectorNr = requested_number;
	// setting the cursor to the requested sector in order to reqd or write on it
	dskfl.seekg(nr);
	dskfl.seekp(nr);
}

void Disk::writeSector(unsigned int number, Sector * tmp)
{
	// first seeking to the requested sector
	this->seekToSector(number);
	
	// writing sector
	this->writeSector(tmp);
	
	// update the current sector.
	this->currDiskSectorNr++; 
}

void Disk::writeSector(Sector* sec)
{
	// checking the file
	if (!dskfl.is_open())
		throw exception("Error! The file is closed!\n");

	// checking if we could write data in the buffer
	if (!dskfl.write((char*)sec, sizeof(Sector)))
		throw exception("Error! Failed writing!\n");
		
	dskfl.flush();
}

void Disk::readSector(Sector* sec)
{
	// closed file
	if (!dskfl.is_open())
		throw exception("Error! The file is closed!\n");
	
	// moving to the right sector
	this->seekToSector(currDiskSectorNr);

	//read the data from the buffer
	if (!this->dskfl.read((char*)sec, sizeof(Sector))) 
		throw exception("Error! Failed writing!\n");
	
	// increasing 
	this->currDiskSectorNr++;
}
// read a sector
void Disk::readSector(unsigned int nR, Sector* sec)
{
	if (!dskfl.is_open())
		throw exception("Error! The file is closed!\n");

	currDiskSectorNr = nR;
	sec->sectorNr = nR;
	readSector(sec);
}

void Disk::mountdisk(string & file_name)
{
	// open the file
	dskfl.open(file_name, ios::in | ios::out | ios::binary);
	if (dskfl.is_open())
	{
		// begin the procedure
		seekToSector(0);
		// reading vhd
		dskfl.read((char*)&vhd, sizeof(Sector));
		seekToSector(1);
		// reading dat
		dskfl.read((char *)&dat, sizeof(Sector));
		seekToSector(3198);
		// reading msbsector
		dskfl.read((char *)&rootdir, sizeof(RootDir));
		this->mounted = true;
		this->dskfl.flush();
		seekToSector(4);
	}
	else
		throw "unable to open the file\n";
}
// checking if a file exist in the disk
bool Disk::checkFile(string & fileName) 
{
	// trying to open the file
	dskfl.open(fileName, ios::in);
	// the file exist close it and return true	
	if (dskfl.is_open())
		{
			dskfl.close();
			return true;
		}
	// the file not exist anymore
	return false;
}
// return vhd
Volume_Header Disk::getvhd()
{
	return vhd;
}

void Disk::flush()
{
	// Verify if there is a mounted disk
	if (!this->mounted)															
		throw"There is n disk mounted, Disk::flush\n";				

	if (!dskfl.is_open())
		throw "The disk isn't open\n";

	this->seekToSector(0);
	this->dskfl.write((char*)&vhd, sizeof(Sector));
	
	this->seekToSector(1);
	this->dskfl.write((char*)&dat, sizeof(Sector));

	this->seekToSector(3198);
	this->dskfl.write((char*)&rootdir, sizeof(RootDir));
	
	// Disk set as mounted
	dskfl.flush();
}
/**************************************** LEVEL 1 **********************************************/
// format function
void Disk::format(string & diskOwner)
{
	try
	{
		// you have to be the owner of the disk in order to format it
		if (diskOwner != vhd.diskOwner)
			throw "Error ! only the owner of the disk can format it";
		
		dat.Dat.reset();
		// all 1.
		dat.Dat.flip(); 
		// Setting to busy that place
		dat.Dat.set(0, false);
		dat.Dat.set(1, false);
		dat.Dat.set(1598, false);
		dat.Dat.set(1599, false);

		// update in the disk.
		for (int i = 0; i < 14; i++)
		{
			rootdir.msbSector.dirEntry[i].entryStatus = 0;
			rootdir.lsbSector.dirEntry[i].entryStatus = 0;
		}
		Sector* tmp = new Sector();
		// writing index in all the sectors.
		for (int i = 0; i < 3200; i++)
		{
			(*tmp).sectorNr = i;
			writeSector(i, tmp);
		}
		delete tmp;
		tmp = nullptr;
		DateNow(this->vhd.formatDate);
		this->vhd.isFormated = true;
		rootdir.msbSector.sectorNr = 3198;
		rootdir.lsbSector.sectorNr = 3199;
		// update in the disk
		this->flush();
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}
}

// return the number of 1 digit in the bitset
int Disk::howmuchempty()
{	
	return dat.Dat.count(); 
}

// Algorithm first_fit (looking for big area for our data)
bool first_fit(DATtype & dat, DATtype & fat, unsigned int request)
{
	// indicator of free place
	int counter = 0;
	for (int i = 0; i < (SECTOR_QUANTITY / 2); i++)
	{
		// free place
		if (dat[i])
			counter++;
		
		// busy place setting the counter to 0
		if (!dat[i])
			counter = 0;

		// find an area with enough space
		if (request == counter)
		{
			// first free place
			int mark = i - counter + 1;
			// filling the area
			while (mark <= i)
			{
				// setting index to busy on both : DAT and FAT
				dat.set(mark, false);
				fat.set(mark, true);
				mark++;
			}
			// Success Allocating
			return true;
		}
	}
	// Fail allocating
	return false;
}

// getting the smallest free area , when using best_fit
bool SmallestPlace(DATtype & dat, int *begin, int *end, unsigned int request)
{
	// indicator of free space
	int counter = 0, mybegin = 0, myend = 0;
	// searching
	for (int i = 0; i < (SECTOR_QUANTITY / 2); i++)
	{
		if (dat[i])
			mybegin = i;
		// searching a place
		while (i < 1600 && dat[i])
		{
			myend = i;
			// checking end of bitset
			if (i != 1599)
				i++;
			else
				break;
		}
		// if this place is less than the previous one
		if ((myend - mybegin + 1) < (*end - *begin + 1) && (mybegin != 0 && myend != 0))
		{
			// updating data
			*begin = mybegin;
			*end = myend;
		}
	}
	if ((*end - *begin + 1) >= request)
		return true;
	else if ((myend - mybegin + 1) >= request)
	{
		*begin = mybegin;
		*end = myend;
		return true;
	}
	else 
		return false;
}

// Algorithm best_fit (looking for exactly space)
bool best_fit(DATtype & dat, DATtype & fat, unsigned int request, unsigned int Request)
{
	// indicator for free space
	int counter = 0, begin = 10000, end = 100000;
	unsigned int i = 0;
	bool check = false;
	do
	{
		if (request + i < dat.count())
			check = SmallestPlace(dat, &begin, &end, request + i);
		else
			throw "Not enought space";
		i++;
		
	} while (check ==  false);
	counter = begin;
	for (unsigned int it = 0; it < Request; it++)
	{
		dat.set(counter, false);
		fat.set(counter, true);
		counter++;
	}
	return true;
}

// Part of the algorithm worst_bit, find the biggest place in our bitset
void LargestPlace(DATtype & dat, int *begin, int *end)
{
	// indicator of free space
	int counter = 0;
	for (int i = 0; i < (SECTOR_QUANTITY / 2); i++)
	{
		// searching a place
		while (i < 1600 && dat[i])
		{
			counter++;
			// checking end of bitset
			if (i != 1599)
				i++;
			else
				break;
		}
		// if this place is greater than the previous one
		if (counter > (*end - *begin + 1))
		{
			// updating data
			*begin = i - counter;
			*end = i - 1;
		}
		// re-initialize our counter if a 0 is found
		if (i != 1599 && !dat[i])
		{
			counter = 0;
		}
	}
}

// Algorithm Worst_Fit (looking for the biggest place to insert our data)
void worst_fit(DATtype & dat, DATtype & fat, unsigned int request)
{
	// indicator for the largest place function
	int begin, end;
	begin = end = 0;
	// searching the largest place
	LargestPlace(dat, &begin, &end);
	// first place
	int tmp = end - begin + 1;
	// if the area is big enought
	if (tmp >= request)
	{
		// filling it
		for (int i = begin, j = 0; j < request; i++, j++)
		{
			// setting index to busy on both : DAT and FAT
			dat.set(i, false);
			fat.set(i, true);
		}
		// finished to allocate place
		return;
	}
	// don't have enought place so we will allocated as much as we can
	else
	{
		for (int i = begin, j = 0; j < request; i++, j++)
		{
			// setting index to busy on both : DAT and FAT
			dat.set(i, false);
			fat.set(i, true);
		}
		// recursive call
		worst_fit(dat, fat, request - tmp);
	}
}

//allocating place in the disk
void Disk::alloc(DATtype & fat, unsigned int sectorsRequest, unsigned int choice)
{
	int clusterRequest;
	// 3200 so divided by 2 and thinking final size
	sectorsRequest % 2 == 0 ? clusterRequest = sectorsRequest / 2 : clusterRequest = (sectorsRequest / 2) + 1;
	int i = 0;
	try
	{
		// checking if we have enough place
		if (clusterRequest > howmuchempty())
			throw "No enough space in the DAT/n";

		bool check;
		switch (choice)
		{
			// first_fit
		case First_fit:
			// if fail allocating then throw exception
			if (!first_fit(dat.Dat, fat, clusterRequest))
				throw "Failing searching place/n";
			break;
			// best_fit
		case Best_fit:
			check = best_fit(dat.Dat, fat, clusterRequest + i, clusterRequest);
			if (!check)
				throw "Fail allocating, Best::fit";
			else
				break;
		
			// worst _fit
		case Worst_fit:
				worst_fit(dat.Dat, fat, clusterRequest);
			break;
		
		default:
			throw "Unknow choice/n";
			break;
		}
	}
	// catching exception
	catch (char * msg)
	{
		cout << msg << endl;
	}
}

// extend a file by increasing it's FAT
void Disk::allocextend(DATtype & fat, unsigned int sector_requested, unsigned int choice)
{
	// allocating again with the same FAT
	alloc(fat, sector_requested, choice);
}

// deallocating file 
void Disk::dealloc(DATtype & FAT)
{
	for (int i = 0; i < SECTOR_QUANTITY / 2; i++)
		if (FAT[i])
			dat.Dat[i] = true;
	FAT.reset();
}

// this function help us to find the last bit allocated, size - count = 0
unsigned int Disk::FindLastOne(DATtype FAT)
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < CLUSTER_QUANTITY; i++)
	{
		if (FAT[i])
		{
			count++;
		}
		if (count == FAT.count())
			return i;
	}
}

/**************************************** LEVEL 2 **********************************************/
// create a file
void Disk::createfile(string & File_name, string & File_owner, string & File_type, unsigned int record_length, unsigned int sector_request, string & Data_type, unsigned int offset, unsigned int Keylength)
{
	try
	{
		// checking if the disk is mounted
		if (!mounted)
			throw "the disk isn't mounted !\n";

		bool check = false;
		
		// checking if the already exist
		if (isExist(File_name, check) != -1)
			throw "A file with the same name already exist in the disk";

		// checking unknow file type
		if (File_type != "V" && File_type != "F" && File_type != "D")
			throw "Unknow file type\n";

		// checking if keylength is allocated or not
		if (File_type == "D" && Keylength == 0)
			throw "KeyLength isn't initialized\n";

		// checking unknow key type
		if (Data_type != "I" && Data_type != "F" && Data_type != "C" && Data_type != "D")
			throw "Unknow Key type \n";

		// searching for a free place
		int i = 0;
		// first in the msb
		for (; i < 14; i++)
		{
			if (rootdir.msbSector.dirEntry[i].entryStatus == 0 || rootdir.msbSector.dirEntry[i].entryStatus == 2)
			{
				break;
			}
				
		}
		// if i == 14 it mean that the msb is full
		if (i == 14)
		{
			i = 0;
			for (; i < 14; i++)
			{
				if (rootdir.lsbSector.dirEntry[i].entryStatus == 0 || rootdir.lsbSector.dirEntry[i].entryStatus == 2)
				{
					check = true;
					break;
				}
			}
		}
		// if i == 14 so the lsb is full, then the disk is full
		if (i == 14)
			throw "The disk is full";
		// now creating and filling the FileHeader 
		FileHeader tmp;
		// each file has a FAT
		DATtype FAT;
		// setting all the bitset to free
		FAT.reset();
		// alloc the file
		alloc(FAT, sector_request, First_fit);
		// assigning the FAT
		tmp.FAT = FAT;
		// file name
		memcpy(tmp.fileDesc.Filename, File_name.c_str(), 12); // ok
		// file owner
		memcpy(tmp.fileDesc.fileOwner, File_owner.c_str(), 12); // ok
		// rechoumot with same size
		tmp.fileDesc.actualRecSize = record_length; // ok
		// not same size
		tmp.fileDesc.maxRecSize = 0; // ok
		// keysize
		tmp.fileDesc.keySize = Keylength; // ok
		// rec format
		strcpy_s(tmp.fileDesc.recFormat, sizeof(tmp.fileDesc.recFormat), File_type.c_str());
		// file size
		tmp.fileDesc.fileSize = sector_request; // ok
		// date
		DateNow(tmp.fileDesc.crDate); // ok
		// keyoffset
		tmp.fileDesc.keyOffset = offset; // ok
		// entry statut 
		tmp.fileDesc.entryStatus = 1; // ok
		// key type
		strcpy_s(tmp.fileDesc.keyType, 2, Data_type.c_str()); // ok
		// filaddr + eofRecNr
		// now searching in which place our file has been allocated
		int place = 0;
		for (int i = 0; i < CLUSTER_QUANTITY; i++)
		{
			// first place allocated
			if (FAT[i])
			{
				tmp.fileDesc.fileAddr = i;
				break;
			}
		}
		tmp.fileDesc.eofRecNr = FindLastOne(FAT);
		tmp.sectorNr = tmp.fileDesc.fileAddr*2;
		// saving our file in the disk
		!check ? (rootdir.msbSector.dirEntry[i] = tmp.fileDesc ): (rootdir.lsbSector.dirEntry[i] = tmp.fileDesc);

		this->seekToSector(tmp.fileDesc.fileAddr*2);

		dskfl.write((char *)&tmp, sizeof(Sector));

		this->flush();
	}
	// if an error occurs
	catch (char * msg)
	{
		cout << msg << endl;
	}
}

// checking if a file is present on the disk, and checking the owner of the file
int Disk::check_right(string & file_name, string & file_owner, bool & check)
{
	// searching on the msb
	int i = 0;
	for (; i < 14; i++)
	{
		if (strcmp(rootdir.msbSector.dirEntry[i].Filename, file_name.c_str()) == 0 && strcmp(rootdir.msbSector.dirEntry[i].fileOwner, file_owner.c_str()) == 0 && rootdir.msbSector.dirEntry[i].entryStatus == 1)
		{
			return i;
		}
	}
	// searching on the msb
	if (i == 14)
	{
		i = 0;
		for (; i < 14; i++)
		{
			if (strcmp(rootdir.lsbSector.dirEntry[i].Filename, file_name.c_str()) == 0 && strcmp(rootdir.lsbSector.dirEntry[i].fileOwner, file_owner.c_str()) == 0 && rootdir.lsbSector.dirEntry[i].entryStatus == 1)
			{
				// file is located is our lsb
				check = true;
				return i;
			}
		}
	}
	// no present on the disk or not the owner
	return -1;
}

// deleting a file from our disk
void Disk::delfile(string & File_name, string & File_owner)
{
	try
	{
		bool indicator = false;
		// checking if we have the file in the disk and the owner
		int tmp = check_right(File_name, File_owner, indicator);
		// no matching for both parameter
		if (tmp == -1)
			throw "The file isn't present on the disk OR you're not the owner of the file";
		// now grabbing the fat in order to dealloc the file
		FileHeader temp;
		temp.FAT.reset();
		// setting the entry status to delete (code '2')
		!indicator ? rootdir.msbSector.dirEntry[tmp].entryStatus = 2 : rootdir.lsbSector.dirEntry[tmp].entryStatus = 2;
		// seek to the msb or the lsb
		!indicator ? seekToSector(rootdir.msbSector.dirEntry[tmp].fileAddr*2) : seekToSector(rootdir.lsbSector.dirEntry[tmp].fileAddr*2);
		// reading data
		dskfl.read((char *)&temp, sizeof(Sector));
		// dealloc the file
		dealloc(temp.FAT);
		this->flush();
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}
}
 
// extend the size of a file
void Disk::extendfile(string & file_name, string & file_owner, unsigned int sector_req)
{
	try
	{
		bool indicator = false;
		// checking if the file exist
		int tmp = check_right(file_name, file_owner, indicator);
		if (tmp == -1)
			throw "The file isn't present on the disk OR you're not the owner of the file";
		// now grabbing the fat in order to dealloc the file
		FileHeader temp;
		// seek to the msb or the lsb
		!indicator ? seekToSector(rootdir.msbSector.dirEntry[tmp].fileAddr*2) : seekToSector(rootdir.lsbSector.dirEntry[tmp].fileAddr*2);
		// reading data in order to grab the fat
		dskfl.read((char *)&temp, sizeof(Sector));
		// now we have the fat , allocextend
		allocextend(temp.FAT, sector_req, First_fit);
		!indicator ? rootdir.msbSector.dirEntry[tmp].fileSize += sector_req : rootdir.lsbSector.dirEntry[tmp].fileSize += sector_req;
		!indicator ? rootdir.msbSector.dirEntry[tmp].eofRecNr = FindLastOne(temp.FAT) : rootdir.lsbSector.dirEntry[tmp].eofRecNr = FindLastOne(temp.FAT);
		/* update the dirEntry of the file, specially the eof*/
		this->flush();
	}
	catch (char * problem)
	{
		cout << problem << endl;
	}
}

// checking if a file is present on the disk
int Disk::isExist(string & file_name, bool & check)
{
	// searching on the msb
	int i = 0;
	for (; i < 14; i++)
	{
		if (strcmp(rootdir.msbSector.dirEntry[i].Filename, file_name.c_str()) == 0 && rootdir.msbSector.dirEntry[i].entryStatus == 1)
			return i;
	}
	// searching on the lsb
	if (i == 14)
	{
		i = 0;
		for (; i < 14; i++)
		{
			if (strcmp(rootdir.lsbSector.dirEntry[i].Filename, file_name.c_str()) == 0 && rootdir.lsbSector.dirEntry[i].entryStatus == 1)
			{
				check = true;
				return i;
			}
		}
	}
	// no present on the disk or not the owner
	return -1;
}

/***************************************** LEVEL 3 ************************************************/
// open file
FCB * Disk::openfile(string & file_name, string & file_owner, string & operation)
{
	if (operation.compare("I") != 0 && operation.compare("O") != 0 && operation.compare("IO") != 0 && operation.compare("E") != 0)
		throw "Unknow operation for your code";
	
	FCB * tmp = new FCB(this);
	int temp;
	FileHeader file;
	file.FAT.reset();
	bool check = false;
	if (operation.compare("I") == 0 || operation.compare("IO") == 0 || operation.compare("E") == 0)
	{
		temp = check_right(file_name, file_owner, check);
		if (temp == -1)
			throw "The file doesn't exist OR you're not the owner of the file";

		!check ? tmp->fileDesc = rootdir.msbSector.dirEntry[temp] : tmp->fileDesc = rootdir.lsbSector.dirEntry[temp];
		!check ? seekToSector(rootdir.msbSector.dirEntry[temp].fileAddr*2) : seekToSector(rootdir.lsbSector.dirEntry[temp].fileAddr*2);
		dskfl.read((char *)&file, sizeof(Sector));
		tmp->FAT = file.FAT;
	}
	else
	{
		temp = isExist(file_name, check);
		if (temp == -1)
			throw "The file doesn't exist";
		
		!check ? tmp->fileDesc = rootdir.msbSector.dirEntry[temp] : tmp->fileDesc = rootdir.lsbSector.dirEntry[temp];
		!check ? seekToSector(rootdir.msbSector.dirEntry[temp].fileAddr*2) : seekToSector(rootdir.lsbSector.dirEntry[temp].fileAddr*2);
		dskfl.read((char *)&file, sizeof(Sector));
		tmp->FAT = file.FAT;
	}
	// if we have open the file to extend it so we have to write after the last (actual) record
	// If the eofRecNr is equal to 0 then on the file there is still no record the we write at the first emplacement
	if (operation.compare("E") == 0 && file.fileDesc.eofRecNr != 0)
	{
		// The current record that we want to write ( but the number is from the beginning of the file)
		tmp->currRecNr = file.fileDesc.eofRecNr;
		int Record_on_sector = (1024 - 4) / file.fileDesc.actualRecSize;
		// Where is the record on the file ( which sector)
		// +1 is because at the first sector sitting the FileHeader 
		int recOnSec = (file.fileDesc.eofRecNr / Record_on_sector) + 1;
		tmp->currSecNr = recOnSec;

		// The rest of the division because the division give us the sector and the rest the emplacement of the record on buffer
		tmp->CurrRecNrlnBuff = (file.fileDesc.eofRecNr) % (Record_on_sector);
	}
	else
	{
		// The first sector sitting the FileHeader
		tmp->currSecNr = 1;
		// first record
		tmp->CurrRecNrlnBuff = tmp->currRecNr = file.fileDesc.maxRecSize;
	}
	// keeping the operation_type
	tmp->opentype = operation;
	// We send at parameters the number of the sector on the file (the logic address) 
	// --> and return the number of the sector (the physic address) on the disk 
	unsigned int nSec = tmp->Number_Of_Sector_Phy(tmp->currSecNr, &(file.FAT));
	// Then we read the present sector on the buffer
	readSector(nSec, &tmp->Buffer);
	return tmp;
}

// updating the dirEntry
unsigned int Disk::update(DirEntry file)
{
	if (!mounted)
		throw "the disk isn't mounted, Disk::update";

	bool check = false;
	int index = isExist(CharToString(file.Filename), check);
	if (index == -1)
		throw "The file isn't found";
	FileHeader fh;
	!check ? rootdir.msbSector.dirEntry[index] = file : rootdir.lsbSector.dirEntry[index] = file;
	!check ? seekToSector(rootdir.msbSector.dirEntry[index].fileAddr*2) : seekToSector(rootdir.lsbSector.dirEntry[index].fileAddr*2);
	dskfl.read((char*)&fh, sizeof(Sector));
	writeSector(file.fileAddr, (Sector*)&fh);
	return file.fileAddr + 1;
}

/***************************************** DLL FUNCTION *********************************************/
// getting the dirEntry
DirEntry *Disk::getDirEntry(string location, int index)
{
	if (index < 0 || index > 13)
		return NULL;
	
	if (location == "msb")
	{
		if (this->rootdir.msbSector.dirEntry[index].entryStatus == 1)
			return &rootdir.msbSector.dirEntry[index];
		else
			return NULL;

	}
	else if (location == "lsb")
	{
		if (this->rootdir.lsbSector.dirEntry[index].entryStatus == 1)
			return &rootdir.lsbSector.dirEntry[index];
		else
			return NULL;
	}
	else
		throw "Unknow location";
}

/**************************************** Defragmentation ******************************************/
// number of file in the disk
int Disk::NumberOfFile()
{
	int counter = 0, i = 0;
	// msb
	for (; i < 14; i++)
	{
		if (this->rootdir.msbSector.dirEntry[i].entryStatus == 1)
			counter++;
	}
	i = 0;
	// lsb
	for (; i < 14; i++)
	{
		if (this->rootdir.lsbSector.dirEntry[i].entryStatus == 1)
			counter++;
	}
	// return number of file
	return counter;
}

// help struct to defragment the disk
struct Defrag
{
	// to keep the dirEntry of a file
	DirEntry backup;
	// to keep the data inside a file (if data)
	char ** data;
};

// defragmentation function, re-organize the disk, needed after few deleted
void Disk::defragmentation()
{
	try
	{
		// if the disk is full this is useless
		if (this->howmuchempty() == 0)
			return;

		int number = NumberOfFile();
		// empty disk
		if (number == 0)
			throw "empty disk";
		// array to keep all the element of the disk
		Defrag * defrag = new Defrag[number];
		int i = 0, index = 0;
		char ** Data = NULL;
		// searching all the file in the msb
		for (; i < 14; i++)
		{
			// a file has been found
			if (this->rootdir.msbSector.dirEntry[i].entryStatus == 1)
			{
				// saving his dirEntry
				defrag[index].backup = rootdir.msbSector.dirEntry[i];
				// open the file and check if he contains records
				FCB * tmp = openfile(CharToString(defrag[index].backup.Filename), CharToString(defrag[index].backup.fileOwner), CharToString("IO"));
				Data = tmp->getfile();
				// the file contains record, so saving it
				if (Data != NULL)
				{
					defrag[index].data = Data;
					Data = NULL;
				}
				// nothing has been found
				else
					defrag[index].data = NULL;
				// closing the file
				tmp->closefile();
				// increasing the index for our Defrag array
				index++;
			}
		}
		i = 0;
		// searching all the file in the msb
		for (; i < 14; i++)
		{
			// a file has been found
			if (this->rootdir.lsbSector.dirEntry[i].entryStatus == 1)
			{
				// saving his dirEntry
				defrag[index].backup = rootdir.lsbSector.dirEntry[i];
				// open the file and check if he contains records
				FCB * tmp = openfile(CharToString(defrag[index].backup.Filename), CharToString(defrag[index].backup.fileOwner), CharToString("IO"));
				Data = tmp->getfile();
				// the file contains record, so saving it
				if (Data != NULL)
				{
					defrag[index].data = Data;
					Data = NULL;
				}
				// nothing has been found
				else
					defrag[index].data = NULL;
				// closing the file
				tmp->closefile();
				// increasing the index for our Defrag array
				index++;
			}
		}
		// formating the disk
		this->format(CharToString(vhd.diskOwner));
		this->vhd.isFormated = false;
		// re-insert all the file in our disk
		for (index = 0; index < number; index++)
		{
			// create a new file
			createfile(CharToString(defrag[index].backup.Filename), CharToString(defrag[index].backup.fileOwner), CharToString(defrag[index].backup.recFormat)
				, defrag[index].backup.actualRecSize, defrag[index].backup.fileSize, CharToString(defrag[index].backup.keyType), defrag[index].backup.keyOffset,
				defrag[index].backup.keySize);

			// if the file contains record
			if (defrag[index].backup.maxRecSize != 0)
			{
				// open
				FCB * tmp = openfile(CharToString(defrag[index].backup.Filename), CharToString(defrag[index].backup.fileOwner), CharToString("IO"));
				// write all the record
				for (int j = 0; j < defrag[index].backup.maxRecSize; j++)
				{
					tmp->writeRec(defrag[index].data[j], false);
					delete defrag[index].data[j];
				}
				delete defrag[index].data;
				// closing
				tmp->closefile();
			}
		}
		//freeing memory
		delete[] defrag;
		// flush the disk 
		this->flush();
	}
	catch (char * msg)
	{
		cout << msg << endl;
	}
}
