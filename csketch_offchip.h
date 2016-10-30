#ifndef _CSKETCH_OFFCHIP_H
#define _CSKETCH_OFFCHIP_H

#include "sketch.h"
#include "BOBHash.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include "params.h"
using namespace std;

class CSketch_off: public Sketch
{
private:
	OffCounter *offsketch;
	BOBHash *fun_counter_f;
	BOBHash *fun_word_f;
	BOBHash *fun_counter_g;
	lint *res;
	int *index_counter;
	int *index_word;
	vector<int> used;
public:
	CSketch_off(int w, int c, int hw, int hc);
	virtual ~CSketch_off();
	virtual void Insert(const char *str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
};

#endif // _CSKETCH_OFFCHIP_H