//#include <afx.h>
// #include <afxtempl.h>
//#include "StdAfx.h"

double RandReal(double lo, double hi);
unsigned int RandInt(unsigned int lo, unsigned int hi);
double RandExponentialDist(double mean);

// void Assert(bool condition, CString msg);
// void AddSet(CArray<int, int> &S, int a);
// bool InSet(CArray<int, int> &S, int a);
int zipf(int x) ;
// FILETIME TimeAddition(FILETIME time1, FILETIME time2);
// FILETIME TimeSubstraction(FILETIME time1, FILETIME time2);
unsigned int hash(int id, unsigned int key, unsigned int maxKey);
unsigned int hash2(int id, unsigned int key1, unsigned int key2, unsigned int maxKey);
unsigned int hash3(int id, unsigned int key1, unsigned int key2, unsigned int maxKey, int counter_num);

#ifndef SUPPORT_H
#define SUPPORT_H

class Zipf {
public:
	Zipf(){};
	Zipf(int seed);
	~Zipf(){};

	unsigned int size;
	unsigned int arr[100000]; //

	unsigned int generate();
};
#endif