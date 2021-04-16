#pragma once
#include "../HashTable/HashObject.h"

enum ScatterObjectStatus
{
	unoccupied,
	deleted,
	occupied
};

template<typename K, typename V>
class ScatterObject : public HashObject<K, V> {
protected:
	unsigned int status;

	template<typename K, typename V>
	friend class OpenScatterTable;

public:
	ScatterObject() : HashObject<K, V>() {
		status = ScatterObjectStatus::unoccupied;
	}
	ScatterObject(const K& key) : HashObject<K, V>(key) {
		status = ScatterObjectStatus::unoccupied;
	}
	ScatterObject(const K& key, const V& value) : HashObject<K, V>(key, value) {
		status = ScatterObjectStatus::unoccupied;
	}
};