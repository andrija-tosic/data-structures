#pragma once
#include "../Stack/Stack.h"
#include "../../LancaneListe/LancanaLista/Node.h"
template<typename T>
class StackLinkedList : public Stack<T>, public Node<T> {
	Node<T>* top;
	size_t n;
public:
	StackLinkedList();
	~StackLinkedList();
	void Push(const T& data);
	T Pop();
	T GetTop() { return top->info;	}
	size_t NumberOfElements() { return n; }
	bool IsEmpty() { return !(n); }
};

template<typename T>
StackLinkedList<T>::StackLinkedList() {
	top = nullptr;
	n = 0;
}

template<typename T>
StackLinkedList<T>::~StackLinkedList() {
	Node<T>* pok1 = top;
	Node<T>* pok2 = top->link;
	while (pok1 != nullptr) {
		delete pok1;
		pok1 = pok2;
		pok2 = pok2->link;
	}
}

template<typename T>
void StackLinkedList<T>::Push(const T& data) {
	// ne moze da overflowuje kao
	Node<T>* node = new Node<T>(data);
	node->link = top;
	top = node;
	n++;
}

template<typename T>
T StackLinkedList<T>::Pop() {
	if (top == nullptr)
		throw "Stack underflow";
	Node<T>* tmp = top;
	top = tmp->link;
	delete tmp;
	n--;
}