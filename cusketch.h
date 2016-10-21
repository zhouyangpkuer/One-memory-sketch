#ifndef _CUSKETCH_H
#define _CUSKETCH_H

#include <algorithm>
#include <cstring>
#include "params.h"
#include "sketch.h"
#include "BOBHash.h"

class CUSketch: public Sketch
{	
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
	int *counter_per_word;
public:
	CUSketch(int w, int c, int hw, int hc);
	virtual void Insert(char * str);
	virtual lint Query(char *str);
	virtual void Delete(char *str);
	virtual ~Sketch();
};

#endif //_CUSKETCH_H

