#include"HashTable.h"

unsigned int HashTable::h(char* key)
{
	return g(f(key));
}

unsigned int HashTable::f(char* key)
{
	// primer kljuca: www.something.com
	unsigned i = 4; // uvek pocinje sa www.

	unsigned int hes = 0;

	while (key[i] != '.') {
		hes = ((hes << 5) + hes) + key[i]; /* hash * 33 + c */
		i++;
	}

	return hes;
}

unsigned int HashTable::g(unsigned int key)
{
	unsigned w = 32;
	return (key * key) >> (w - 6);
}

