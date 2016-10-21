#ifndef _CSKETCH_H
#define _CSKETCH_H

#include "sketch.h"
#include "BOBHash.h"
#include <cstring>
#include <algorithm>
using namespace std;

class CSketch: public Sketch
{
private:
	BOBHash *fun_counter_f;
	BOBHash *fun_word_f;
	BOBHash *fun_counter_g;
public:
	CSketch(int w, int c, int hw, int hc);
	virtual ~CSketch();
	virtual void Insert(const char *str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
};

#endif // _CSKETCH_H