#pragma once
template <typename T>
class DoubleNode
{
	template <class T>
	friend class DoubleLinkedList;
private:
	T info;
	DoubleNode<T>* llink;
	DoubleNode<T>* dlink;
public:
	DoubleNode() { this->info = T(); llink = this->link = nullptr; }
	DoubleNode(const T& data) {
		this->info = data;
		llink = this->dlink = nullptr;
	}
	DoubleNode(const T& data, DoubleNode<T>* prev, DoubleNode<T>* next) {
		this->info = data;
		llink = prev;
		this->dlink = next;
	}
	~DoubleNode() {}
};