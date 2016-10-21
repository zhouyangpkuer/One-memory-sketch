#ifndef _CUSKETCH_H
#define _CUSKETCH_H

#include "params.h"
#include "sketch.h"

class CUSketch: public sketch
{	
public:
	CUSketch(int _word_num)
	{
		word_num = _word_num;
		sketch = new Counter[_word_num];
	}


};

#endif _CUSKETCH_H

