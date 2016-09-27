#ifndef DAT_h
#define DAT_h
#include <iostream>
#include <bitset>

using namespace std;

typedef bitset<1600> DATtype;

class DAT
{
public:
	DAT();
	~DAT() {};
	void operator = (const DAT &);

	unsigned int sectorNr;
	DATtype Dat;
	char emptyArea[816];
};
#endif /* DAT_h */




