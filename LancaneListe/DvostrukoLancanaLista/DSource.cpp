#pragma once
#include "DoubleLinkedList.h"
using namespace std;
#include <random>
int main() {
	DoubleLinkedList<int> list;

		srand((unsigned int)time(NULL));

		list.InsertToHead(1);

		cout << endl;
		list.Print();
		cout << endl;

		list.InsertToTail(2);

		cout << endl;
		list.Print();
		cout << endl;

		list.InsertAfter(2, 3);

		cout << endl;
		list.Print();
		cout << endl;

		list.DeleteFromHead();

		cout << endl;
		list.Print();
		cout << endl;

		list.DeleteFromTail();

		cout << endl;
		list.Print();
		cout << endl;

		list.DeleteNode(5);

		cout << endl;
		list.Print();
		cout << endl;

		list.InsertToTail(4);

		cout << endl;
		list.Print();
		cout << endl;

		list.InsertBefore(4, 7);

		cout << endl;
		list.Print();
		cout << endl;

		list.InsertToTail(10);

		cout << endl;
		list.Print();
		cout << endl;

		list.DeleteNode(10);

		cout << endl;
		list.Print();
		cout << endl;

		list.DeleteNode(4);

		cout << endl;
		list.Print();
		cout << endl;

		list.DeleteNode(2);

		cout << endl;
		list.Print();
		cout << endl;

	return 0;
}