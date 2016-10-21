#include <cstring>
#include <algorithm>
#include "cmsketch.h"

#define MAX_NUM 100000000

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

CMSketch::Query(char *str)
{
	lint res = MAX_NUM;
	int index_word[HASH_WORD];
	for(int i = 0; i < HASH_WORD; i++)
	{
		index_word[i] = hash_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int index_counter[HASH_COUNTER];
	for(int i = 0; i < HASH_COUNTER; i++)
	{
		index_counter[i] = hash_counter[i].run((const unsigned char *)str, strlen(str)) % COUNTER_WORD;
	}
	for(int i = 0; i < HASH_WORD; i++)
	{
		for(int j = 0; j < HASH_COUNTER; j++)
		{
			res = min(res, sketch[index_word[i]*COUNTER_WORD+index_counter[j]].counter);
		}
	}
	return res;
}

CMSketch::Insert(char *str)
{
	int index_word[HASH_WORD];
	for(int i = 0; i < HASH_WORD; i++)
	{
		index_word[i] = hash_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int index_counter[HASH_COUNTER];
	for(int i = 0; i < HASH_COUNTER; i++)
	{
		index_counter[i] = hash_counter[i].run((const unsigned char *)str, strlen(str)) % COUNTER_WORD;
	}
	for(int i = 0; i < HASH_WORD; i++)
	{
		for(int j = 0; j < HASH_COUNTER; j++)
		{
			sketch[index_word[i]*COUNTER_WORD+index_counter[j]].counter++;
		}
	}
}