#include "cusketch_plus.h"
using namespace std;
CUSketch_plus::CUSketch_plus(int w, int c, int hw, int hc)
{
	srand(time(0)); 

	sketch = new Counter[c*w];
	memset(sketch, 0, sizeof(sketch));
	// fprintf(stderr, "%s\n", "1");

	st_min.clear();
	st_max.clear();
	query_str.clear();

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

CUSketch_plus:: ~CUSketch_plus()
{	
	delete []hashedcounter_per_word;
	delete []hash_value;
}

lint CUSketch_plus::Query(const char *str)
{
	query_str.clear();
	unsigned long long res = MAX_NUM;
	int cnt_counter = 0;
	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter++].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			// res = min((unsigned long long)sketch[base + rest].counter, res);
			query_str.push_back((unsigned long long)sketch[base + rest].counter);
		}
	}
	sort(query_str.begin(), query_str.end());
	if(hash_counter % 2 == 0)
		return (query_str[hash_counter / 2] + query_str[hash_counter / 2 - 1]) / 2;
	else
		return query_str[hash_counter / 2];
	// return (lint)res;
}

void CUSketch_plus::Insert(const char *str)
{
	unsigned long long res_min = MAX_NUM;
	unsigned long long res_max = 0;

	int temp = 0;
	st_min.clear();
	st_max.clear();

	int cnt_counter = 0;
	// fprintf(stderr, "%s\n", "2");

	int base, rest;
	for(int i = 0; i < hash_word; i++)
	{
		base = counter_per_word * (fun_word[i].run((const unsigned char *)str, strlen(str)) % word_num);
		for(int j = 0; j < hashedcounter_per_word[i]; j++)
		{
			rest = fun_counter[cnt_counter].run((const unsigned char *)str, strlen(str)) % counter_per_word;
			
			res_min = min((unsigned long long)sketch[base + rest].counter, res_min);
			res_max = max((unsigned long long)sketch[base + rest].counter, res_max);

			hash_value[cnt_counter] = base + rest;
			cnt_counter++;
		}
	}
	
	int cnt = 0;
	set<int>::iterator it;

	// fprintf(stderr, "%s\n", "1");
	
	if(res_min < (1 << COUNTER_SIZE) - 1)
	{
		for(int i = 0; i < hash_counter; i++)
		{
			if((unsigned long long)sketch[hash_value[i]].counter == res_min)
				st_min.insert(hash_value[i]);
		}

		int min_num = st_min.size();
		int select_min_num = rand() % min_num;
	
		for(it = st_min.begin(); it != st_min.end(); it++, cnt++)
		{
			if(cnt == select_min_num)
			{
				sketch[*it].counter++;
				break;
			}
		}
	}

	// fprintf(stderr, "%s\n", "2");

	cnt = 0;
	for(int i = 0; i < hash_counter; i++)
	{
		if((unsigned long long)sketch[hash_value[i]].counter == res_max)
			st_max.insert(hash_value[i]);
	}
	int max_num = st_max.size();
	int select_max_num = rand() % max_num;	
	for(it = st_max.begin(); it != st_max.end(); it++, cnt++)
	{
		if(cnt == select_max_num)
		{
			sketch[*it].counter--;
			break;
		}
	}

	// int min_num = st.size();
	// if(min_num == 1)
	// 	sketch[*st.begin()].counter++;
	// else
	// {
	// 	set<int>::iterator it = st.end();
	// 	st.erase(--it);

	// 	for (it = st.begin(); it != st.end(); it++)
	// 	{
	// 		sketch[*it].counter++;
	// 	}
	// }
}

void CUSketch_plus::Delete(const char *str)
{

}