#include "BinaryMaxHeapInt.h"

#include <iostream>
using namespace std;

int main()
{
	BinaryMaxHeapInt maxHeap(16);

	maxHeap.insert(1);
	maxHeap.insert(2);
	maxHeap.insert(3);
	maxHeap.insert(4);
	maxHeap.insert(5);


	std::cout << maxHeap.isInHeap(1) << std::endl;
	std::cout << maxHeap.isInHeap(2) << std::endl;
	std::cout << maxHeap.isInHeap(3) << std::endl;
	std::cout << maxHeap.isInHeap(4) << std::endl;
	std::cout << maxHeap.isInHeap(5) << std::endl;
	std::cout << maxHeap.isInHeap(10) << std::endl;
	std::cout << maxHeap.isInHeap(-1) << std::endl;

	return 0;
}
