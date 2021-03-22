#pragma once
#include "DoubleNode.h"
#include <iostream>
using namespace std;
template <typename T>
class DoubleLinkedList {
private:
	DoubleNode<T>* start;
	DoubleNode<T>* tail;
public:
	DoubleLinkedList() { start = tail = nullptr; }
	~DoubleLinkedList();
	void InsertToHead(const T& data);
	void InsertToTail(const T& data);
	void InsertAfter(const T& to_find, const T& data);
	void InsertBefore(const T& to_find, const T& data);
	void DeleteFromHead();
	void DeleteFromTail();
	void DeleteNode(const T& data);

	void Print();
};

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	DoubleNode<T>* pok1 = start;
	DoubleNode<T>* pok2;
	while (pok1 != nullptr) {
		pok2 = pok1->dlink;
		delete pok1;
		pok1 = pok2;
	}
}

template <typename T>
void DoubleLinkedList<T>::InsertToHead(const T& data)
{
	DoubleNode<T>* node = new DoubleNode<T>(data);
	if (start == nullptr) {
		start = tail = node;
		node->llink = node->dlink = nullptr;
	}
	else {
		node->dlink = start;
		start = node;
		start->llink = nullptr;
	}
	cout << data << " inserted to head" << endl;
}

template <typename T>
void DoubleLinkedList<T>::InsertToTail(const T& data)
{
	DoubleNode<T>* node = new DoubleNode<T>(data);
	if (start == nullptr) {
		start = tail = node;
		node->llink = node->dlink = nullptr;
	}
	else {
		tail->dlink = node;
		node->llink = tail;
		tail = node;
		tail->dlink = nullptr;
	}
	cout << data << " inserted to tail" << endl;
}

template <typename T>
void DoubleLinkedList<T>::InsertAfter(const T& to_find, const T& data)
{
	DoubleNode<T>* pok = start;
	while (pok != nullptr && pok->info != to_find) {
		pok = pok->dlink;
	}
	if (pok != nullptr && pok->info == to_find) {
		DoubleNode<T>* node = new DoubleNode<T>(data);
		node->info = data;
		node->llink = pok;
		pok->dlink = node;
		node->dlink = pok->dlink;

		if (pok == tail) {
			InsertToTail(data);
		}
		cout << data << " inserted after " << to_find << endl;
	}
	else {
		cout << "node with " << to_find << " not found, not inserting" << endl;
	}
}

template <typename T>
void DoubleLinkedList<T>::InsertBefore(const T& to_find, const T& data)
{
	if (start != nullptr) {
		if (start->info == to_find) {
			InsertToHead(data);
		}
		else if (start != tail) {
			DoubleNode<T>* pok = start->dlink;
			while (pok != nullptr && pok->info != to_find) {
				pok = pok->dlink;
			}
			if (pok != nullptr && pok->info == to_find) {
				DoubleNode<T>* node = new DoubleNode<T>(data);
				node->llink = pok->llink;
				pok->llink->dlink = node;
				pok->llink = node;
				node->dlink = pok;
				cout << data << " inserted before " << to_find << endl;
			}
			else
				cout << "node with " << to_find << " not found, not inserting" << endl;
		}
	}
}

template <typename T>
void DoubleLinkedList<T>::DeleteFromHead()
{
	if (start != nullptr) {
		if (start != tail) {
			DoubleNode<T>* old_start = start;
			cout << "deleted " << start->info << " from head" << endl;
			start = start->dlink;
			start->llink = nullptr;
			delete old_start;
		}
		else {
			cout << "deleted " << start->info << " from head" << endl;
			delete start;
			start = tail = nullptr;
		}
	}
}

template <typename T>
void DoubleLinkedList<T>::DeleteFromTail()
{
	if (start != nullptr) {
		if (start != tail) {
			cout << "deleted " << tail->info << " from tail" << endl;
			tail = tail->llink;
			delete tail->dlink;
			tail->dlink = nullptr;
		}
		else {
			cout << "deleted " << tail->info << " from tail" << endl;
			delete tail;
			start = tail = nullptr;
		}
	}
}


template <typename T>
void DoubleLinkedList<T>::DeleteNode(const T& data)
{
	if (start != nullptr) {
		if (start->info == data) {
			DeleteFromHead();
		}
		else {
			DoubleNode<T>* pok = start;
			while (pok != nullptr && pok->info != data) {
				pok = pok->dlink;
			}
			if (pok != nullptr) {
				if (pok == tail) {
					DeleteFromTail();
				}
				else {
					pok->llink->dlink = pok->dlink;
				}
				pok = nullptr;
				delete pok;
				cout << "deleted node " << data << endl;
			}
			else
				cout << "node " << data << " not found, not deleting" << endl;
		}
	}
}

template <typename T>
void DoubleLinkedList<T>::Print() {
	if (start != nullptr) {
		DoubleNode<T>* pok = start;
		while (pok != nullptr) {
			cout << pok->info << " ";
			pok = pok->dlink;
		}
		cout << endl;
	}
	else
		cout << "list empty" << endl;
}