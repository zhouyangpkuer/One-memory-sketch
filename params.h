#ifndef _PARAMS_H
#define _PARAMS_H

#define WORD_SIZE 64
#define COUNTER_SIZE 16

#define ON_COUNTER_SIZE 4
#define OFF_COUNTER_SIZE 28

#define COUNTER_PER_WORD (WORD_SIZE / COUNTER_SIZE)
#define ONCHIP_COUNTER_PER_WORD (WORD_SIZE / ON_COUNTER_SIZE)

#define HASH_COUNTER 3
#define HASH_WORD 3
// #define MEMORY 11.4440918
#define MEMORY 1.50

#define MAX_NUM ((1<<COUNTER_SIZE)-1)

#define N_QUERY 1000000
#define N_INSERT 10000000

#define max_term 21
#define pm 1.50//MB
#define hash_num_cb 3
#define size1 5
#define size2 32
#define counter_ratio 10

typedef unsigned long long lint;

#endif //_PARAMS_H