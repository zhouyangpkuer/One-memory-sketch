#ifndef _CMSKETCH_OFFCHIP_H
#define _CMSKETCH_OFFCHIP_H
#include <cstring>
#include <algorithm>
#include "sketch.h"
#include "BOBHash.h"
#include "params.h"
#include <vector>

using namespace std;

class CMSketch_off : public Sketch
{
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
	OffCounter *offsketch;

public:
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	CMSketch_off(int w, int c, int hw, int hc);
	virtual ~CMSketch_off();
	
};

#endif // _CMSKETCH_OFFCHIP_H