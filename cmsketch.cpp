#include <cstring>
#include <algorithm>
#include "cmsketch.h"

#define MAX_NUM 100000000

CMSketch::CMSketch(int w, int c, int hw, int hc)
{
	sketch = new Counter[c*w];
	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;
	for(int i = 0; i < hash_counter; i++)
	{
		fun_counter[i].initialize(i+1);
	}
	for(int i = 0; i < hash_word; i++)
	{
		fun_word[i].initialize(i+1+hash_counter);
	}
}

CMSketch::~CMSketch()
{
}

CMSketch::Query(char *str)
{
	lint res = MAX_NUM;
	int index_word[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int index_counter[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_word i++)
	{
		for(int j = 0; j < hash_counter; j++)
		{
			res = min(res, sketch[index_word[i]*counter_per_word+index_counter[j]].counter);
		}
	}
	return res;
}

CMSketch::Insert(char *str)
{
	int index_word[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int index_counter[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_word i++)
	{
		for(int j = 0; j < hash_counter; j++)
		{
			int index = index_word[i]*counter_per_word+index_counter[j];
			if(sketch[index].counter < (1<<COUNTER_SIZE) - 1)
				sketch[index].counter ++;
		}
	}
}

CMSketch::Delete(char *str)
{
	int index_word[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int index_counter[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_word i++)
	{
		for(int j = 0; j < hash_counter; j++)
		{
			int index = index_word[i]*counter_per_word+index_counter[j];
			if(sketch[index].counter > 0)
				sketch[index].counter --;
		}
	}
}