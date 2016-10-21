#include "pfsketch_cu.h"
// #include <iostream>
using namespace std;
PFSketch_cu::PFSketch_cu(int w, int c, int hw, int hc)
{
	srand(time(0)); 

	sketch = new Counter[c*w];
	memset(sketch, 0, sizeof(sketch));

	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;
	packages_num = 0;

	int base = hc / hw;
	int rest = hc - base * hw;
	hashedcounter_per_word = new int[hash_word];
	memset(hashedcounter_per_word, 0, sizeof(hashedcounter_per_word));

	fun_counter = new BOBHash[hash_counter];
	fun_word = new BOBHash[hash_word];

	for(int i = 0; i < hash_word; i++)
	{
		if(i < rest)
			hashedcounter_per_word[i] = base + 1;
		else
			hashedcounter_per_word[i] = base;
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

PFSketch_cu:: ~PFSketch_cu()
{	
	delete []hashedcounter_per_word;
	// delete []hash_value;
}

lint PFSketch_cu::Query(const char *str)
{
	lint res = 0;
	int cnt_counter = 0;
	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter++].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			res += sketch[base + rest].counter;
		}
	}
	return res - hash_counter * packages_num / (word_num * counter_per_word * 1.0);
}

void PFSketch_cu::Insert(const char *str)
{
	lint res = MAX_NUM;
	int temp = 0;

	int cnt_counter = 0;

	int base, rest;
	int hash_value;
	int word_i = rand() % hash_word;

	base = counter_per_word * (fun_word[word_i].run((const unsigned char *)str, strlen(str)) % word_num);
	
	for(int i = 0; i < word_i; i++)
	{
		cnt_counter += hashedcounter_per_word[i];
	}

	for(int j = 0; j < hashedcounter_per_word[word_i]; j++)
	{
		rest = fun_counter[cnt_counter].run((const unsigned char *)str, strlen(str)) % counter_per_word;
		if(sketch[base + rest].counter < res)
		{
			res = sketch[base + rest].counter;
			hash_value = base + rest;
		}
		cnt_counter++;
	}
	sketch[hash_value].counter ++;
	packages_num++;
}

void PFSketch_cu::Delete(const char *str)
{

}