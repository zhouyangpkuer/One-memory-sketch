#include "sketch.h"
#include "BOBHash.h"

class CMSketch : public Sketch
{
private:
	BOBHash *fun_counter;
	BOBHash *fun_word;
public:
	CMSketch(int w, int c, ing hw, int hc);
	~CMSketch();
};