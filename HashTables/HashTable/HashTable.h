#pragma once
#include "HashObject.h"

template<typename K, typename V>
class HashTable {
protected:
	unsigned int length;
	unsigned int count;

	virtual unsigned int f(const int& i) { // primary transformation: int => unsigned int
		return abs(i);
	}
	
	virtual unsigned int f(const double& d) { // primary transformation: double => unsigned int
		if (d == 0) {
			return 0;
		}
		else {
			int exponent;
			double mantisa = frexp(d, &exponent);
			return (unsigned int)((2 * fabs(mantisa) - 1) * ~0U);
		}
	}

	virtual unsigned int f(char* s) { // primary transformation: string => unsigned int
		unsigned int res = 0;
		unsigned int a = 7; // character is a 7-bit ASCII code
		for (int i = 0; s[i] != '\0'; i++) {
			res = res << a ^ s[i];
		}
		return res;
	}

	virtual unsigned int g(unsigned int i) { // secondary transformation: unsigned int => index
		return (i + 1) % length;
	}

	unsigned int hash(const K& key) { // key => index
		return g(f(key));
	}

	unsigned int hash(const HashObject<K, V>& obj) { // key => index
		return g(f(obj.key));
	}

public:
	unsigned int getLength() {
		return length;
	}

	virtual double getLoadFactor() {
		return (double)count / (double)length;
	}

	virtual void insert(const HashObject<K, V>& obj) = 0;
	virtual void insert(const K& key, const V& value) = 0;
	
	virtual void withdraw(const HashObject<K, V>& obj) = 0;
	virtual void withdraw(const K& key) = 0;

	virtual HashObject<K, V> find(const K& key) = 0;
	virtual bool isInTable(const K& key) = 0;

	virtual void print() = 0;
};