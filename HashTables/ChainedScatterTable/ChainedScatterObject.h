#pragma once
#include "../HashTable/ScatterObject.h"

template<typename K, typename V>
class ChainedScatterObject : public ScatterObject<K, V> {
private:
	unsigned int next;

	template<typename K, typename V>
	friend class ChainedScatterTable;

public:
	ChainedScatterObject() : ScatterObject<K, V>() {
		next = -1;
	}
	ChainedScatterObject(const K& key) : ScatterObject<K, V>(key) {
		next = -1;
	}
	ChainedScatterObject(const K& key, const V& value) : ScatterObject<K, V>(key, value) {
		next = -1;
	}
	ChainedScatterObject(const K& key, const V& value, const unsigned int& n) : ScatterObject<K, V>(key, value) {
		next = n;
	}
};