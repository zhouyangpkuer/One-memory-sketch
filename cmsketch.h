#ifndef _CMSKETCH_H
#define _CMSKETCH_H
#include <cstring>
#include <algorithm>
#include "sketch.h"
#include "BOBHash.h"
#include "params.h"

using namespace std;
class CMSketch : public Sketch
{
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
public:
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	CMSketch(int w, int c, int hw, int hc);
	virtual ~CMSketch();
};

#endif // _CMSKETCH_H