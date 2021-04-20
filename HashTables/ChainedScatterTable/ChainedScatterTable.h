#pragma once
#include "../HashTable/HashTable.h"
#include "ChainedScatterObject.h"
#include <iostream>

template<typename K, typename V>
class ChainedScatterTable : public HashTable<K, V> {
private:
	ChainedScatterObject<K, V>* table;

public:
	ChainedScatterTable(const unsigned int& l);
	~ChainedScatterTable();

	void insert(const K& key, const V& value) override;

	V withdraw(const K& key) override;

	V find(const K& key) const override;

	void print() const;
};

template<typename K, typename V>
ChainedScatterTable<K, V>::ChainedScatterTable(const unsigned int& l) {
	this->length = l;
	this->count = 0;
	this->table = new ChainedScatterObject<K, V>[this->length + 1];
}

template<typename K, typename V>
ChainedScatterTable<K, V>::~ChainedScatterTable() {
	delete[] table;
}

template<typename K, typename V>
V ChainedScatterTable<K, V>::find(const K& key) const {
	unsigned i = this->hash(key);
	while (i != -1) {
		i = table[i].next; // search
	}
	return table[i].value;
}

template<typename K, typename V>
void ChainedScatterTable<K, V>::insert(const K& key, const V& value) {
	if (this->count == this->length) {
		std::cout << "Table is full, can't insert." << std::endl;
	}
	else {
		unsigned i = this->hash(key);
		if (table[i].key == key) {
			table[i].value = value;
			table[i].status = ScatterObjectStatus::occupied;
			this->count++;
		}
		else {
			unsigned prev = i;
			while (table[i].status != ScatterObjectStatus::unoccupied && table[i].key != key) {
				prev = i;
				i = this->g(i);
			}
			if (prev != i) 
				table[prev].next = i;
			table[i].key = key;
			table[i].value = value;
			table[i].status = ScatterObjectStatus::occupied;
			table[i].next = -1;
			this->count++;
		}
	}
}

template<typename K, typename V>
V ChainedScatterTable<K, V>::withdraw(const K& key) {
	if (this->count == 0) {
		std::cout << "Table is empty, can't withdraw." << std::endl;
		return V();
	}
	else {
		unsigned i = this->hash(key);
		unsigned prev = -1;
		while (i != -1 && table[i].key != key) {
			prev = i;
			i = table[i].next;
		}
		if (i == -1) {
			std::cout << "Element with key " << key << " not found, can't withdraw." << std::endl;
		}
		else {
			if (prev != -1) {
				table[prev].next = table[i].next;
				table[i].status = ScatterObjectStatus::deleted; // collision gets deleted
				this->count--;
				return table[i].value;
			}
			else if (table[i].next == -1) {
					table[i].status = ScatterObjectStatus::deleted;
					this->count--;
					return table[i].value;
			}
			else {
				unsigned next = table[i].next;
				table[i] = table[next];
				table[i].next = table[next].next;
				table[next].status = ScatterObjectStatus::deleted;
				this->count--;
				return table[next].value;
			}
		}
		return V();
	}
}

template<typename K, typename V>
void ChainedScatterTable<K, V>::print() const {
	for (unsigned i = 0; i < this->length; i++) {
		if (table[i].status == ScatterObjectStatus::occupied) {
			table[i].print(std::cout);
			std::cout << std::endl;
		}
	}
}