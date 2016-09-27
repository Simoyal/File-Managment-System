#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <ctime>
#include <fstream>
#include <list>

#include "Sector.h"
#include "DAT.h"
#include "DirEntry.h"
#include "VolumeHeader.h"
#include "SectorDir.h"
#include "FileHeader.h"
#include "RootDir.h"
#include "FCB.h"

class FCB;

class Disk
{
	string LastErrorMessage;
	DAT dat;
public:
	Volume_Header vhd;
	RootDir rootdir;
	bool mounted;
	fstream dskfl;
	unsigned int currDiskSectorNr;
	/************* LEVEL 0 **************/
	/*************************************************
	* FUNCTION
	*    Constructor disk
	* PARAMETERS
	*    void
	* RETURN VALUE
	*    none
	* MEANING
	*     Ctor: Create an empty disk.
	*           With empty name and empty fields.
	*
	*
	**************************************************/
	Disk();
	/*************************************************
	* FUNCTION
	*    Destructor disk
	* PARAMETERS
	*    void
	* RETURN VALUE
	*    none
	* MEANING
	*     Dtor: delete a disk.
	**************************************************/
	~Disk();
	/*************************************************
	* FUNCTION
	*   default Constructor disk
	* PARAMETERS
	*    1-string&: file's name.
	*    2-string&: owner's name.
	*    3-char   : C or M :
	*    C for creating a new disk
	*    M for mounted an existed disk.
	* RETURN VALUE
	*    none
	* MEANING
	*     Ctor: Create a disk.
	*           With owner's name .
	* SEE ALSO
	*     mounted().
	*     createdisk().
	**************************************************/
	Disk(string &, string &, char);
	/*************************************************
	* FUNCTION
	*   createdisk
	* PARAMETERS
	*    1-string&:diskName
	*    2-string&:ownerName
	* RETURN VALUE
	*    void
	* MEANING
	*    Create a disk, create a file with capacity
	*    (#sector)3200 * 1024 (sizeSector) = 3276800 B
	* SEE ALSO
	*    writeSector(Sector*).
	**************************************************/
	void createdisk(string , string );
	/*************************************************
	* FUNCTION
	*   recreatedisk
	* PARAMETERS
	*    1-string&:ownerName
	* RETURN VALUE
	*    void
	* MEANING
	*    recreate a disk, boot a disk given owner's name
	* SEE ALSO
	*     seekToSector(unsigned int).
	*     writeSector(unsigned int , Sector*)
	**************************************************/
	void recreatedisk(string &);
	/*************************************************
	* FUNCTION
	*   mountdisk
	* PARAMETERS
	*    1-string&:fileName
	* RETURN VALUE
	*    void
	* MEANING
	*   simulation of the mounted disk.
	*   make accesible the disk by the computer.
	*   enable to have I/O operation on the disk
	**************************************************/
	void mountdisk(string &);
	/*************************************************
	* FUNCTION
	*   unmountdisk
	* PARAMETERS
	*   none
	* RETURN VALUE
	*    void
	* MEANING
	*   simulation of the unmounted disk.
	*   make inaccesible the disk by the computer.
	**************************************************/
	void unmountdisk();
	/*************************************************
	* FUNCTION
	*   seekToSector
	* PARAMETERS
	*    unsigned int: sector number requested.
	* RETURN VALUE
	*    void
	* MEANING
	*    localise a requested Sector.
	*    set the field currDiskSectorNr by the given paramter.

	**************************************************/
	void seekToSector(unsigned int);
	/*************************************************
	* FUNCTION
	*   writeSector
	* PARAMETERS
	*    1-unsigned int: sector number requested.
	*    2-Sector*     : buffer.
	* RETURN VALUE
	*    void
	* MEANING
	*    write from buffer to sectorNr requested.
	* SEE ALSO
	*     seekToSector(unsigned int).
	*     writeSector(Sector*)
	**************************************************/
	void writeSector(unsigned int, Sector *);
	/*************************************************
	* FUNCTION
	*   writeSector
	* PARAMETERS
	*    1-Sector* : buffer.
	* RETURN VALUE
	*    void
	* MEANING
	*    write from buffer to currDiskSectorNr
	**************************************************/
	void writeSector(Sector *);
	/*************************************************
	* FUNCTION
	*   readSector
	* PARAMETERS
	*    1-unsigned int: sector number requested.
	*    2-Sector*     : buffer.
	* RETURN VALUE
	*    void
	* MEANING
	*    read from sectorNr requested to buffer
	* SEE ALSO
	*     seekToSector(unsigned int).
	*     readSector( Sector*)
	**************************************************/
	void readSector(unsigned int, Sector *);
	/*************************************************
	* FUNCTION
	*   getdskfl
	* PARAMETERS
	*    void
	* RETURN VALUE
	*    fstream*
	* MEANING
	*    give a pointer on the content of the disk which is a file.
	**************************************************/
	fstream * getdskfl();
	/*************************************************
	* FUNCTION
	*   readSector
	* PARAMETERS
	*    1-Sector*     : buffer.
	* RETURN VALUE
	*    void
	* MEANING
	*    read from currDiskSectorNr  to buffer
	**************************************************/
	void readSector(Sector *);
	/*************************************************
	* FUNCTION
	* checkfile
	* PARAMETERS
	* 1- String &
	* RETURN VALUE
	* boolean
	* MEANING
	* Checking if the file exist on the disk
	**************************************************/
	bool checkFile(string &);
	Volume_Header getvhd();
	/*************************************************
	* FUNCTION
	*	flush
	* PARAMETERS
	*	The function does not receive a value
	* RETURN VALUE
	*	The function does not return a value
	* MEANING
	*	The function will release the data to the disk file
	*	(DAT, Volumen Header ,Rootdir)
	***************************************************/
	void flush();
	/****************** LEVEL 0 ***************/

	
	/****************** LEVEL 1 *********************/
	
