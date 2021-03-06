#include "cmsketch_nonconflict.h"

using namespace std;

NCMSketch::NCMSketch(int w, int c, int hw, int hc)
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

NCMSketch::~NCMSketch()
{
	delete [] fun_word;
	delete [] fun_counter;
}

lint NCMSketch::Query(const char *str)
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
		res = min(res, (unsigned long long) sketch[index].counter);
	}
	delete [] index_counter;
	delete [] index_word;
	return (lint)res;
}

void NCMSketch::Insert(const char *str)
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
		if((unsigned long long) sketch[index].counter < (1 << COUNTER_SIZE) - 1)
		{
			sketch[index].counter ++;
		}
	}
	delete [] index_word;
	delete [] index_counter;
}

void NCMSketch::Delete(const char *str)
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
	}
	delete [] index_word;
	delete [] index_counter;
}