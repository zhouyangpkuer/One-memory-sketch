#include "cusketch_nonconflict.h"
#include <iostream>
using namespace std;
NCUSketch::NCUSketch(int w, int c, int hw, int hc)
{
	sketch = new Counter[c*w];
	memset(sketch, 0, sizeof(sketch));

	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;

	hash_value = new int[hc];

	int base = hc / hw;
	int rest = hc - base * hw;
	hashedcounter_per_word = new int[hash_word];
	memset(hashedcounter_per_word, 0, sizeof(hashedcounter_per_word));

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

NCUSketch:: ~NCUSketch()
{	
	delete []hashedcounter_per_word;
	delete []hash_value;
}

lint NCUSketch::Query(const char *str)
{
	lint res = MAX_NUM;
	int cnt_counter = 0;
	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter++].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			res = min(sketch[base + rest].counter, res);
		}
	}
	return res;
}

void NCUSketch::Insert(const char *str)
{
	lint res = MAX_NUM;
	int temp = 0;

	int cnt_counter = 0;

	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			
			res = min(sketch[base + rest].counter, res);
			hash_value[cnt_counter] = base + rest;

			cnt_counter++;
		}
	}
	for(int i = 0; i < hash_counter; i++)
	{
		if(sketch[hash_value[i]].counter == res)
			sketch[hash_value[i]].counter ++;
	}
}

void NCUSketch::Delete(const char *str)
{

}