	/*************************************************
	* FUNCTION
	*   readInfoFromFileToDisk
	* PARAMETERS
	*    void
	* RETURN VALUE
	*    void
	* MEANING
	*    read the info scope of the disk from the file to the disk
	* SEE ALSO
	*     seekToSector(unsigned int).
	**************************************************/
	void format(string & diskOwner);
	/*************************************************
	* FUNCTION
	*   howmuchempty
	* PARAMETERS
	*    void
	* RETURN VALUE
	*    int
	* MEANING
	*    return the number of free space in the dat
	**************************************************/
	int howmuchempty();
	/*************************************************
	* FUNCTION
	*   alloc
	* PARAMETERS
	*    DATtype&: the fat of the file we want to fit clusters.
	*    unsingned int : the numbers of clusters requested.
	*    unsigned int : the choice : 1/2/3 according the way of fitting.
	* RETURN VALUE
	*    void
	* MEANING
	*    allocate memory to a file.
	**************************************************/
	void alloc(DATtype & fat, unsigned int sectorsRequest, unsigned int choice);
	/*************************************************
	* FUNCTION
	*   allocextend
	* PARAMETERS
	*    DATtype&: the fat of the file we want to fit clusters.
	*    unsingned int : the numbers of clusters requested.
	*    unsigned int : the choice : 1/2/3 according the way of fitting.
	* RETURN VALUE
	*    void
	* MEANING
	*    extend the allocated memory of  a file.
	* SEE ALSO
	*  alloc()
	**************************************************/
	void allocextend(DATtype & fat, unsigned int, unsigned int);
	/*************************************************
	* FUNCTION
	*   dealloc
	* PARAMETERS
	*    DATtype&: the fat of the file we want to fit clusters.
	* RETURN VALUE
	*    void
	* MEANING
	*    deallocat memory of  a file.
	* SEE ALSO
	**************************************************/
	void dealloc(DATtype & fat);
	unsigned int FindLastOne(DATtype FAT);

	/****************** END OF LEVEL 1 **************/

	/****************** LEVEL 2  ********************/
	
	/*************************************************
	* FUNCTION
	*	createfile
	* PARAMETERS
	*	The name				- Type: DATtype
	*	The owner				- Type: unsigned int
	*	If is dynamic			- Type: bool
	*	The regSize				- Type: unsigned int
	*	The Amount of sectors	- Type: unsigned int
	*	The key type			- Type: string
	*	The key offset			- Type: unsigned int
	*	The offset size			- Type: unsigned int
	* RETURN VALUE
	*	The function does not return a value
	* MEANING
	*	The function will create a file header and then
	*	allocate the file into the disk.
	***************************************************/
	void createfile(string &, string &, string &, unsigned int, unsigned int, string &, unsigned int, unsigned int = 0);
	/*************************************************
	* FUNCTION
	*	delfile
	* PARAMETERS
	*	The name				- Type: DATtype
	*	The owner				- Type: unsigned int
	* RETURN VALUE
	*	The function does not return a value
	* MEANING
	*	The function will delete a file.
	***************************************************/
	void delfile(string &, string &);
	/*************************************************
	* FUNCTION
	*	extendfile
	* PARAMETERS
	*	The name				- Type: DATtype
	*	The owner				- Type: unsigned int
	*	The Amount of sectors	- Type: unsigned int
	* RETURN VALUE
	*	The function does not return a value
	* MEANING
	*	The function will extend a file header through
	*	allocext.
	***************************************************/
	void extendfile(string &, string &, unsigned int);
	/**************************************************
	* FUNCTION
	*		check_right
	* PARAMETERS			
	*	Name of the file		- Type: string
	*	Name of the owner of the file		- Type: string
	*	check : indicator to located our file in the msb or lsb    - Type: bool
	* RETURN VALUE
	*	The function return the index , where our file is located
	* MEANING
	*	The function check if the file exist in the disk and which is the owner,
	*	and with the help of check : located where our file is located : 
	*	as check is false -> msb otherwise lsb
	***************************************************/
	int check_right(string &file_name, string &file_owner, bool & check);
	/**************************************************
	* FUNCTION
	*		IsExist
	* PARAMETERS
	*	Name of the file		- Type: string
	*	check : indicator to located our file in the msb or lsb    - Type: bool
	* RETURN VALUE
	*	The function return the index , where our file is located
	* MEANING
	*	The function check if the file exist in the disk
	*	and with the help of check : located where our file is located :
	*	as check is false -> msb otherwise lsb
	***************************************************/
	int isExist(string &, bool &);
	/*******************END OF LEVEL 2***************/

	/****************** LEVEL 3  ********************/
	FCB * openfile(string &, string &, string &);
	unsigned int update(DirEntry file);
	/********************END OF LEVEL 3**************/

	/***************** LEVEL 4 **********************/
	DAT GetDat()
	{
		return dat;
	}
	DirEntry *getDirEntry(string location, int index);
	string & GetLastErrorMessage()
	{
		return LastErrorMessage;
	}
	void SetLastErrorMessage(string lastErrorMessage)
	{
		this->LastErrorMessage = lastErrorMessage;
	}
	/**************** Defragmentation **************/
	int NumberOfFile();
	void defragmentation();
};
