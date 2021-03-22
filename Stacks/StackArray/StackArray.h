#include "../Stack/Stack.h"
using namespace std;
template <typename T, int size>
class StackArray : public Stack<T> {
	T array[size];
	int top;
public:
	StackArray();
	StackArray(int s);

	void Push(const T& data);
	T Pop();
	T GetTop();
	size_t NumberOfElements();
	bool IsEmpty();
};

template<typename T, int size>
StackArray<T, size>::StackArray() {
	top = -1;
}

template<typename T, int size>
StackArray<T, size>::StackArray(int s) {
	size = s;
	top = -1;
}

template<typename T, int size>
void StackArray<T, size>::Push(const T& data) {
	if (top == size - 1) {
		throw "Stack overflow";
	}
	else {
		array[++top] = data;
	}
}

template<typename T, int size>
T StackArray<T, size>::Pop()
{
	if (top == -1) {
		throw "Stack underflow";
	}
	else {
		top--;
	}
	return array[top + 1];
}

template<typename T, int size>
inline T StackArray<T, size>::GetTop()
{
	if (top > -1 && top < size)
		return array[top];
	else
		throw "Stack access out of bounds";
}

template<typename T, int size>
inline size_t StackArray<T, size>::NumberOfElements()
{
	return top + 1;
}

template<typename T, int size>
inline bool StackArray<T, size>::IsEmpty()
{
	return !(top + 1);
}