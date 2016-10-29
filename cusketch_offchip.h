#ifndef _CUSKETCH_OFFCHIP_H
#define _CUSKETCH_OFFCHIP_H

#include <algorithm>
#include <cstring>
#include "params.h"
#include "sketch.h"
#include "BOBHash.h"
#include <iostream>

using namespace std;

class CUSketch_off: public Sketch
{	
private:
	OffCounter *offsketch;

	BOBHash *fun_counter;
	BOBHash *fun_word;
	int *hashedcounter_per_word;
	int *hash_value;
	
public:
	CUSketch_off(int w, int c, int hw, int hc);
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	~CUSketch_off();
};

#endif //_CUSKETCH_OFFCHIP_H

