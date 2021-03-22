#include "LinkedList.h"
#include <random>

void fun(LinkedList<int>& list) {
	for (int i = 0; i < 10; i++)
		list.DeleteFromHead();
	list.InsertToTail(4);
	list.InsertToTail(3);
	list.InsertToTail(2);
	list.InsertToTail(5);
	list.InsertToTail(7);
	list.InsertToTail(1);
	list.InsertToHead(9);
	list.InsertToTail(10);
	list.InsertToHead(6);
	list.InsertToTail(8);
}

int main() {
	LinkedList<int> list;

	for (int i = 0; i < 1; i++) {

		srand((unsigned int)time(NULL));

		list.InsertToTail(4);
		list.InsertToTail(10);
		list.InsertToTail(3);
		list.InsertToHead(9);
		list.InsertToHead(6);
		list.InsertToTail(2);
		list.InsertToTail(5);
		list.InsertToTail(7);
		list.InsertToTail(1);
		list.InsertToTail(8);

		cout << endl;
		cout << "ins sort" << endl;
		fun(list);
		list.Print();
		list.InsertionSort(true);
		cout << endl;
		cout << "bub sort" << endl;
		fun(list);
		list.BubbleSort(true);
		cout << endl;
		cout << "sel sort" << endl;
		fun(list);
		list.SelectionSort(true);
		cout << endl;
	}

	return 0;
}