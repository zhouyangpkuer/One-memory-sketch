#ifndef _CSKETCH_NONCONFLICT_H
#define _CSKETCH_NONCONFLICT_H

#include "sketch.h"
#include "BOBHash.h"
using namespace std;

class NCSketch: public Sketch
{
private:
	BOBHash *fun_counter_f;
	BOBHash *fun_word_f;
	BOBHash *fun_counter_g;
public:
	NCSketch(int w, int c, int hw, int hc);
	virtual ~NCSketch();
	virtual void Insert(const char *str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
};

#endif // _CSKETCH_NONCONFLICT_H