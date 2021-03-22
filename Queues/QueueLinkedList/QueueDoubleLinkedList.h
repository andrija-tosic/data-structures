#include "../Queue/Queue.h"
#include "../../LancaneListe/DvostrukoLancanaLista/DoubleNode.h"
template<typename T>
class QueueDoubleLinkedList : public Queue<T> {
	DoubleNode<T>* head;
	DoubleNode<T>* tail;
	size_t n;
public:
	QueueDoubleLinkedList();
	~QueueDoubleLinkedList();
	void EnQueue(const T& data);
	T DeQueue();
	T GetHead() { return head->info; }
	bool IsEmpty() { return !n }
	size_t NumberOfElements() { return n}

};

template<typename T>
inline QueueDoubleLinkedList<T>::QueueDoubleLinkedList()
{
	head = tail = nullptr;
	n = 0;
}

template<typename T>
inline QueueDoubleLinkedList<T>::~QueueDoubleLinkedList()
{
	DoubleNode<T>* pok1, pok2;
	pok1 = tail;
	pok2 = tail->dlink;
	while (pok1 != nullptr) {
		delete pok1;
		pok1 = pok2;
		pok2 = tail->dlink;
	}
}

template<typename T>
inline void QueueDoubleLinkedList<T>::EnQueue(const T& data)
{
	DoubleNode<T>* node = new DoubleNode<T>(data);
	node->dlink = tail;
	node->llink = nullptr;
	tail = node;
	if (n == 1)
		head = tail;
}

template<typename T>
inline T QueueDoubleLinkedList<T>::DeQueue()
{
	DoubleNode<T>* node = new DoubleNode<T>(data);
	node->llink = head;
	node->dlink = nullptr;
	head = node;
	if (n == 1)
		tail = head;
}
