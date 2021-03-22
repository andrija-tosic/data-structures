#include "../Deque/Deque.h"
template<typename T>
class DequeArray : public Deque<T> {
	T* array;
	size_t head;
	size_t tail;
	size_t size;
	size_t n;
public:
	DequeArray();
	DequeArray(size_t s);
	~DequeArray();
	void EnQueueHead(const T& data);
	void EnQueueTail(const T& data);
	T DeQueueHead();
	T DeQueueTail();
	T GetHead();
	T GetTail();
	bool IsEmpty() { return !n; }
	size_t NumberOfElements() { return n; }
};

template<typename T>
inline DequeArray<T>::DequeArray()
{
	array = nullptr;
	head = tail = size = n = 0;
}

template<typename T>
inline DequeArray<T>::DequeArray(size_t s)
{
	size = s;
	n = 0;
	array = new T[size];
	head = tail = 0;
}

template<typename T>
inline DequeArray<T>::~DequeArray()
{
	delete[] array;
}

template<typename T>
inline void DequeArray<T>::EnQueueHead(const T& data)
{
	if (n == size)
		throw "Can't enqueue, queue is full";
	if (head == size - 1)
		head = 0;
	else
		head++;
	array[head] = data;
	n++;
	if (n == 1)
		tail = head;
}

template<typename T>
inline void DequeArray<T>::EnQueueTail(const T& data)
{
	if (n == size)
		throw "Can't enqueue, queue is full";
	if (tail==0)
		tail=size-1;
	else
		tail--;
	array[tail] = data;
	n++;
	if (n == 1)
		head=tail;
}

template<typename T>
inline T DequeArray<T>::DeQueueHead()
{
	if (n == 0)
		throw "Can't dequeue, queue is empty";
	if (head == 0)
		head = size - 1;
	else
		head--;
	n--;
	if (n == 1)
		tail = head;
}

template<typename T>
inline T DequeArray<T>::DeQueueTail()
{
	if (n == 0)
		throw "Can't dequeue, queue is empty";
	if (tail == size-1)
		tail = 0;
	else
		tail++;
	n--;
	if (n == 1)
		head=tail;
}

template<typename T>
inline T DequeArray<T>::GetHead()
{
	if (n == 0)
		throw "Can't get head, queue is empty";
	return array[head];
}

template<typename T>
inline T DequeArray<T>::GetTail()
{
	if (n == 0)
		throw "Can't get head, queue is empty";
	return array[tail];
}
