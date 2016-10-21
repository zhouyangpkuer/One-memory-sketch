#ifndef _CMSKETCH_NONCONFLICT_H
#define _CMSKETCH_NONCONFLICT_H
#include <cstring>
#include <algorithm>
#include "sketch.h"
#include "BOBHash.h"
#include "params.h"
#include <vector>

using namespace std;

class NCMSketch : public Sketch
{
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
public:
	virtual void Insert(const char * str);
	virtual lint Query(const char *str);
	virtual void Delete(const char *str);
	NCMSketch(int w, int c, int hw, int hc);
	virtual ~NCMSketch();
	
};

#endif // _CMSKETCH_NONCONFLICT_H