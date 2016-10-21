#include <cstring>
#include <algorithm>
#include "csketch.h"
using namespace std;

CSketch::CSketch(int w, int c, int hw, int hc)
{
	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;
	sketch = new Counter[w*c];
	fun_word_f = new BOBHash[hash_word];
	fun_counter_f = new BOBHash[hash_counter];
	fun_counter_g = new BOBHash[hash_counter];
	for(int i = 0; i < hash_word; i++)
	{
		fun_word_f[i].initialize(i+1);
	}
	for(int i = 0; i < hash_counter; i++)
	{
		fun_counter_f[i].initialize(i+hash_word+1);
		fun_counter_g[i].initialize(i+hash_word+hash_counter+1);
	}
}

CSketch::~CSketch()
{
	delete [] fun_counter_f;
	delete [] fun_counter_g;
	delete [] fun_word_f;
}

lint CSketch::Query(const char *str)
{
	lint *res = new lint[hash_counter];
	int *index_word = new int[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word_f[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int *index_counter = new int[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter_f[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_counter; i++)
	{
		int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
		int para;
		if(fun_counter_g[i].run((const unsigned char *)str, strlen(str)) % 2 == 0)
		{
			para = 1;
		}
		else
		{
			para = -1;
		}
		res[i] = sketch[index].counter * para;
	}
	sort(res, res + hash_counter);
	lint r;
	if(hash_counter % 2 == 0)
	{
		r = (res[hash_counter / 2] + res[hash_counter / 2 - 1]) / 2;
	}
	else
	{
		r = res[hash_counter / 2];
	}
	delete [] res;
	delete [] index_word;
	delete [] index_counter;
	return r;
}

void CSketch::Insert(const char *str)
{
	int *index_word = new int[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word_f[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int *index_counter = new int[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter_f[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_counter; i++)
	{
		int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
		int para;
		if(fun_counter_g[i].run((const unsigned char *)str, strlen(str)) % 2 == 0)
		{
			para = 1;
		}
		else
		{
			para = -1;
		}
		sketch[index].counter += para;
	}

	delete [] index_word;
	delete [] index_counter;
}

void CSketch::Delete(const char *str)
{
	int *index_word = new int[hash_word];
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word_f[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	int *index_counter = new int[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter_f[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_counter; i++)
	{
		int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
		int para;
		if(fun_counter_g[i].run((const unsigned char *)str, strlen(str)) % 2 == 0)
		{
			para = 1;
		}
		else
		{
			para = -1;
		}
		sketch[index].counter -= para;
	}
	
	delete [] index_word;
	delete [] index_counter;
}