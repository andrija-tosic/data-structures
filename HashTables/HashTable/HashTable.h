#pragma once
#include "HashObject.h"

template<typename K, typename V>
class HashTable {
protected:
	unsigned int length;
	unsigned int count;

	virtual unsigned int f(const int& i) const { // primary transformation: int => unsigned int
		return abs(i);
	}
	
	virtual unsigned int f(const double& d) const { // primary transformation: double => unsigned int
		if (d == 0) {
			return 0;
		}
		else {
			int exponent;
			double mantisa = frexp(d, &exponent);
			return (unsigned int)((2 * fabs(mantisa) - 1) * ~0U);
		}
	}

	virtual unsigned int f(const char* s) const { // primary transformation: string => unsigned int
		unsigned int res = 0;
		unsigned int a = 7; // character is a 7-bit ASCII code
		for (int i = 0; s[i] != '\0'; i++) {
			res = res << a ^ s[i];
		}
		return res;
	}

	virtual unsigned int g(const unsigned int& i) const { // secondary transformation: unsigned int => index
		return (i + 1) % length;
	}

	unsigned int hash(const K& key) const { // key => index
		return g(f(key));
	}

public:
	unsigned int getLength() const {
		return length;
	}

	virtual double getLoadFactor() const {
		return (double)count / (double)length;
	}

	virtual void insert(const K& key, const V& value) = 0;
	
	virtual V withdraw(const K& key) = 0;

	virtual V find(const K& key) const = 0;
};