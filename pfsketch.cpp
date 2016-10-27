#include "pfsketch.h"
// #include <iostream>
// #define pf_cu
//the counter across many words is chosen with random, and adds one
using namespace std;
PFSketch::PFSketch(int w, int c, int hw, int hc)
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

PFSketch:: ~PFSketch()
{	
	delete []hashedcounter_per_word;
	// delete []hash_value;
}

lint PFSketch::Query(const char *str)
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

void PFSketch::Insert(const char *str)
{
	unsigned long long res = MAX_NUM;
	int temp = 0;

	int cnt_counter = 0;

	int base, rest;
	// int i = rand() % hash_word;
	int counterID = rand() % hash_counter;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			if(cnt_counter == counterID)
			{
				rest = fun_counter[cnt_counter].run((const unsigned char *)str, strlen(str)) % counter_per_word;
				res = (unsigned long long)sketch[base + rest].counter;
				if(res < (1 << COUNTER_SIZE) - 1)
					sketch[base + rest].counter = res + 1;
			}
			cnt_counter++;
		}
	}
	packages_num++;
}

void PFSketch::Delete(const char *str)
{

}