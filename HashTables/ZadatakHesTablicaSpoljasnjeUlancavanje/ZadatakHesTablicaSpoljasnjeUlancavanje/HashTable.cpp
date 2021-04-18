#include"HashTable.h"

unsigned int HashTable::h(char* key)
{
	return g(f(key));
}

unsigned int HashTable::f(char* key) // djb2 hash
{
	unsigned int hash = 5381;
	int c;
	while (c = *key++) {
#if 0
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
#endif
		hash = ((hash << 5) + hash) ^ c; // hash * 33 xor c
	}
	return hash;

#if 0
	unsigned int h = 0;
	for (int i = 0; i < strlen(key); i++)
		h += key[i];
	return h;
#endif
}

unsigned int HashTable::g(unsigned int key)
{
	return (key * 2,654,435,769) >> (32-6);
}