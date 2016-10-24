#ifndef _CBSKETCH_H
#define _CBSKETCH_H

#include "params.h"
#include "sketch.h"
#include "support.h"
#include <ctime>
#include <stdio.h>
#include <set>
#include <map>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926

using namespace std;

class CBSketch: public Sketch
{	
private:
	int *B1, *B2;
	bool *sb; // status bit
	int cnt1, cnt2;
	int thre1, thre2;
	
	int k;
	int out;
	int term;
	
	int *carrier_val;
	int *carrier_est;
	int *est_rlt;
	
	int *num;
	unsigned int **src;
	int **uai;
	
	int **via;
	int **oldvia;
	unsigned int **dst;
	
	int *num2;
	unsigned int **src2;
	int **uai2;
	
	int **via2;
	int **oldvia2;
	unsigned int **dst2;	
	

	set<unsigned int> srcdstset;

	set <unsigned int> source; //source addresses during the epoch
	map <unsigned int, unsigned int> srcEstimatedDegree;

public:
	CBSketch(int counter_num_layer1, int counter_num_layer2, 
		int counter_size_layer1, int counter_size_layer2, int hash_num);
	
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	
	bool Insert(unsigned int ip_s, unsigned int ip_d, int val);
	bool carrier();
	void decode(int iteration_num, int flow_num);

	int *get_est_rlt()
	{
		return est_rlt;
	}
	~CBSketch();
};

#endif //_CBSKETCH_H

