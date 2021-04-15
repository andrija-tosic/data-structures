#include "StaticNode.h"
#include <iostream>

template<typename T>
class StaticLinkedList {
private:
	unsigned int head;
	unsigned int lrmp;
	StaticNode<T>* list;

public:
	StaticLinkedList();
	StaticLinkedList(unsigned size);
	~StaticLinkedList();

	bool isEmpty() const;

	void addToHead(const T& data);
	void addToTail(const T& data);

	T deleteFromHead();
	T deleteFromTail();

	T deleteElement(const T& data);

	void print() const;

};

template<typename T>
StaticLinkedList<T>::StaticLinkedList() {
	head = lrmp = 0;
	list = NULL;
}

template<typename T>
StaticLinkedList<T>::StaticLinkedList(unsigned size) {
	head = 0;
	lrmp = 1;
	list = new StaticNode<T>[size + 1];
	for (unsigned i = 1; i < size; i++) {
		list[i].next = i + 1;
	}
	list[size].next = 0;
}

template<typename T>
StaticLinkedList<T>::~StaticLinkedList() {
	delete[] list;
}

template<typename T>
bool StaticLinkedList<T>::isEmpty() const
{
	return (head == 0);
}

template<typename T>
void StaticLinkedList<T>::addToHead(const T& data) {
	if (lrmp == 0) {
		std::cout << "List is full. Can't add " << data << std::endl;
	}
	else {
		unsigned old_lrmp = lrmp;
		lrmp = list[lrmp].next;
		list[old_lrmp].info = data;
		list[old_lrmp].next = head;
		head = old_lrmp;

		std::cout << data << " added to head." << std::endl;
	}

}

template<typename T>
void StaticLinkedList<T>::addToTail(const T& data) // tail is element with .next = 0
{
	if (lrmp == 0) {
		std::cout << "List is full. Can't add " << data << std::endl;
	}
	else if (head == 0) {
		addToHead(data);
	}
	else {
		unsigned temp = head;
		while (temp && list[temp].next) { // search for tail
			temp = list[temp].next;
		}
		unsigned indexof_new = lrmp;
		lrmp = list[lrmp].next;

		list[temp].next = indexof_new; // tail.next = index of new element
		list[indexof_new].info = data;
		list[indexof_new].next = 0;

		std::cout << data << " added to tail." << std::endl;
	}
}

template<typename T>
T StaticLinkedList<T>::deleteFromHead() {
	if (head == 0) { // empty list
		return T();
	}
	else {
		unsigned old_head = head;
		if (list[head].next == 0) { // ako ima samo 1 element
			head = 0;
		}
		else {
			head = list[head].next;
		}
		T deleted_data = list[old_head].info;
		list[old_head].next = lrmp;
		lrmp = old_head;

		std::cout << deleted_data << " deleted from head." << std::endl;

		return deleted_data;
	}
}

template<typename T>
T StaticLinkedList<T>::deleteFromTail() {
	if (head == 0) { // empty list
		return T();
	}
	else if (list[head].next == 0) { // only 1 element
		T deleted_data = list[head].info;
		deleteFromHead();
		return deleted_data;
	}
	else {
		unsigned prev = head;
		unsigned temp = list[head].next;
		while (temp && list[temp].next) { // search for tail
			prev = temp;
			temp = list[temp].next;
		}


		unsigned old_tail = temp;
		T deleted_data = list[old_tail].info;
		list[old_tail].next = lrmp;
		lrmp = old_tail;

		list[prev].next = 0;

		std::cout << deleted_data << " deleted from tail." << std::endl;
		
		return deleted_data;
	}
}

template<typename T>
T StaticLinkedList<T>::deleteElement(const T& data) {
	unsigned prev = head;
	unsigned temp = list[head].next;

	while (temp && list[temp].info != data) { // search
		prev = temp;
		temp = list[temp].next;
	}
	
	if (temp) { // if found
		if (temp == head) {
			head = list[head].next;
		}
		else {
			list[prev].next = list[temp].next;
			list[temp].next = lrmp;
			lrmp = temp; // lrmp pointing to last deleted
		}

		std::cout << data << " deleted." << std::endl;
		return list[temp].info;
	}
	else {
		std::cout << data << " not found." << std::endl;
		return T();
	}
}

template<typename T>
void StaticLinkedList<T>::print() const {
	if (isEmpty()) {
		std::cout << "List is empty" << std::endl;
	}
	else {
		unsigned temp = head;
		while (temp) {
			std::cout << list[temp].info << " " << std::endl;
			temp = list[temp].next;
		}
	}
}