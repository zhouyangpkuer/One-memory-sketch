#ifndef _CMLSKETCH_H
#define _CMLSKETCH_H

#include <algorithm>
#include "sketch.h"
#include "BOBHash.h"

class CMLSketch
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
	virtual void Insert(char *str);
	virtual void Query(char *str);
	virtual void Delete(char *str);
	bool decision(int c);
	double pointv(int c);
};