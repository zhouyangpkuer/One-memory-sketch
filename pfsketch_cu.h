#ifndef _PFSKETCH_CU_H
#define _PFSKETCH_CU_H

#include <algorithm>
#include <cstring>
#include "params.h"
#include "sketch.h"
#include "BOBHash.h"
#include <ctime>
#include <stdio.h>
using namespace std;
class PFSketch_cu: public Sketch
{	
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
	int *hashedcounter_per_word;
	int packages_num;
	// int *hash_value;
public:
	PFSketch_cu(int w, int c, int hw, int hc);
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	~PFSketch_cu();
};

#endif //_PFSKETCH_CU_H

