#include "DAT.h"
#include <iostream>
#include <bitset>

DAT::DAT()
{
	sectorNr = 1;
	// since the first Four sector are always taken
	// and in each cluster there is 2 sector.
	Dat.set(0, true);
	Dat.set(1, true);

}
void DAT::operator = (const DAT & dat)
{
	this->sectorNr = dat.sectorNr;
	this->Dat = dat.Dat;
}
