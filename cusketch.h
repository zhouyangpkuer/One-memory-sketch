#ifndef _CUSKETCH_H
#define _CUSKETCH_H

#include <algorithm>
#include <cstring>
#include "params.h"
#include "sketch.h"
#include "BOBHash.h"
using namespace std;

class CUSketch: public Sketch
{	
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
	int *hashedcounter_per_word;
	int *hash_value;
public:
	CUSketch(int w, int c, int hw, int hc);
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	~CUSketch();
};

#endif //_CUSKETCH_H

