#include "csketch_offchip.h"
using namespace std;

CSketch_off::CSketch_off(int w, int c, int hw, int hc)
{
	sketch = new Counter[w*c];
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

	fun_word_f = new BOBHash[hash_word];
	fun_counter_f = new BOBHash[hash_counter];
	fun_counter_g = new BOBHash[hash_counter];
	res = new lint[hash_counter];
	index_counter = new int[hash_counter];
	index_word = new int[hash_word];
	
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

CSketch_off::~CSketch_off()
{
	delete [] fun_word_f;
	delete [] fun_counter_g;
	delete [] fun_counter_f;
	delete [] offsketch;
	delete [] index_counter;
	delete [] index_word;
	delete [] res;
	printf("success exit form CSketch_off!");

}

lint CSketch_off::Query(const char *str)
{
	int temp = 0;
	//res = new lint[hash_counter];
	//int *index_word = new int[hash_word];
	// vector<int> used;
	used.clear();
	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word_f[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	//int *index_counter = new int[hash_counter];
	for(int i = 0; i < hash_counter; i++)
	{
		index_counter[i] = fun_counter_f[i].run((const unsigned char *)str, strlen(str)) % counter_per_word;
	}
	for(int i = 0; i < hash_counter; i++)
	{
		int index = index_word[i%hash_word] * counter_per_word + index_counter[i];
		if(find(used.begin(), used.end(), index) != used.end())
		{
			temp ++;
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
		res[i - temp] = ((unsigned long long)(sketch[index].counter & 15) + offsketch[index].counter * (1 << (ON_COUNTER_SIZE))) * para;
	}
	sort(res, res + hash_counter - temp);
	temp = hash_counter - temp;
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
	//delete [] index_counter;
	//delete [] index_word;
	return r;
}

void CSketch_off::Insert(const char *str)
{
	// int *index_word = new int[hash_word];
	// vector<int> used;
	used.clear();

	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word_f[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	// int *index_counter = new int[hash_counter];
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
		// if((para == 1 && sketch[index].counter < (1 << (COUNTER_SIZE - 1)) - 1) || 
		// 	(para == -1 && sketch[index].counter > (-(1 << (COUNTER_SIZE - 1))))) 
		// 	sketch[index].counter += para;
		if(para == 1)
		{
			if((unsigned long long)(sketch[index].counter & 15) == (1 << (ON_COUNTER_SIZE)) - 1)
			// if(sketch[index].counter == (1 << (ON_COUNTER_SIZE - 1)) - 1)
			{
				sketch[index].counter = 0;
				offsketch[index].counter ++;
			}
			else
			{
				sketch[index].counter ++;
			}
		}
		else
		{
			// if(sketch[index].counter == (-(1 << (ON_COUNTER_SIZE - 1))))
			if((unsigned long long)(sketch[index].counter & 15) == 0)
			{
				sketch[index].counter --;
				offsketch[index].counter --;
			}	
			else
			{
				sketch[index].counter--;
			}
		}
	}
	// delete [] index_counter;
	// delete [] index_word;
}

void CSketch_off::Delete(const char *str)
{
	// int *index_word = new int[hash_word];
	// vector<int> used;
	used.clear();

	for(int i = 0; i < hash_word; i++)
	{
		index_word[i] = fun_word_f[i].run((const unsigned char *)str, strlen(str)) % word_num;
	}
	// int *index_counter = new int[hash_counter];
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
		// if((para == -1 && sketch[index].counter < (1 << (COUNTER_SIZE - 1)) - 1) || 
		// 	(para == 1 && sketch[index].counter > (-(1 << (COUNTER_SIZE - 1))))) 
		// 	sketch[index].counter -= para;
		if(para == -1)
		{
			if(sketch[index].counter == (1 << (ON_COUNTER_SIZE - 1)) - 1)
			{
				sketch[index].counter = 0;
				offsketch[index].counter ++;
			}
			else
			{
				sketch[index].counter ++;
			}
		}
		else
		{
			if(sketch[index].counter == (-(1 << (ON_COUNTER_SIZE - 1))))
			{
				sketch[index].counter = 0;
				offsketch[index].counter --;
			}	
			else
			{
				sketch[index].counter--;
			}
		}
	}
	// delete [] index_word;
	// delete [] index_counter;
}