#include "../Queue/Queue.h"
template<typename T>
class QueueArray : public Queue<T> {
	T* array;
	size_t head;
	size_t tail;
	size_t size;
	size_t n;
public:
	QueueArray();
	QueueArray(size_t size);
	~QueueArray();
	void EnQueue(const T& data);
	T DeQueue();
	T GetHead();
	bool IsEmpty();
	size_t NumberOfElements();
};

template<typename T>
inline QueueArray<T>::QueueArray() {
	head = tail = 0;
	n = size = 0;
	array = nullptr;
}

template<typename T>
inline QueueArray<T>::QueueArray(size_t size) {
	head = tail = 0;
	this->size = size;
	n = 0;
	array = new T[this->size];
}

template<typename T>
inline QueueArray<T>::~QueueArray() {
	delete[] array;
}

template<typename T>
inline void QueueArray<T>::EnQueue(const T& data)
{
	if (n == size)
		throw "Can't enqueue: Queue is full";
	if (tail == 0)
		tail = size - 1;
	else
		tail--;
	n++;
	array[tail] = data;
	if (NumberOfElements() == 1)
		head = tail;
}

template<typename T>
inline T QueueArray<T>::DeQueue()
{
	if (n == 0)
		throw "Can't dequeue: Queue is empty";
	T tmp = array[head];
	if (head == 0)
		head = size - 1;
	else
		head--;
	n--;
	if (NumberOfElements() == 1)
		head = tail;
	return tmp;
}

template<typename T>
inline T QueueArray<T>::GetHead()
{
	if (n == 0)
		throw "Can't get head: Queue is empty";
	return array[head];
}

template<typename T>
inline bool QueueArray<T>::IsEmpty()
{
	return !(n);
}

template<typename T>
inline size_t QueueArray<T>::NumberOfElements()
{
	return n;
}
