#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include "csketch_nonconflict.h"
using namespace std;

NCSketch::NCSketch(int w, int c, int hw, int hc)
{
	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;
	sketch = new Counter[w*c];
	fun_word_f = new BOBHash[hash_word];
	fun_counter_f = new BOBHash[hash_counter];
	fun_counter_g = new BOBHash[hash_counter];
	res = new lint[hash_counter];
	//index_counter = new int[hash_counter];
	//index_word = new int[hash_word];
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

NCSketch::~NCSketch()
{
	delete [] fun_word_f;
	delete [] fun_counter_g;
	delete [] fun_counter_f;
}

lint NCSketch::Query(const char *str)
{
	int temp = hash_counter;
	//res = new lint[hash_counter];
	int *index_word = new int[hash_word];
	vector<int> used;
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
		if(find(used.begin(), used.end(), index) != used.end())
		{
			temp --;
			continue;
		}
		used.push_back(index);
		int para;
		if(fun_counter_g[i].run((const unsigned char *)str, strlen(str)) % 2 == 0)
		{
			para = 1;
		}
		else
		{
			para = -1;
		}
		res[i - temp + hash_counter] = sketch[index].counter * para;
	}
	sort(res, res + temp);
	lint r;
	if(temp % 2 == 0)
	{
		r = (res[temp / 2] + res[temp / 2 - 1]) / 2;
	}
	else
	{
		r = res[temp / 2];
	}
	//cout << 3 << endl;
	//delete [] res;
	delete [] index_counter;
	delete [] index_word;
	return r;
}

void NCSketch::Insert(const char *str)
{
	int *index_word = new int[hash_word];
	vector<int> used;
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
		if(find(used.begin(), used.end(), index) != used.end()) continue;
		used.push_back(index);
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
	delete [] index_counter;
	delete [] index_word;
}

void NCSketch::Delete(const char *str)
{
	int *index_word = new int[hash_word];
	vector<int> used;
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
		if(find(used.begin(), used.end(), index) != used.end()) continue;
		used.push_back(index);
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