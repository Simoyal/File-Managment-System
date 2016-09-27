#pragma once
#include "Disk.h"

class TestLevel_0
{

public:

	string diskName = "disk2.bin";
	string ownerName = "Sim's";
	Disk d;

	TestLevel_0()
	{

	}

	TestLevel_0(string name, string owner)
	{
		string diskName = name;
		string ownerName = owner;
	}

	void printStructSize()
	{
		cout << "start" << endl;
		cout << "Size Of Disk -->" << sizeof(Disk) << endl;
		cout << "Size Of Sector -->" << sizeof(Sector) << endl;
		cout << "Size Of VolumeHeader -->" << sizeof(Volume_Header) << endl;
		cout << "Size Of DAT -->" << sizeof(DAT) << endl;
		cout << "Size Of DirEntry -->" << sizeof(DirEntry) << endl;
		cout << "Size Of SectorDir -->" << sizeof(SectorDir) << endl;
		cout << "Size Of FileHeader -->" << sizeof(FileHeader) << endl;
		cout << "Size Of RootDir -->" << sizeof(RootDir) << endl;
	}

	void printDiskInfo()
	{
		Volume_Header* vh = &d.vhd;

		cout << "	disk name:        " << vh->diskName << endl;
		cout << "	Owner Name:       " << vh->diskOwner << endl;
		cout << "	prodDate:         " << vh->prodDate << endl;
		cout << "	formatDate:       " << vh->formatDate << endl;
		cout << "	isFormated:       " << vh->isFormated << endl;
		cout << "	addrDataStart:    " << vh->addrDataStart << endl;

		cout << "	ClusQty:          " << vh->ClusQty << endl;
		cout << "	dataClusQty:      " << vh->dataClusQty << endl;

		cout << "	addrDAT:          " << vh->addrDAT << endl;
		cout << "	addrRootDir:      " << vh->addrRootDir << endl;
		cout << "	addrDATcpy:       " << vh->addrDATcpy << endl;
		cout << "	addrRootDirCpy:   " << vh->addrRootDircpy << endl << endl;
	}

	void test_create()
	{
		d.createdisk(diskName, ownerName);
		cout << "Disk created!" << endl;
	}

	void test_mount()
	{
		this->d.mountdisk(diskName);
		cout << "mounted!" << endl;
	}

	void test_rwSector()
	{
		Sector sector;
		d.mountdisk(diskName);
		cout << "\nread sector: " << endl;
		d.readSector(8, &sector);
		strcpy_s(sector.rawData, "this is write temp sector");
		d.writeSector(8, &sector);
		d.unmountdisk();

	}

	void test_0()
	{
		printStructSize();
		test_create();		
		test_mount();
	}
};