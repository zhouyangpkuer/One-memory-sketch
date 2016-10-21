#ifndef _CUSKETCH_NONCONFLICT_H
#define _CUSKETCH_NONCONFLICT_H

#include <algorithm>
#include <cstring>
#include "params.h"
#include "sketch.h"
#include "BOBHash.h"
using namespace std;

class NCUSketch: public Sketch
{	
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
	int *hashedcounter_per_word;
	int *hash_value;
public:
	NCUSketch(int w, int c, int hw, int hc);
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	~NCUSketch();
};

#endif //_CUSKETCH_NONCONFLICT_H

