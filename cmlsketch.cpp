#include "cmlsketch.h"

using namespace std;
CMLSketch::CMLSketch(int w, int c, int hw, int hc)
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

CMLSketch::~CMLSketch()
{
	delete [] fun_word;
	delete [] fun_counter;
}

bool CMLSketch::decision(int c)
{
	double r = distribution(generator);
    double lim = pow(b, -c);
    return r < lim;
}

double CMLSketch::pointv(int c)
{
	return c == 0 ? 0 : pow(b, c - 1);
}

lint CMLSketch::Query(const char *str)
{
	lint c = MAX_NUM;
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
		c = min(c, sketch[index].counter);
	}

	delete []index_word;
	delete []index_counter;
	return c <= 1 ? pointv(c) : (int)(round((1 - pointv(c + 1)) / (1 - b)));
}

void CMLSketch::Insert(const char *str)
{
	lint c = MAX_NUM;
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
		c = min(c, sketch[index].counter);
	}
	if(decision(c))
	{
		for(int i = 0; i < hash_counter; i++)
		{
			int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
			if(sketch[index].counter < (1 << COUNTER_SIZE) - 1)	
				sketch[index].counter ++;
		}
	}
	
	delete []index_word;
	delete []index_counter;
}

void CMLSketch::Delete(const char *str)
{
	
}