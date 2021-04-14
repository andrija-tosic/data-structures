#pragma once
template <typename T>
class Node
{
	template<typename T>
	friend class LinkedList;
	template<typename K, typename V>
	friend class ChainedHashTable;
protected:
	T info;
	Node<T>* link;
public:
	Node() { info = T(); link = nullptr; }
	Node(const T& data) : info(data) { link = nullptr; }
	Node(const T& data, Node<T>* next) : info(data), link(next) {}
	~Node() {}
};