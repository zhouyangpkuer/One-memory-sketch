#include "cmsketch.h"

using namespace std;

CMSketch::CMSketch(int w, int c, int hw, int hc)
{
	sketch = new Counter[c*w];
	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;
	fun_counter = new BOBHash[hash_counter];
	fun_word = new BOBHash[hash_word];
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

lint CMSketch::Query(const char *str)
{
	lint res = MAX_NUM;
	int *index_word = new int[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int *index_counter = new int[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_counter; i++)
	{
		int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
		res = min(res, sketch[index].counter);
	}
	return res;
}

void CMSketch::Insert(const char *str)
{
	int *index_word = new int[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int *index_counter = new int[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_counter; i++)
	{
		int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
		if(sketch[index].counter < (1 << COUNTER_SIZE) - 1)
		{
			sketch[index].counter ++;
		}
	}
}

void CMSketch::Delete(const char *str)
{
	int *index_word = new int[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int *index_counter = new int[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_counter; i++)
	{
		int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
		if(sketch[index].counter > 0)
		{
			sketch[index].counter --;
		}
	}
}