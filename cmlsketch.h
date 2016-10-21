#ifndef _CMLSKETCH_H
#define _CMLSKETCH_H

#include <algorithm>
#include <cassert>
#include <cstring>
#include <cmath>
#include <random>
#include <math.h>
#include "sketch.h"
#include "BOBHash.h"
#include "params.h"
using namespace std;
class CMLSketch: public Sketch
{
private:
	double b;
	default_random_engine generator;
    uniform_real_distribution<double> distribution;
    BOBHash *fun_word;
    BOBHash *fun_counter;
public:
	CMLSketch(int w, int c, int hw, int hc);
	virtual ~CMLSketch();
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	bool decision(int c);
	double pointv(int c);
};

#endif // _CMLSKETCH_H