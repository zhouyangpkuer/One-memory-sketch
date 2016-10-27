#include "cbsketch_origin.h"
#include <iostream>
using namespace std;

CBSketch::CBSketch(int counter_num_layer1, int counter_num_layer2, 
		int counter_size_layer1, int counter_size_layer2, int hash_num)
{	
	srand(time(0));
	cnt1 = counter_num_layer1;
	cnt2 = counter_num_layer2;
	thre1 = pow(2, counter_size_layer1);
	thre2 = pow(2, counter_size_layer2);
	k = hash_num;


	carrier_val = new int[cnt1];
	carrier_est = new int[cnt1];
	est_rlt = new int[N_QUERY];


	num = new int[cnt2];
	src = new unsigned int *[cnt2];
	for(int i = 0; i < cnt2; i++)
	{
		src[i] = new unsigned int[100];
	}
	uai = new int *[cnt2];
	for(int i = 0; i < cnt2; i++)
	{
		uai[i] = new int[100];
	}
	
	via = new int *[cnt1];
	for(int i = 0; i < cnt1; i++)
	{
		via[i] = new int[k];
	}
	oldvia = new int *[cnt1];
	for(int i = 0; i < cnt1; i++)
	{
		oldvia[i] = new int[k];
	}
	dst = new unsigned int *[cnt1];
	for(int i = 0; i < cnt1; i++)
	{
		dst[i] = new unsigned int[k];
	}

	num2 = new int[cnt1];
	src2 = new unsigned int *[cnt1];
	for(int i = 0; i < cnt1; i++)
	{
		src2[i] = new unsigned int[50];
	}

	uai2 = new int *[cnt1];
	for(int i = 0; i < cnt1; i++)
	{
		uai2[i] = new int[50];
	}

	via2 = new int *[N_QUERY];
	for(int i = 0; i < N_QUERY; i++)
	{
		via2[i] = new int[k];	
	}
	oldvia2 = new int *[N_QUERY];
	for(int i = 0; i < N_QUERY; i++)
	{
		oldvia2[i] = new int[k];		
	}
	dst2 = new unsigned int *[N_QUERY];
	for(int i = 0; i < N_QUERY; i++)
	{
		dst2[i] = new unsigned int[k];		
	}

	B1 = (int *) malloc(sizeof(int)*cnt1);
	B2 = (int *) malloc(sizeof(int)*cnt2);
	sb = (bool *) malloc(sizeof(bool)*cnt1);
	for (int i = 0; i < cnt1; i++) 
	{
		B1[i] = 0;
		sb[i] = false;
	}
	for (int i = 0; i < cnt2; i++) 
		B2[i] = 0;
}


bool CBSketch::Insert(unsigned int out, unsigned int dst, int val) 
{
	bool result = true;
	unsigned int hashIndex, bitIndex;

	for (int i = 1; i <= k; i++)
	{
		bitIndex = hash2(i, out, 1, cnt1);
		B1[bitIndex] += val;
	}
	return true;
}

bool CBSketch::carrier() 
{
	bool result = true;
	unsigned int bitIndex;
	for (int i = 0; i < cnt1; i++)
	{
		int tmp = B1[i] / thre1;
		carrier_val[i] = tmp;
		B1[i] %= thre1;
		if (tmp > 0)
		{
			sb[i] = true;
			for (int j = 1; j <= k; j++)
			{
				bitIndex = hash2(j, i, 1, cnt2);
				B2[bitIndex] += tmp;
			}
		}
	}
	return true;
}

