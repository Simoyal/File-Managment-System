#pragma once
#include "Sector.h"
#include "Disk.h"
#include "VolumeHeader.h"
#include "DirEntry.h"
#include "DAT.h"
#include "FileHeader.h"
#include <iostream>
class TestLevel_1
{
public:
	static void test_1();
	static void bestfit(Disk& d, DATtype& fat);
	static void worstfit(Disk& d, DATtype& fat);
	static void firstfit(Disk& d, DATtype& fat);
	static void printdat(Disk& d);

	static void firstfitextend(Disk& d, DATtype& fat);
	static void bestfitextend(Disk& d, DATtype& fat);
};

