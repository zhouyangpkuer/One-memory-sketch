#ifndef _CMSKETCH_H
#define _CMSKETCH_H

#include "sketch.h"
#include "BOBHash.h"

class CMSketch : public Sketch
{
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
public:
	virtual Insert(char *str);
	virtual Query(char *str);
	virtual Delete(char *str);
	CMSketch(int w, int c, ing hw, int hc);
	virtual ~CMSketch();
};

#endif // _CMSKETCH_H