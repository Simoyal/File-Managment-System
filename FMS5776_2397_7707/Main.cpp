// Simon Moyal 1177707
// Shimson Attal 
#pragma once
#include "Disk.h"
#include "TestLevel_0.h"
#include "TestLevel_2.h"
#include "FCB.h"

using namespace std;

enum menu {
	clear = 1,																			 // Others
	testLevel0, createDisk, mountDisk, unmountDisk, flush, printDiskDetails,            // Level 0
	printDat, formatDisk, allocate, allocateext, deallocate,							 // Level 1
	createFile, getFile, extendFile, ShowFileFAT, deleteFile,							 // Level 2
	newFCB, fileDetails, NStudent, IStudent, GStudent, CUStudent, UStudent, DStudent,		 // Level 3
	PAStudents
};

void testLevel1(Disk * d, DATtype & FAT, bool ext = false);
void DATprint(DATtype DAT, char type = 'D');
int Student::used = 0;

int main() 
{

	system("color a");

	char choice[3], ans;

	char ** allData = NULL;

	TestLevel_0 a;

	Disk * disk = &a.d;

	DATtype FAT;

	FAT.set();

	FCB * fcb = NULL;

	Student stud;

	short anstemp;

	int save, tmp;

	do {
		try
		{

#pragma region Cout Options
			cout << "Select option:" << endl;
			cout << "\n\t\t<100> Exit " << endl;
			cout << "\t\t<1> Clear screen " << endl;
			cout << "\n\tLevel 0:" << endl;
			cout << "\t\t<2> Test level 0 " << endl;
			cout << "\t\t<3> Create disk " << endl;
			cout << "\t\t<4> Mount Disk " << endl;
			cout << "\t\t<5> Unmount Disk " << endl;
			cout << "\t\t<6> Release data into the Disk " << endl;
			cout << "\t\t<7> Print disk details " << endl;
			cout << "\n\tLevel 1:" << endl;
			cout << "\t\t<8> Print DAT " << endl;
			cout << "\t\t<9> Format Disk " << endl;
			cout << "\t\t<10> Allocate sectors " << endl;
			cout << "\t\t<11> Allocate last FAT " << endl;
			cout << "\t\t<12> Deallocate last FAT " << endl;
			cout << "\n\tLevel 2:" << endl;
			cout << "\t\t<13> Create new file " << endl;
			cout << "\t\t<14> Get file header" << endl;
			cout << "\t\t<15> Extend File " << endl;
			cout << "\t\t<16> Get FAT from a file " << endl;
			cout << "\t\t<17> Delete File " << endl;
			cout << "\n\tLevel 3:" << endl;
			cout << "\t\t<18> Get FCB " << endl;
			cout << "\t\t<19> Print file details " << endl;
			cout << "\t\t<20> New Student  " << endl;
			cout << "\t\t<21> Insert new Student  " << endl;
			cout << "\t\t<22> Get Student by id " << endl;
			cout << "\t\t<23> Cancel student update " << endl;
			cout << "\t\t<24> Update student " << endl;
			cout << "\t\t<25> Delete Student by id " << endl;
			cout << "\t\t<26> Print all students " << endl;
			cout << "\t\t<27> Close the current file " << endl;
			cout << "\t\t<28> Defragment the disk " << endl;



			cout << "\nYour choice: [    ]\b\b\b\b";


			cin >> choice;


			cout << "**************************************************" << endl;
#pragma endregion

			switch (atoi(choice))
			{
			case createDisk:
				a.test_create();
				break;
			case mountDisk:
				a.test_mount();
				TestLevel_2::Numberof(disk);
				break;
			case unmountDisk:
				disk->unmountdisk();
				cout << "unmounted!" << endl;
				break;
			case menu::flush:
				disk->flush();
				break;
			case formatDisk:
				cout << "are you sure <Y/N>? " << endl;
				cin >> ans;
				if (ans == 'Y' || ans == 'y')
				{
					disk->format(a.ownerName);
					cout << "Disk formated!" << endl;
				}
				break;

			case printDiskDetails:
				a.printDiskInfo();
				break;
			case testLevel0:
				a.printStructSize();
				break;
			case allocate:
				FAT.reset();
				testLevel1(disk, FAT);
				break;
			case allocateext:
				testLevel1(disk, FAT, true);
				break;
			case deallocate:
				cout << "De-alloc with this FAT\n";
				DATprint(FAT, 'F');
				disk->dealloc(FAT);
				cout << "deallocated! " << endl;
				break;
			case printDat:
				if (disk->mounted)
					DATprint(disk->GetDat().Dat, 'D');
				else
					cout << "There is not a mounted disk" << endl;
				break;
			case createFile:
				TestLevel_2::createFile(disk);
				break;
			case extendFile:
				TestLevel_2::extFile(disk);
				break;
			case getFile:
				TestLevel_2::printHeader(disk);
				break;
			case deleteFile:
				TestLevel_2::DeleteFile(disk);
				break;
			case ShowFileFAT:
				FAT = TestLevel_2::getFAT(disk);
				DATprint(FAT, 'F');
				break;
			
			case newFCB:
				fcb = disk->openfile((string)"Sim", (string)"David", (string)"IO");
				if (fcb != NULL)
				{
					DATprint(fcb->FAT, 'F');
				}
				else
					cout << "File doesn't exist" << endl;
				break;
			case fileDetails:
				if (fcb != NULL)
					TestLevel_2::printHeader(&fcb->fileDesc);
				else
					cout << "File are not opened" << endl;
				break;
			case NStudent:
				stud.setStudent();
			case IStudent:
				if (fcb != NULL) {
					fcb->writeRec((char *)&stud, false);
				}
				else
					cout << "File are not opened" << endl;
				cout << "Inserted!" << endl;
				break;
			
			case GStudent:
				if (fcb != NULL)
				{
					cout << "Insert record number:" << endl;
					cin >> anstemp;
					fcb->seekRec(0, anstemp);
					fcb->readRec((char *)&stud, true);
					stud.printStudent();
				}
				else
					cout << "File are not opened" << endl;
				break;

			case CUStudent:
				if (!fcb)
					throw "FCB is null";
				fcb->updateRecCancel();
				cout << "Update canceled" << endl;
				break;
			case UStudent:
				if (!fcb)
					throw "FCB is null";
				cout << "Insert record number:" << endl;
				cin >> anstemp;
				while (anstemp > fcb->currRecNr)
				{
					cout << "Out of range/n";
					cin >> anstemp;
				}
				stud.updateStudent();
				fcb->seekRec(0, anstemp);
				fcb->updateRec((char *)&stud);
				break;
			case DStudent:
				if (!fcb)
					throw "FCB is null";
				fcb->deleteRec();
				break;
			case PAStudents:
				if (!fcb)
					throw "FCB is null";
				cout << "Total rec in file --> " << fcb->fileDesc.eofRecNr << endl;
				save = fcb->currRecNr;
				cout << "Value of save: " << save << endl;
				allData = fcb->getfile();
				for (unsigned int i = 0; i < save; i++)
				{
					memcpy(&stud, allData[i], sizeof(Student));
					if (stud.id != 0)
						stud.printStudent();
				}
				fcb->currRecNr = save;
				break;
			case 27:
				cout << "Closing file ..." << endl;
				fcb->closefile();
				if (!fcb->d)
					cout << "File succefully close " << endl;
				break;
			case 28:
				cout << "Beginning defragmentation" << endl;
				disk->defragmentation();
				DATprint(disk->GetDat().Dat, 'D');
				break;

			case clear: std::system("cls"); break;

			}

			cin.get();
		}
		catch (exception ex)
		{
			cout << ex.what() << endl;
		}
		catch (char * msg)
		{
			string err(msg);
			cout << err << endl;
		}
		catch (...)
		{
			cout << "Error" << endl;
		}

		if (atoi(choice) != 1)
			cout << "**************************************************" << endl;


	} while (atoi(choice) != 100);

	return 0;
}

void testLevel1(Disk * d, DATtype & FAT, bool ext)
{
	short algo;
	int amount;
	cout << "Insert amount of sector to allocate:" << endl;
	cin >> amount;
	cout << "Select algorithm type" << endl;
	do {
		cout << "<1>First fit <2> Best Fit <3> Worst Fit" << endl;
		cin >> algo;
	} while (algo <= 0 && algo > 4);
	if (ext)
		d->allocextend(FAT, amount, algo);
	else
		d->alloc(FAT, amount, algo);

	cout << "FAT:" << endl;
	DATprint(FAT, 'F');
}

void DATprint(DATtype DAT, char type)
{
	for (int i = 0; i < 1600; i++)
	{
		if (type == 'D' && DAT[i] || type != 'D' && !DAT[i])
			cout << (char)219;
		else
			cout << (char)176;

		cout << '|';

		if (!((i + 1) % 50))
			cout << endl;
	}
	cout << endl;
}