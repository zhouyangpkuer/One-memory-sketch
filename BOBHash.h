#ifndef BOB_HASH_H
#define BOB_HASH_H

class BOBHash
{
public:
	BOBHash();
	~BOBHash();
	BOBHash(uint primeNum);

	void initialize(uint primeNum);

	uint run(const unsigned char * str, uint len);

private:
	uint primeNum;
};

#endif

