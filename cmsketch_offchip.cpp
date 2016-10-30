#include "cmsketch_offchip.h"

using namespace std;

CMSketch_off::CMSketch_off(int w, int c, int hw, int hc)
{
	sketch = new Counter[c*w];
	offsketch = new OffCounter[c*w];
	// memset(offsketch, 0, sizeof(offsketch));
	for(int i = 0; i < c*w; i++)
	{
		offsketch[i].counter = 0;
		sketch[i].counter = 0;
	}

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

CMSketch_off::~CMSketch_off()
{
	delete [] fun_word;
	delete [] fun_counter;
	delete [] offsketch;
}

lint CMSketch_off::Query(const char *str)
{
	unsigned long long res = MAX_NUM;
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
		res = min(res, (unsigned long long)(sketch[index].counter + offsketch[index].counter * (1 << ON_COUNTER_SIZE)));
	}
	delete [] index_counter;
	delete [] index_word;
	return (lint)res;
}

void CMSketch_off::Insert(const char *str)
{
	int *index_word = new int[hash_word];
	vector<int> used;
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
		if(find(used.begin(), used.end(), index) != used.end()) continue;
		used.push_back(index);
		if((unsigned long long)sketch[index].counter == (1 << ON_COUNTER_SIZE) - 1)
		{
			sketch[index].counter = 0;
			offsketch[index].counter++;	
		}
		else
		{
			sketch[index].counter ++;
		}
	}
	delete [] index_word;
	delete [] index_counter;
}

void CMSketch_off::Delete(const char *str)
{
	int *index_word = new int[hash_word];
	vector<int> used;
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
		if(find(used.begin(), used.end(), index) != used.end()) continue;
		used.push_back(index);
		if(sketch[index].counter != 0)
		{
			sketch[index].counter --;
		}
		else
		{
			sketch[index].counter = (1 << ON_COUNTER_SIZE) - 1;
			offsketch[index].counter --;
		}
	}
	delete [] index_word;
	delete [] index_counter;
}