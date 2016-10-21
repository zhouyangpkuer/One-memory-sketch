#ifndef _PARAMS_H
#define _PARAMS_H

#define COUNTER_SIZE 6
#define WORD_SIZE 64
#define COUNTER_PER_WORD 32
#define HASH_COUNTER 3
#define HASH_WORD 1
#define WORD_NUM (1<<16)
#define MAX_NUM ((1<<COUNTER_SIZE)-1)

#define N_QUERY 1000000
#define N_INSERT 10000000

typedef long long lint;


#endif //_PARAMS_H