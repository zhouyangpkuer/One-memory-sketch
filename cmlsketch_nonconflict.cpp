#include <vector>
#include "cmlsketch_nonconflict.h"
using namespace std;
NCMLSketch::NCMLSketch(int w, int c, int hw, int hc)
{
	word_num = w;
	counter_per_word = c;
	hash_word = hw;
	hash_counter = hc;
	b = 1.08;
	sketch = new Counter[w*c];
	fun_word = new BOBHash[hw];
	fun_counter = new BOBHash[hc];
	for(int i = 0; i < hw; i++)
	{
		fun_word[i].initialize(i+1);
	}
	for(int i = 0; i < hc; i++)
	{
		fun_counter[i].initialize(i+1+hw);
	}
}

NCMLSketch::~NCMLSketch()
{
	delete [] fun_counter;
	delete [] fun_word;
}

bool NCMLSketch::decision(int c)
{
	double r = distribution(generator);
    double lim = pow(b, -c);
    return r < lim;
}

double NCMLSketch::pointv(int c)
{
	return c == 0 ? 0 : pow(b, c - 1);
}

lint NCMLSketch::Query(const char *str)
{
	unsigned long long c = MAX_NUM;
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
		c = min(c, (unsigned long long) sketch[index].counter);
	}
	delete [] index_counter;
	delete [] index_word;
	return c <= 1 ? pointv(c) : (int)(round((1 - pointv(c + 1)) / (1 - b)));
}

void NCMLSketch::Insert(const char *str)
{
	lint c = MAX_NUM;
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
		c = min(c, sketch[index].counter);
	}
	if((unsigned long long)c < (1 << COUNTER_SZIE) - 1 && decision(c))
	{
		for(int i = 0; i < hash_counter; i++)
		{
			int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
			if(find(used.begin(), used.end(), index) != used.end()) continue;
			used.push_back(index);
			if(sketch[index].counter == c) sketch[index].counter ++;
		}
	}
	delete [] index_counter;
	delete [] index_word;
}

void NCMLSketch::Delete(const char *str)
{
	
}