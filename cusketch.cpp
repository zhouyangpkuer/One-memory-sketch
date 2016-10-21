#include <algorithm>
#include <cstring>
#include "cusketch.h"


CUSketch::CUSketch(int w, int c, int hw, int hc)
{
	sketch = new Counter[c*w];
	memset(Counter, 0, sizeof(Counter));

	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;

	int base = hc / hw;
	int rest = hc - base * hw;
	hashedcounter_per_word = new int[hash_word];
	memset(hashedcounter_per_word, 0, sizeof(hashedcounter_per_word));
	for(int i = 0; i < hash_word; i++)
	{
		if(i < rest)
			hashedcounter_per_word[i] = temp + 1;
		else
			hashedcounter_per_word[i] = temp;
	}


	for(int i = 0; i < hash_counter; i++)
	{
		fun_counter[i].initialize(i+1);
	}
	for(int i = 0; i < hash_word; i++)
	{
		fun_word[i].initialize(i+1+hash_counter);
	}
}

CUSketch:: ~CUSketch()
{	

}

lint CUSketch::Query(char *str)
{
	lint res = (((lint)1) << 63);
	int cnt_counter = 0;
	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num) * counter_per_word;
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter++].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			res = min(sketch[base + rest].counter, res);
		}
	}
	return res;
}

void CUSketch::Insert(char *str)
{
	lint res = (((lint)1) << 63);
	int temp = 0;
	int cnt_counter = 0;
	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num) * counter_per_word;
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter++].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			if(sketch[base + rest].counter < res)
			{
				res = sketch[base + rest].counter;
				temp = base + rest;
			}
		}
	}
	sketch[temp].counter ++;
}