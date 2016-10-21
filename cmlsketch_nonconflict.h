#ifndef _CMLSKETCH_NONCONFLICT_H
#define _CMLSKETCH_NONCONFLICT_H

#include <algorithm>
#include <cassert>
#include <cstring>
#include <cmath>
#include <random>
#include <math.h>
#include "sketch.h"
#include "BOBHash.h"
#include "params.h"
#include <vector>

using namespace std;
class NCMLSketch: public Sketch
{
private:
	double b;
	default_random_engine generator;
    uniform_real_distribution<double> distribution;
    BOBHash *fun_word;
    BOBHash *fun_counter;
public:
	NCMLSketch(int w, int c, int hw, int hc);
	virtual ~NCMLSketch();
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	bool decision(int c);
	double pointv(int c);
};

#endif // _CMLSKETCH_NONCONFLICT_H