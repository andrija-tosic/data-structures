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

	unsigned int c(const unsigned int& i) const;

	V find(const K& key) const override;
	unsigned int find_index(const K& key) const;

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
	if (this->count != this->length) {
		unsigned h = this->hash(key);
		unsigned probe = h;
		if (table[probe].status == ScatterObjectStatus::unoccupied) {
			return probe;
		}
		else { // do secondary search
			unsigned i = 1;
			do {
				probe = (this->hash(key) + c(i)) % this->length;
				if (table[probe].status != ScatterObjectStatus::occupied) {
					return probe;
				}
				i++;
			} while (probe != h && i < this->length);
		}
	}
	else {
		std::cout << "Table is full." << std::endl;
		return -1;
	}
}

template<typename K, typename V>
V OpenScatterTable<K, V>::find(const K& key) const {
	long int probe;
	for (unsigned i = 0; i < this->length; i++) {
		probe = (this->hash(key) + c(i)) % this->length;
		if (table[probe].status == ScatterObjectStatus::unoccupied) {
			std::cout << "Element with key " << key << " not found." << std::endl;
			return V();
		}
		else if (table[probe].key == key) {
			return table[probe].value;
		}
	}
	std::cout << "Element with key " << key << " not found." << std::endl;
	return V();
}

template<typename K, typename V>
unsigned int OpenScatterTable<K, V>::find_index(const K& key) const {
	long int probe;
	for (unsigned i = 0; i < this->length; i++) {
		probe = (this->hash(key) + c(i)) % this->length;
		if (table[probe].status == ScatterObjectStatus::unoccupied) {
			return -1;
		}
		else if (table[probe].key == key) {
			return probe;
		}
	}
	return -1;
}

template<typename K, typename V>
unsigned int OpenScatterTable<K, V>::c(const unsigned int& i) const {
	return i * i; // quadratic probing
}

template<typename K, typename V>
void OpenScatterTable<K, V>::insert(const K& key, const V& value) {
	if (this->count == this->length) {
		std::cout << "Table is full, can't insert." << std::endl;
	}
	else {
		unsigned i = this->findUnoccupied(key);
		table[i] = ScatterObject<K, V>(key, value);
		table[i].status = ScatterObjectStatus::occupied;
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
		unsigned match = (this->find_index(key));
		if (match >= 0 && table[match].status == ScatterObjectStatus::occupied) {
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