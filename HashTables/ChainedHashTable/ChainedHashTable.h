#pragma once
#include "../HashTable/HashTable.h"
#include "../../LancaneListe/LancanaLista/LinkedList.h"

template<typename K, typename V>
class ChainedHashTable : public HashTable<K, V> {

	LinkedList<HashObject<K, V>>* table; // array of linked lists

public:
	ChainedHashTable(unsigned int l);
	~ChainedHashTable();

	HashObject<K, V> find(const K& key);
	
	void insert(const HashObject<K, V>& obj);
	void insert(const K& key, const V& value);

	void withdraw(const HashObject<K, V>& obj);
	void withdraw(const K& key);
	bool isInTable(const K& key);
	void print();
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
HashObject<K, V> ChainedHashTable<K, V>::find(const K& key) {
	unsigned i = this->hash(key);
	if (!table[i].isEmpty()) {
		Node<HashObject<K, V>>* temp = table[i].start;
		while (temp && temp->info.key != key) {
			temp = temp->link;
		}
		if (temp)
			return temp->info;
		else
			return HashObject<K, V>();
	}
	else
		return HashObject<K, V>();
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
void ChainedHashTable<K, V>::insert(const HashObject<K, V>& obj) {
	unsigned i = this->hash(obj);
	
	Node<HashObject<K, V>>* node = table[i].start;
	while (node && node->info.key != obj.key) {
		node = node->link;
	}
	if (node) {
		node->info.value = obj.value; // replace value if object with given key exists
	}
	else {
		this->table[i].InsertToTail(obj); // insert if object with given key is not found
		this->count++;
	}
}

template<typename K, typename V>
void ChainedHashTable<K, V>::withdraw(const HashObject<K, V>& obj) {
	if (isInTable(obj.key)) {
		unsigned i = this->hash(obj);
		this->table[i].DeleteNode(obj);
		this->count--;
	}
}

template<typename K, typename V>
void ChainedHashTable<K, V>::withdraw(const K& key) {
	if (isInTable(key)) {
		HashObject<K, V> obj = find(key);
		withdraw(obj);
	}
}

template<typename K, typename V>
bool ChainedHashTable<K, V>::isInTable(const K& key) {
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
void ChainedHashTable<K, V>::print() {
	for (unsigned i = 0; i < this->length; i++) {
		if (!table[i].isEmpty()) {
			table[i].Print();
			std::cout << std::endl;
		}
	}
}