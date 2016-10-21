#ifndef _CSKETCH_H
#define _CSKETCH_H

#include "sketch.h"
#include "BOBHash.h"

class CSketch
{
private:
	BOBHash *fun_counter_f;
	BOBHash *fun_word_f;
	BOBHash *fun_counter_g;
public:
	CSketch(int w, int c, int hw, int hc);
	virtual ~CSketch();
	virtual void Insert(char *str);
	virtual void Query(char *str);
	virtual void Delele(char *str);
};

#endif // _CSKETCH_H