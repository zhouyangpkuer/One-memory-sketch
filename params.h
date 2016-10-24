#ifndef _PARAMS_H
#define _PARAMS_H

#define COUNTER_SIZE 16

#define COUNTER_PER_WORD 32
#define HASH_COUNTER 3
#define HASH_WORD 3

// #define WORD_SIZE 64
// #define WORD_NUM (1<<16)
#define MAX_NUM ((1<<COUNTER_SIZE)-1)

#define N_QUERY 1000000
#define N_INSERT 10000000

#define max_term 41
#define pm 1.00//MB
#define hash_num_cb 3
#define size1 5
#define size2 32
#define counter_ratio 10
typedef long long lint;

#endif //_PARAMS_H