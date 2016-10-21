#include "params.h"

struct Counter
{
	lint counter : COUNTER_SIZE;
};

class Sketch
{
private:
	int word_num;
	Counter *sketch;
public:
	Sketch(int w);
	virtual void Insert(char *str);
	virtual lint Query(char *str);
	virtual void Delete(char *str);
	virtual ~Sketch()
	{
		delete[] sketch;
	}
};