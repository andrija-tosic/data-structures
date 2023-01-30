#include "BinaryMinHeapInt.h"
#include "BTreeInt.h"
#include <iostream>
using namespace std;

void main()
{
	BinaryMinHeapInt heap(10);
	heap.insert(1);
	heap.insert(2);
	heap.insert(3);
	heap.insert(4);
	heap.insert(5);
	heap.insert(6);
	heap.insert(7);

	BTreeInt tree;
	tree.createFromMinHeap(heap);

	tree.inorder();
}
