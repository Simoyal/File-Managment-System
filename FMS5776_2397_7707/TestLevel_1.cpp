#include "TestLevel_1.h"
#include <iostream>

void TestLevel_1::test_1()
{
	try
	{
		string diskName = "disk 1";
		string ownerName = "oshri";
		Disk d;
		d.createdisk(diskName, ownerName);
		d.mountdisk(diskName);
		d.format(ownerName);

		d.GetDat().Dat.reset();
		d.GetDat().Dat.set(1, 1);
		d.GetDat().Dat.set(2, 1);
		d.GetDat().Dat.set(3, 1);
		d.GetDat().Dat.set(8, 1);
		d.GetDat().Dat.set(9, 1);
		d.GetDat().Dat.set(11, 1);
		d.GetDat().Dat.set(12, 1);
		d.GetDat().Dat.set(13, 1);
		d.GetDat().Dat.set(14, 1);

		DATtype fat;
		fat.reset();
		cout << "add a new file: 5 clusters" << endl;
		cout << "First Fit:" << endl;
		firstfit(d, fat);
		cout << "best Fit:" << endl;
		bestfit(d, fat);
		cout << "worst Fit:" << endl;
		worstfit(d, fat);
		firstfitextend(d, fat);
		bestfitextend(d, fat);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}

	catch (char* str)
	{
		cout << str << endl;
	}
}

void TestLevel_1::bestfit(Disk& d, DATtype& fat)
{
	cout << "before (free clusters numbers):" << endl;
	printdat(d);
	d.alloc(fat, 5, 2);
	cout << "after alloc (free clusters numbers):" << endl;
	printdat(d);
	d.dealloc(fat);
	fat.reset();
}
void TestLevel_1::firstfit(Disk& d, DATtype& fat)
{
	cout << "before (free clusters numbers):" << endl;
	printdat(d);
	d.alloc(fat, 5, 1);
	cout << "after alloc (free clusters numbers):" << endl;
	printdat(d);
	d.dealloc(fat);
	fat.reset();
}

void TestLevel_1::worstfit(Disk& d, DATtype& fat)
{
	cout << "before (free clusters numbers):" << endl;
	printdat(d);
	d.alloc(fat, 5, 3);
	cout << "after alloc (free clusters numbers):" << endl;
	printdat(d);
	d.dealloc(fat);
	fat.reset();
}

void TestLevel_1::printdat(Disk& d)
{
	for (int i = 0; i < 1600; i++)
	{
		if (d.GetDat().Dat.test(i))
			cout << i << ", ";
	}
	cout << endl;
}

void TestLevel_1::firstfitextend(Disk& d, DATtype& fat)
{

	d.alloc(fat, 5, 1);
	cout << "after extend the file with 3 more clusters by first fit method:" << endl;
	d.allocextend(fat, 3, 2);
	printdat(d);
	d.dealloc(fat);

}
void TestLevel_1::bestfitextend(Disk& d, DATtype& fat)
{
	d.alloc(fat, 5, 1);
	cout << "after extend the file with 3 more clusters by best fit method:" << endl;
	d.allocextend(fat, 3, 2);
	printdat(d);
	d.dealloc(fat);
}