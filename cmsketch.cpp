#include "cmsketch.h"

CMSketch::CMSketch(int w)
{
	sketch = new Counter[COUNTER_WORD*w];
	word_num = w;
	for(int i = 0; i < HASH_COUNTER; i++)
	{
		hash_counter[i].initialize(i+1);
	}
	for(int i = 0; i < HASH_WORD; i++)
	{
		hash_word[i].initialize(i+1+HASH_COUNTER);
	}
}

CMSketch::~CMSketch()
{
	delete [] sketch;
}