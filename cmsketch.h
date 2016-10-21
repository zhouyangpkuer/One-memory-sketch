#include "sketch.h"
#include "BOBHash.h"

class CMSketch : public Sketch
{
private:
	BOBHash hash_counter[HASH_COUNTER];
	BOBHash hash_word[HASH_WORD];
public:
	CMSketch(int w);
	~CMSketch();
}