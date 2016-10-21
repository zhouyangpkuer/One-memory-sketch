#include "params.h"

struct Counter
{
	lint counter : COUNTER_SIZE;
};

class Sketch
{
private:
	int word_num;
	int counter_per_word;
	int hash_counter;
	int hash_word;
	Counter *sketch;
public:
	// Sketch(int w, int c, int hw, int hc);
	virtual void Insert(char *str) = 0;
	virtual lint Query(char *str) = 0;
	virtual void Delete(char *str) = 0;
	virtual ~Sketch()
	{
		delete[] sketch;
	}
};