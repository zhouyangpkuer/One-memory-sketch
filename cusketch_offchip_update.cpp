#include "cusketch_offchip_update.h"
using namespace std;
CUSketch_off_up::CUSketch_off_up(int w, int c, int hw, int hc)
{
	sketch = new Counter[c*w];
	// memset(sketch, 0, sizeof(sketch));
	for(int i = 0; i < c*w; i++)
	{
		sketch[i].counter = 0;
	}
	offsketch = new OffCounter[c*w];
	// memset(offsketch, 0, sizeof(offsketch));
	for(int i = 0; i < c*w; i++)
	{
		offsketch[i].counter = 0;
	}

	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;

	hash_value = new int[hc];

	int base = hc / hw;
	int rest = hc - base * hw;
	
	hashedcounter_per_word = new int[hash_word];
	
	fun_counter = new BOBHash[hash_counter];
	fun_word = new BOBHash[hash_word];
	// cout << "hello 1" << endl;
	
	for(int i = 0; i < hash_word; i++)
	{
		if(i < rest)
			hashedcounter_per_word[i] = base + 1;
		else
			hashedcounter_per_word[i] = base;
	}

	// cout << "hello 2" << endl;

	for(int i = 0; i < hash_counter; i++)
	{
		fun_counter[i].initialize(i+1);
	}
	// cout << "hello 2.5" << endl;

	for(int i = 0; i < hash_word; i++)
	{
		fun_word[i].initialize(i+1+hash_counter);
	}
	// cout << "hello 3" << endl;

}

CUSketch_off_up:: ~CUSketch_off_up()
{	
	delete []hashedcounter_per_word;
	delete []hash_value;
}

lint CUSketch_off_up::Query(const char *str)
{
	unsigned long long res = MAX_NUM;
	int cnt_counter = 0;
	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter++].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			res = min((unsigned long long)(sketch[base + rest].counter + offsketch[base + rest].counter * (1 << ON_COUNTER_SIZE)), res);
		}
	}
	return (lint)res;
}

void CUSketch_off_up::Insert(const char *str)
{
	unsigned long long res = MAX_NUM;
	int temp = 0;

	int cnt_counter = 0;

	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			
			res = min((unsigned long long)(sketch[base + rest].counter), res);
			
			hash_value[cnt_counter] = base + rest;

			cnt_counter++;
		}
	}
	for(int i = 0; i < hash_counter; i++)
	{
		if((unsigned long long)(sketch[hash_value[i]].counter) == res)
		{
			if(sketch[hash_value[i]].counter == (1 << ON_COUNTER_SIZE) - 1)
			{
				sketch[hash_value[i]].counter = 0;
				offsketch[hash_value[i]].counter++;	
			}
			else
			{
				sketch[hash_value[i]].counter ++;
			}
		}
	}
}

void CUSketch_off_up::Delete(const char *str)
{

}
