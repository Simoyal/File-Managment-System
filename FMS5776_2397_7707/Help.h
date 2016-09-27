#ifndef Help_h
#define Help_h

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

// If the variable is true we print the size of all stuct that we instanced
#define PRINT_SIZE false

// The size of sector
#define SIZE_OF_SECTOR 1024

// The number of sector on the cluster
#define N_SECTOR_ON_CLUSTER 2

// The number of cluster on track
#define N_CLUSTER_ON_TRACK 4

// The number of track on platter
#define N_TRACK_ON_PLATTER 200

// The number of platter on the disk
#define N_PLATTER_ON_DISK 2

// The number of sector
#define SECTOR_QUANTITY 3200

// The number of clusters on this disk
#define CLUSTER_QUANTITY (SECTOR_QUANTITY/N_SECTOR_ON_CLUSTER)

// The number of dirEntry on directory
#define N_DIRENTRY_ON_CLUSTER 14

// The quantity of clusters for data
#define QUANTITY_CLUSTERS_FOR_DATA (CLUSTER_QUANTITY-4)

static string CharToString(char * convert)
{
	string final = "";
	stringstream s;
	s << convert;
	s >> final;
	return final;
}

static void DateNow(char tab[11])
{
	time_t  now = time(0);
	tm  tstruct;
	localtime_s(&tstruct, &now);
	strftime(tab, 11, "%d/%m/%Y", &tstruct);
}

#endif