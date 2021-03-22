#include "../../LancaneListe/DvostrukoLancanaLista/DoubleNode.h"
template<typename T>
class DequeDoubleLinkedList : public Deque<T> {
	DoubleNode<T>* head;
	DoubleNode<T>* tail;
	size_t n;
public:
	DequeDoubleLinkedList();
	~DequeDoubleLinkedList();
	void EnQueueHead(const T& data);
	void EnQueueTail(const T& data);
	T DeQueueHead();
	T DeQueueTail();
	T GetHead();
	T GetTail();
	bool IsEmpty() { return !n; }
	size_t NumberOfElements() { return n }
};

template<typename T>
inline DequeDoubleLinkedList<T>::DequeDoubleLinkedList()
{
	head = tail = nullptr;
	n = 0;
}

template<typename T>
inline DequeDoubleLinkedList<T>::~DequeDoubleLinkedList()
{
	DoubleNode<T>* pok1, pok2;
	pok1 = head;
	pok2 = head->dlink;
	while (pok1 != nullptr) {
		delete pok1;
		pok1 = pok2;
		pok2 = pok2->dlink;
	}
}

template<typename T>
inline void DequeDoubleLinkedList<T>::EnQueueHead(const T& data)
{
	DoubleNode<T>* node = new DoubleNode<T>(data);
	head->dlink = node;
	node->llink = head;
	node->dlink = nullptr;
	head = node;
	n++;
	if (n == 1)
		tail = head;
}

template<typename T>
inline void DequeDoubleLinkedList<T>::EnQueueTail(const T& data)
{
	DoubleNode<T>* node = new DoubleNode<T>(data);
	tail->llink = node;
	node->dlink = tail;
	node->llink = nullptr;
	tail = node;
	n++;
	if (n == 1)
		head = tail;
}

template<typename T>
inline T DequeDoubleLinkedList<T>::DeQueueHead()
{
	if (n == 0)
		throw "Can't dequeue head, deque empty";
	DoubleNode<T>* node = new DoubleNode<T>(data);
	node->llink = head->llink;
	node->dlink = nullptr;
	head->llink->dlink = node;
	delete head;
	head = node;
	n--;
	if (n == 1)
		tail = head;
}

template<typename T>
inline T DequeDoubleLinkedList<T>::DeQueueTail()
{
	if (n == 0)
		throw "Can't dequeue tail, deque empty";
	DoubleNode<T>* node = new DoubleNode<T>(data);
	node->dlink = tail->dlink;
	node->llink = nullptr;
	tail->dlink->llink = node;
	delete tail;
	tail = node;
	n--;
	if (n == 1)
		head = tail;
}

template<typename T>
inline T DequeDoubleLinkedList<T>::GetHead()
{
	if (n == 0)
		throw "Can't get head, deque empty";
	return head->info;
}

template<typename T>
inline T DequeDoubleLinkedList<T>::GetTail()
{
	if (n == 0)
		throw "Can't get tail, deque empty";
	return tail->info;
}
