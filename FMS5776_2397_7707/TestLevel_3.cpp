//#include "TestLevel_3.h"
//#include "TestLevel_2.h"
//using namespace std;
//
//void TestLevel_3::test_3()
//{
//	try
//	{
//		// We create the disk
//		string diskName = "disk 1";
//		string ownerName = "oshri";
//		Disk d;
//		d.createdisk(diskName, ownerName);
//
//		// We mounted it then we format it
//		d.mountdisk(diskName);
//		d.format(ownerName);
//
//		// We create file
//		string fN = "myNewFile";
//		string own = "Nissim";
//		string type = "F";
//		string It = "I";
//		d.createfile(fN, own, type, sizeof(Student), 5, It, 0);
//
//		// We open the file
//		string tp = "O";
//		FCB* fcb = d.openfile(fN, own, tp);
//
//		// We add it an record
//		Student s;
//		char txt[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus ultrices ante dolor, at euismod tellus posuere .";
//		strcpy_s(s.name, txt);
//		fcb->writeRec((char*)&s);
//
//		// We add it an record
//		Student s1;
//		char txt1[] = "nissim Tal nissim Tal nissim Tal nissim Tal nissim Tal nissim Tal nissim Tal nissim Tal 555";
//		strcpy_s(s1.name, txt1);
//		fcb->writeRec((char*)&s1);
//
//		// We add it an record
//		Student s2;
//		char txt2[] = "Itay vakninItay vakninItay vakninItay vakninItay vakninItay vaknin 65656565656";
//		strcpy_s(s2.name, txt2);
//		fcb->writeRec((char*)&s2);
//
//		// We close the file
//		fcb->closefile();
//
//		// We open the file
//		string tp2 = "E";
//		FCB* fcb2 = d.openfile(fN, own, tp2);
//
//		// We add it an record
//		Student s3;
//		char txt3[] = "princesse 1234";
//		strcpy_s(s3.name, txt3);
//		fcb2->writeRec((char*)&s3);
//
//		// We close the file
//		fcb2->closefile();
//
//		// We open the file
//		string tp5 = "E";
//		FCB* fcb5 = d.openfile(fN, own, tp5);
//
//		// We add it an record
//		Student s5;
//		char txt5[] = "ce reve bleu";
//		strcpy_s(s5.name, txt5);
//		fcb5->writeRec((char*)&s5);
//
//		// We close the file
//		fcb5->closefile();
//
//		// We open the file
//		string tp4 = "IO";
//		FCB* fcb4 = d.openfile(fN, own, tp4);
//
//		// We add it an record
//		Student s4;
//		char txt4[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce sed cursus leo. Pellentesque ultricies, odio a vulputate ultricies, odio neque egestas nunc, et aliquam quam nunc sed metus. Nunc pulvinar nec massa in malesuada. Nam lacinia mauris amet.";
//		strcpy_s(s4.name, txt4);
//
//		fcb4->seekRec(0, 2);
//		fcb4->writeRec((char*)&s4);
//
//		// We close the file
//		fcb4->closefile();
//
//	}
//	catch (char* c)
//	{
//		cout << c << endl;
//	}
//}
