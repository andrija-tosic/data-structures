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
	while (i != 0) {
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
		if (table[i].status != ScatterObjectStatus::unoccupied) {
			while (table[i].next != 0) {
				i = table[i].next;
			}
			unsigned t = i;
			t = this->g(t);
			while (table[t].status != ScatterObjectStatus::unoccupied && i != t) {
				t = this->g(t);
			}
			if (i == t) {
				throw "Secondary hash transformation error.";
			}
			else {
				table[t].next = i;
			}
		}
		table[i].key = key;
		table[i].value = value;
		table[i].status = ScatterObjectStatus::occupied;
		table[i].next = 0;
		this->count++;
	}
}

template<typename K, typename V>
V ChainedScatterTable<K, V>::withdraw(const K& key) {
	if (this->count == 0) {
		std::cout << "Table is empty, can't withdraw." << std::endl;
	}
	else {
		unsigned i = this->hash(key);
		unsigned prev = 0;
		while (i != 0 && table[i].key != key) {
			prev = i;
			i = table[i].next;
		}
		if (i == 0) {
			std::cout << "Element with key " << key << " not found, can't withdraw." << std::endl;
		}
		else {
			if (prev != 0) {
				table[prev].next = table[i].next;
				table[i].status = ScatterObjectStatus::deleted; // collision gets deleted
				this->count--;
				return table[i].value;
			}
			else {
				if (table[i].next == 0) {
					table[i].status = ScatterObjectStatus::deleted;
					this->count--;
					return table[i].value;
				}
				else {
					unsigned next = table[i].next;
					table[i] = table[next];
					table[i].next = table[next].next;
					V to_delete = table[next].value;
					table[next] = ChainedScatterObject<K, V>();
					table[next].status = ScatterObjectStatus::deleted;
					this->count--;
					return to_delete;
				}
			}
		}
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