#include "StackVector.h"
#include <iostream>
using namespace std;
int main() {
	StackVector<int> stek(10);
	stek.Push(1);
	stek.Push(2);
	cout << stek.Pop() << endl;
	stek.Push(3);
	cout << "number of elements: " << stek.NumberOfElements() << endl;
	cout << "is stack empty: " << stek.IsEmpty() << endl;
	int a = stek.GetTop();
	stek.Pop();
	stek.Pop();
	stek.Pop();
	return 0;
}