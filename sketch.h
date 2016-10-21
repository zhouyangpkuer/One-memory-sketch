#include "params.h"

struct Counter
{
	lint counter : COUNTER_SIZE;
};

class Sketch
{
private:
	int width;
	int depth;
	Counter *sketch;
public:
	Sketch(int d, int w);
	~Sketch();
	virtual void Insert(char *str);
	virtual lint Query(char *str);
	virtual void Delete(char *str);
};