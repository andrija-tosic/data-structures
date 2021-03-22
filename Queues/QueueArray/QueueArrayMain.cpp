#include "QueueArray.h"
#include <iostream>
using namespace std;
int main() {
	try {
		QueueArray<int> queue(10);
		queue.EnQueue(1);
		cout << "enqueued 1" << endl;
		cout << "queue head: " << queue.GetHead() << endl;
		queue.EnQueue(2);
		cout << "enqueued 2" << endl;
		cout << "queue head: " << queue.GetHead() << endl;
		queue.EnQueue(3);
		cout << "enqueued 3" << endl;
		cout << "number of elements: " << queue.NumberOfElements() << endl;
		queue.DeQueue();
		cout << "dequeued" << endl;
		cout << "number of elements: " << queue.NumberOfElements() << endl;
		cout << "queue head: " << queue.GetHead() << endl;
		queue.DeQueue();
		cout << "dequeued" << endl;
		cout << "queue head: " << queue.GetHead() << endl;
		cout << "number of elements: " << queue.NumberOfElements() << endl;
		cout << "is empty: " << queue.IsEmpty() << endl;
		queue.DeQueue();
		cout << "dequeued" << endl;
		cout << "queue head: " << queue.GetHead() << endl;
		queue.DeQueue();
		cout << "dequeued" << endl;
		return 0;
	}
	catch (const char* str) {
		cout << str;
	}
}