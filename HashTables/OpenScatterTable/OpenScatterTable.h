#pragma once
#include "../HashTable/HashTable.h"
#include "../HashTable/ScatterObject.h"
template<typename K, typename V>
class OpenScatterTable : public HashTable<K, V>
{
protected:
	ScatterObject<K, V>* table;

public:
	OpenScatterTable(unsigned int len);
	~OpenScatterTable();

	unsigned int findUnoccupied(const K& key) const;
	unsigned int findMatch(const K& key) const;

	V find(const K& key) const override;
	void insert(const K& key, const V& value) override;
	V withdraw(const K& key) override;

	void print() const;

};

template<typename K, typename V>
OpenScatterTable<K, V>::OpenScatterTable(unsigned int len) {
	this->length = len;
	this->count = 0;
	table = new ScatterObject<K, V>[this->length];
}

template<typename K, typename V>
OpenScatterTable<K,V>::~OpenScatterTable() {
	delete[] table;
}

template<typename K, typename V>
unsigned int OpenScatterTable<K, V>::findUnoccupied(const K& key) const {
	unsigned i = this->hash(key);
	unsigned t = i;
	if (table[t].status != ScatterObjectStatus::occupied) {
		return t;
	}
	do {
		t = this->g(t);
		if (table[t].status != ScatterObjectStatus::occupied) {
			return t;
		}
	} while (t != i);
	throw "Table is full.";
}

template<typename K, typename V>
unsigned int OpenScatterTable<K, V>::findMatch(const K& key) const {
	unsigned int t = this->hash(key);
	for (unsigned i = 0; i < this->length; i++) {
		if (table[t].status == ScatterObjectStatus::unoccupied) {
			return 0;
		}
		else if (table[t].key == key) {
			return t;
		}
		else {
			t = this->g(t);
		}
	}
	return 0;
}

template<typename K, typename V>
V OpenScatterTable<K, V>::find(const K& key) const {
	unsigned match = this->findMatch(key);
	if (match >= 1) {
		return table[match].value;
	}
	else {
		std::cout << "Element with key " << key << " not found." << std::endl;
	}
}

template<typename K, typename V>
void OpenScatterTable<K, V>::insert(const K& key, const V& value) {
	if (this->count == this->length) {
		std::cout << "Table is full, can't insert." << std::endl;
	}
	else {
		unsigned to_insert = this->findUnoccupied(key);
		table[to_insert] = ScatterObject<K, V>(key, value);
		table[to_insert].status = ScatterObjectStatus::occupied;
		this->count++;
	}
}

template<typename K, typename V>
V OpenScatterTable<K, V>::withdraw(const K& key) {
	if (this->count == 0) {
		std::cout << "Table is empty, can't withdraw." << std::endl;
		return V();
	}
	else {
		unsigned match = this->findMatch(key);
		if (match >= 1) {
			V deleted_value = table[match].value;
			table[match].status = ScatterObjectStatus::deleted;
			return deleted_value;
		}
		else {
			std::cout << "Element with key " << key << " not found, can't withdraw." << std::endl;
			return V();
		}
	}
}

template<typename K, typename V>
void OpenScatterTable<K, V>::print() const {
	for (unsigned i = 0; i < this->length; i++) {
		if (table[i].status == ScatterObjectStatus::occupied) {
			std::cout << table[i] << std::endl;
		}
	}
}