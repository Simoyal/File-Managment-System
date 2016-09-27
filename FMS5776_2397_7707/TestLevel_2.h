#include "Disk.h"
#include "TestLevel_0.h"
#include "FileHeader.h"

class Disk;

class Student
{
public:
	int id;
	char name[20];
	int year;
	float average;

	static int used;

	void setStudent()
	{
		id = ++used;
		cout << "id = " << id << endl;
		cout << "Enter name" << endl;
		cin >> name;
		cout << "Enter year" << endl;
		cin >> year;
		cout << "Enter average" << endl;
		cin >> average;
	}
	void updateStudent()
	{
		cout << "id = " << id << endl;
		cout << "Enter name" << endl;
		cin >> name;
		cout << "Enter year" << endl;
		cin >> year;
		cout << "Enter average" << endl;
		cin >> average;
	}

	void printStudent()
	{
		cout << "Id: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Year: " << year << endl;
		cout << "average: " << average << endl;
	}
};
class TestLevel_2
{
public:
	
	static void createFile(Disk * d)
	{
		unsigned int sectorSize;
		string fileName = "";
		cout << "Enter file name: " << endl;
		cin >> fileName;
		cout << "file name: " << fileName << endl;
		cout << "The owner: " << "David" << endl;
		cout << "Enter the number of sectors" << endl;
		cin >> sectorSize;
		d->createfile(fileName, (string)"David", (string)"F", sizeof(Student), sectorSize, (string)"I", 0, 4);
		printHeader(d, fileName.c_str());
	}

	static void extFile(Disk * d)
	{
		string  fileName;
		string  ownerFile;
		unsigned int sectorSize;
		cout << "Enter the file name" << endl;
		cin >> fileName;
		cout << "Enter the owner of the file" << endl;
		cin >> ownerFile;
		cout << "Enter the number of sectors to extend" << endl;
		cin >> sectorSize;

		d->extendfile(fileName, ownerFile, sectorSize);

		printHeader(d, fileName.c_str());
	}

	static void printHeader(Disk * d, const char * file = NULL)
	{
		char fileName[12];

		if (file != NULL)
			memcpy(fileName, file, 12);
		else {
			cout << "Insert the file name:" << endl;
			cin >> fileName;
		}
		bool check = false;
		unsigned int index = d->isExist((string)fileName, check);
		if (index == -1)
			throw "File not found\n";
		DirEntry * dir = !check ? &d->rootdir.msbSector.dirEntry[index] : &d->rootdir.lsbSector.dirEntry[index];
		if (dir == NULL)
		{
			throw "File doesn't exist";
			return;
		}

		cout << "File Name -->" << dir->Filename << endl;
		cout << "File Owner -->" << dir->fileOwner << endl;
		cout << "File Address -->" << dir->fileAddr << endl;
		cout << "Created Date -->" << dir->crDate << endl;
		cout << "File size -->" << dir->fileSize << endl;
		cout << "End of Record Nr -->" << dir->eofRecNr << endl;
		cout << "Max rec size -->" << dir->maxRecSize << endl;
		cout << "Actual Rec Size -->" << dir->actualRecSize << endl;
		cout << "Rec Format -->" << dir->recFormat << endl;
		cout << "Key offset -->" << dir->keyOffset << endl;
		cout << "Key Size -->" << dir->keySize << endl;
		cout << "Key Type -->" << dir->keyType << endl;
	}
	static void printHeader(DirEntry * dir)
	{
		if (dir == NULL)
		{
			throw "File doesn't exist";
			return;
		}
		cout << "File Name --> " << dir->Filename << endl;
		cout << "File Owner --> " << dir->fileOwner << endl;
		cout << "File Address --> " << dir->fileAddr << endl;
		cout << "Created Date --> " << dir->crDate << endl;
		cout << "File size --> " << dir->fileSize << endl;
		cout << "End of Record Nr --> " << dir->eofRecNr << endl;
		cout << "Max rec size --> " << dir->maxRecSize << endl;
		cout << "Actual Rec Size --> " << dir->actualRecSize << endl;
		cout << "Rec Format --> " << dir->recFormat << endl;
		cout << "Key offset --> " << dir->keyOffset << endl;
		cout << "Key Size --> " << dir->keySize << endl;
		cout << "Key Type --> " << dir->keyType << endl;
	}

	static void DeleteFile(Disk * d)
	{
		string  fileName;
		string  ownerFile;
		char ans;

		cout << "Are you sure? <Y/N>" << endl;
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			cout << "Enter the file name" << endl;
			cin >> fileName;
			cout << "Enter the owner of the file" << endl;
			cin >> ownerFile;

			d->delfile(fileName, ownerFile);
			int a = Number(d);
			cout << "Number of file: " << --a << endl;
		}
	}

	static DATtype getFAT(Disk *d, char * file = NULL, DATtype FAT = NULL)
	{
		bool check = false;
		string filename = "";
		cout << "Enter filename: " << endl;
		cin >> filename;
		int index = d->isExist(filename, check);
		if (index == -1)
			throw "File not found\n";
		FileHeader fh;
		fh.FAT.reset();
		cout << "Reading FAT, please wait..." << endl;
		if (!check)
			d->seekToSector(d->rootdir.msbSector.dirEntry[index].fileAddr*2);
		else
			d->seekToSector(d->rootdir.lsbSector.dirEntry[index].fileAddr*2);
		d->dskfl.read((char *)&fh, sizeof(Sector));
		return fh.FAT;
	}
	static int Number(Disk * d)
	{
		int i = 0, counter = 0;
		for (; i < 14; i++)
		{
			if (d->rootdir.msbSector.dirEntry[i].entryStatus == 1)
			{
				
				counter++;
			}
		}
		// searching on the msb
		if (i == 14)
		{
			i = 0;
			for (; i < 14; i++)
			{
				if (d->rootdir.lsbSector.dirEntry[i].entryStatus == 1)
				{
					
					counter++;
				}
			}
		}
		return counter;
	}

	static void Numberof(Disk * d)
	{
		int i = 0, counter = 0;
		for (; i < 14; i++)
		{
			if (d->rootdir.msbSector.dirEntry[i].entryStatus == 1)
			{
				printHeader(&d->rootdir.msbSector.dirEntry[i]);
				counter++;
			}
		}
		// searching on the msb
		if (i == 14)
		{
			i = 0;
			for (; i < 14; i++)
			{
				if (d->rootdir.lsbSector.dirEntry[i].entryStatus == 1)
				{
					printHeader(&d->rootdir.msbSector.dirEntry[i]);
					counter++;
				}
			}
		}
		cout << "Number of file on the disk: " << counter << endl;
	}
};
