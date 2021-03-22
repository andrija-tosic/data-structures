#include "../Stack/Stack.h"
using namespace std;
template <typename T>
class StackVector : public Stack<T> {
	T* array;
	int top;
	int size;
public:
	StackVector();
	StackVector(int s);
	~StackVector() { delete[] array; }
	void Push(const T& data);
	T Pop();
	T GetTop();
	size_t NumberOfElements() { return top + 1; }
	bool IsEmpty() { return !(top + 1); }
};

template<typename T>
StackVector<T>::StackVector() {
	top = -1;
	array = nullptr;
}

template<typename T>
StackVector<T>::StackVector(int s) {
	size = s;
	top = -1;
	array = new T[size];
}

template<typename T>
void StackVector<T>::Push(const T& data) {
	if (top == size - 1)
		throw "Stack overflow";
	array[++top] = data;
}	

template<typename T>
T StackVector<T>::Pop()
{
	if (top == -1)
		throw "Stack underflow";
	top--;
	return array[top + 1];
}

template<typename T>
inline T StackVector<T>::GetTop()
{
	if (top == -1)
		throw "Can't get top, stack is empty";
	return array[top];
}