void CBSketch::decode(int iteration_num, int flow_num) 
{
	out = flow_num;
	term = iteration_num;

	/* decode the second layer */
	int minflow = 1;
	unsigned int hashIndex, bitIndex;

	int mycnt = 0;
	for (int i = 0; i < cnt1; i++)
	{
		if (sb[i])
		{
			mycnt++;
		}
	}
	printf("cnt1 = %d, cnt2 = %d, my cnt = %d\n", cnt1, cnt2, mycnt);

	/************************************************************************/
	/* For layer2 -> layer1 reconstruction                                  */
	/************************************************************************/
	/* determine the map */
	for (int i = 0; i < this->cnt1; i++)
	{
		for (int j = 1; j <= this->k; j++)
		{	
			bitIndex = hash2(j, i, 1, this->cnt2); // left part
			dst[i][j-1] = bitIndex;
			via[i][j-1] = 0;
	
			uai[bitIndex][num[bitIndex]] = 0;
			src[bitIndex][num[bitIndex]++] = i;
			if (num[bitIndex] > 199)
			{
				printf("How come, overflow??\n");
				return;
			}
		}
	}


//	return;
	int t;
	for (t = 1; t < 100000; t++) // iteration
	{
		for (int i = 0; i < cnt1; i++)
		{
			for (int j = 0; j < this->k; j++)
			{
				oldvia[i][j] = via[i][j];
			}
		}

		// get uai
		for (int i = 0; i < cnt2; i++) // for each dst
		{
			for (int j = 0; j < num[i]; j++) // for all its src of a given dst
			{
				int sum = 0;
				unsigned int sip = src[i][j];
				for (int j2 = 0; j2 < num[i]; j2++)
				{
					if (j2 != j)
					{
						unsigned int tsip = src[i][j2];
						for (int j3 = 0; j3 < this->k; j3++)
						{
							if (dst[tsip][j3] == i)
							{
								sum += via[tsip][j3];
								break;
								//only add one ?!
							}
						}
					}
				}
				uai[i][j] = this->B2[i] - sum; 
				if (uai[i][j] < minflow)
				{
					uai[i][j] = minflow;
				}
			}
		}

		// get via
		for (int i = 0; i < cnt1; i++)
		{
			if (!this->sb[i])
			{
				continue;
			}

			if (t % 2 == 1) // odd, get min value
			{
				// compute via[i][0];
				for (int ii = 0; ii < this->k; ii++) // each src has k dst (via)
				{	
					unsigned int dip = dst[i][ii];
					int tmp = 100000000;
					for (int i2 = 0; i2 < this->k; i2++) // for each via, find all the vja
					{
						if (i2 != ii)
						{
							unsigned int tdip = dst[i][i2];
							for (int i3 = 0; i3 < num[tdip]; i3++)
							{
								if (src[tdip][i3] == i)
								{
									if (tmp > uai[tdip][i3])
									{
										tmp = uai[tdip][i3];
									}
									break;
								}
							}
						}
					}
					via[i][ii] = tmp;
				}
			}
			else // even, get max value
			{
				for (int ii = 0; ii < this->k; ii++)
				{	
					unsigned int dip = dst[i][ii];
					int tmp = minflow;
					for (int i2 = 0; i2 < this->k; i2++)
					{
						if (i2 != ii)
						{
							unsigned int tdip = dst[i][i2];
							for (int i3 = 0; i3 < num[tdip]; i3++)
							{
								if (src[tdip][i3] == i)
								{
									if (tmp < uai[tdip][i3])
									{
										tmp = uai[tdip][i3];
									}
									break;
								}
							}
						}
					}
					via[i][ii] = tmp;
				}
			}
		}

		bool flag = true;
		for (int i = 0; i < this->cnt1; i++)
		{
			if (!this->sb[i])
			{
				continue;
			}
			for (int j = 0; j < this->k; j++)
			{
				if (oldvia[i][j] != via[i][j])
				{
					flag = false;
					break;
				}
			}
		}
		printf("%d\n", t);
		if (flag || t >= term)
		{
			break;
		}
	}

	for (int i = 0; i < cnt1; i++)
	{
		if (this->sb[i])
		{
			if (t % 2 == 1)
			{
				int tmp = 10000000;
				for (int ii = 0; ii < this->k; ii++)
				{
					unsigned int tdip = dst[i][ii];
					for (int i3 = 0; i3 < num[tdip]; i3++)
					{
						if (src[tdip][i3] == i)
						{
							if (tmp > uai[tdip][i3])
							{
								tmp = uai[tdip][i3];
							}
						}
					}
				}
				/*if (carrier_val[i] != tmp)
				{
					printf("got one\n");
				}*/
		//		printf("%d %d %d\n", i, carrier_val[i], tmp);
				this->B1[i] += tmp * thre1;
			}
			else
			{
				int tmp = 0;
				for (int ii = 0; ii < this->k; ii++)
				{
					unsigned int tdip = dst[i][ii];
					for (int i3 = 0; i3 < num[tdip]; i3++)
					{
						if (src[tdip][i3] == i)
						{
							if (tmp < uai[tdip][i3])
							{
								tmp = uai[tdip][i3];
							}
						}
					}
				}
				if (tmp == 0)
				{
					printf("Impossible\n");
					return;
				}
				/*if (carrier_val[i] != tmp)
				{
					printf("got one\n");
				}*/
				this->B1[i] += tmp * thre1;
			}	
		}
	}

	/************************************************************************/
	/*  From layer 1 -> flow                                                */
	/************************************************************************/
	/* determine the map */
	for (int i = 0; i < out; i++)
	{
		for (int j = 1; j <= this->k; j++)
		{			
			bitIndex = hash2(j, i, 1, this->cnt1); // left part
			dst2[i][j-1] = bitIndex;
			via2[i][j-1] = 0;
	
			uai2[bitIndex][num2[bitIndex]] = 0;
			src2[bitIndex][num2[bitIndex]++] = i;
			if (num2[bitIndex] > 99)
			{
				printf("How come??\n");
				return;
			}
		}
	}
	
	for (int t = 1; t < 100000; t++) // iteration
	{
		for (int i = 0; i < out; i++)
		{
			for (int j = 0; j < this->k; j++)
			{
				oldvia2[i][j] = via2[i][j];
			}
		}

		// get uai
		for (int i = 0; i < cnt1; i++) // for each dst
		{
			for (int j = 0; j < num2[i]; j++) // for all its src of a given dst
			{
				int sum = 0;
				unsigned int sip = src2[i][j];
				for (int j2 = 0; j2 < num2[i]; j2++)
				{
					if (j2 != j)
					{
						unsigned int tsip = src2[i][j2];
						for (int j3 = 0; j3 < this->k; j3++)
						{
							if (dst2[tsip][j3] == i)
							{
								sum += via2[tsip][j3];
								break;
							}
						}
					}
				}
				uai2[i][j] = this->B1[i] - sum; 
				if (uai2[i][j] < minflow)
				{
					uai2[i][j] = minflow;
				}
			}
		}

		// get via
		for (int i = 0; i < out; i++)
		{
			if (t % 2 == 1) // odd, get min value
			{
				// compute via[i][0];
				for (int ii = 0; ii < this->k; ii++) // each src has k dst (via)
				{	
					unsigned int dip = dst2[i][ii];
					int tmp = 100000000;
					for (int i2 = 0; i2 < this->k; i2++) // for each via, find all the vja
					{
						if (i2 != ii)
						{
							unsigned int tdip = dst2[i][i2];
							for (int i3 = 0; i3 < num2[tdip]; i3++)
							{
								if (src2[tdip][i3] == i)
								{
									if (tmp > uai2[tdip][i3])
									{
										tmp = uai2[tdip][i3];
									}
									break;
								}
							}
						}
					}
					if (tmp == 0)
					{
						printf("How come?");
					}
					via2[i][ii] = tmp;
				}
			}
			else // even, get max value
			{
				for (int ii = 0; ii < this->k; ii++)
				{	
					unsigned int dip = dst2[i][ii];
					int tmp = minflow;
					for (int i2 = 0; i2 < this->k; i2++)
					{
						if (i2 != ii)
						{
							unsigned int tdip = dst2[i][i2];
							for (int i3 = 0; i3 < num2[tdip]; i3++)
							{
								if (src2[tdip][i3] == i)
								{
									if (tmp < uai2[tdip][i3])
									{
										tmp = uai2[tdip][i3];
									}
									break;
								}
							}
						}
					}
					via2[i][ii] = tmp;
				}
			}
		}

		bool flag = true;
		for (int i = 0; i < out; i++)
		{
			for (int j = 0; j < this->k; j++)
			{
				if (oldvia2[i][j] != via2[i][j])
				{
					flag = false;
					break;
				}
			}
		}
		printf("%d\n", t);
		if (flag || t >= term)
		{
			break;
		}
	}

	for (int i = 0; i < out; i++)
	{
		if (t % 2 == 1)
		{
			int tmp = 10000000;
			for (int ii = 0; ii < this->k; ii++)
			{
				unsigned int tdip = dst2[i][ii];
				for (int i3 = 0; i3 < num2[tdip]; i3++)
				{
					if (src2[tdip][i3] == i)
					{
						if (tmp > uai2[tdip][i3])
						{
							tmp = uai2[tdip][i3];
						}
					}
				}
			}
			est_rlt[i] = tmp;
			// this->B1[i] += tmp * thre1;
		}
		else
		{
			int tmp = 0;
			for (int ii = 0; ii < this->k; ii++)
			{
				unsigned int tdip = dst2[i][ii];
				for (int i3 = 0; i3 < num2[tdip]; i3++)
				{
					if (src2[tdip][i3] == i)
					{
						if (tmp < uai2[tdip][i3])
						{
							tmp = uai2[tdip][i3];
						}
					}
				}
			}
			if (tmp == 0)
			{
				printf("Impossible\n");
				return;
			}	
			est_rlt[i] = tmp;
			// this->B1[i] += tmp * thre1;
		}	
	}
	// free(this);
}

CBSketch:: ~CBSketch()
{	
	free(B1);
	free(B2);
	free(sb);

	delete []carrier_val;
	delete []carrier_est;
	delete []est_rlt;

	delete []num;
	for(int i = 0; i < cnt2; i++)
	{
		delete []src[i];
		delete []uai[i];
	}	
	delete []src;
	delete []uai;

	for(int i = 0; i < cnt1; i++)
	{
		delete []via[i];
		delete []oldvia[i];
		delete []dst[i];
	}
	delete []via;
	delete []oldvia;
	delete []dst;

	delete []num2;
	for(int i = 0; i < cnt1; i++)
	{
		delete []src2[i];
		delete []uai2[i];
	}	
	delete []src2;
	delete []uai2;

	for(int i = 0; i < N_QUERY; i++)
	{
		delete []via2[i];
		delete []oldvia2[i];
		delete []dst2[i];
	}
	delete []via2;
	delete []oldvia2;
	delete []dst2;
}

lint CBSketch::Query(const char *str)
{

}

void CBSketch::Insert(const char *str)
{

}

void CBSketch::Delete(const char *str)
{

}
