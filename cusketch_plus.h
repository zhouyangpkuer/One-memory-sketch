#ifndef _CUSKETCH_PLUS_H
#define _CUSKETCH_PLUS_H

#include <algorithm>
#include <cstring>
#include "params.h"
#include "sketch.h"
#include "BOBHash.h"
#include <iostream>
#include <set>
#include <iterator>
#include <ctime>
#include <stdio.h>
#include <vector>
using namespace std;

class CUSketch_plus: public Sketch
{	
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
	int *hashedcounter_per_word;
	int *hash_value;
	set<int> st_min;
	set<int> st_max;
	vector<unsigned long long> query_str;
public:
	CUSketch_plus(int w, int c, int hw, int hc);
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	~CUSketch_plus();
};

#endif //_CUSKETCH_PLUS_H

