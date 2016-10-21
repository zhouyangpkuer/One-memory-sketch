#ifndef _SKETCH_H
#define _SKETCH_H
#include "params.h"

struct Counter
{
	lint counter : COUNTER_SIZE;
};

class Sketch
{
protected:
	int word_num;
	int counter_per_word;
	int hash_counter;
	int hash_word;
	Counter *sketch;
public:
	// Sketch(int w, int c, int hw, int hc);
	virtual void Insert(const char *str) = 0;
	virtual lint Query(const char *str) = 0;
	virtual void Delete(const char *str) = 0;
	virtual ~Sketch()
	{
		delete[] sketch;
	}
};

#endif // _SKETCH_H