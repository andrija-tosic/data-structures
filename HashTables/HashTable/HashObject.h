#pragma once
#include <iostream>
template<typename K, typename V>
class HashObject {

	template<typename K, typename V>
	friend class HashTable;
	
	template<typename K, typename V>
	friend class ChainedHashTable;

	template<typename K, typename V>
	friend class OpenScatterTable;

protected:
	K key;
	V value;

public:
	HashObject() {
		key = K();
		value = V();
	}
	
	HashObject(const K& k) {
		key = k;
		value = V();
	}
	
	HashObject(const K& k, const V& v) {
		key = k;
		value = v;
	}

	~HashObject() {}

	HashObject& operator=(const HashObject& obj) {
		key = obj.key;
		value = obj.value;
		return *this;
	}

	bool operator==(const HashObject& obj) {
		return value == obj.value;
	}

	bool operator!=(const HashObject& obj) {
		return value != obj.value;
	}

	friend std::ostream& operator<<(std::ostream& out, const HashObject& obj) {
		obj.print(out);
		return out;
	}

	K getKey() {
		return key;
	}

	V getValue() {
		return value;
	}

	bool isKeyEqual(const K& k) {
		return key == k;
	}

	void print(std::ostream& out) const {
		out << key << "|" << value;
	}
};