#pragma once
#include "../HashTable/HashTable.h"
#include "../../LancaneListe/LancanaLista/LinkedList.h"

template<typename K, typename V>
class ChainedHashTable : public HashTable<K, V> {

	LinkedList<HashObject<K, V>>* table; // array of linked lists

public:
	ChainedHashTable(unsigned int l);
	~ChainedHashTable();

	V find(const K& key) const override;
	
	void insert(const K& key, const V& value) override;

	V withdraw(const K& key) override;
	
	bool isInTable(const K& key) const;
	void print() const;
};

template<typename K, typename V>
ChainedHashTable<K, V>::ChainedHashTable(unsigned int l) {
	this->length = l;
	this->count = 0;
	table = new LinkedList<HashObject<K, V>>[this->length];
}

template<typename K, typename V>
ChainedHashTable<K, V>::~ChainedHashTable() {
	delete[] table;
}

template<typename K, typename V>
V ChainedHashTable<K, V>::find(const K& key) const {
	unsigned i = this->hash(key);
	if (!table[i].isEmpty()) {
		Node<HashObject<K, V>>* temp = table[i].start;
		while (temp && temp->info.key != key) {
			temp = temp->link;
		}
		if (temp)
			return temp->info.value;
		else
			return V();
	}
	else
		return V();
}


template<typename K, typename V>
void ChainedHashTable<K, V>::insert(const K& key, const V& value) {
	unsigned i = this->hash(key);
	
	Node<HashObject<K, V>>* node = table[i].start;
	while (node && node->info.key != key) {
		node = node->link;
	}
	if (node) {
		node->info.value = value; // replace value if object with given key exists
	}
	else {
		HashObject<K, V> o(key, value);
		this->table[i].InsertToTail(o); // insert if object with given key is not found
		this->count++;
	}
}

template<typename K, typename V>
V ChainedHashTable<K, V>::withdraw(const K& key) {
	if (isInTable(key)) {
		unsigned i = this->hash(key);
		V to_delete = find(key);
		this->table[i].DeleteNode(HashObject<K, V>(key, to_delete));
		this->count--;
		return to_delete;
	}
	else {
		std::cout << "Element with key " << key << " not found, can't withdraw." << std::endl;
		return V();
	}
}

template<typename K, typename V>
bool ChainedHashTable<K, V>::isInTable(const K& key) const {
	unsigned i = this->hash(key);
	if (!table[i].isEmpty()) {
		Node<HashObject<K, V>>* temp = table[i].start;
		while (temp && temp->info.key != key) {
			temp = temp->link;
		}
		if (temp)
			return true;
		else
			return false;
	}
	else
		return false;
}

template<typename K, typename V>
void ChainedHashTable<K, V>::print() const {
	for (unsigned i = 0; i < this->length; i++) {
		if (!table[i].isEmpty()) {
			table[i].Print();
			std::cout << std::endl;
		}
	}
}