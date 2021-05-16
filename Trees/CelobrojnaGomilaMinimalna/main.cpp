#include "BinaryMinHeapInt.h"

#include <iostream>
using namespace std;

int main()
{
	int niz[] = { 7, 6, 3, 8, 0, 1, 2, 5, 4, 9 };

	BinaryMinHeapInt::heapSort(niz, 10);

	for (int i = 0; i < 10; i++) {
		std::cout << niz[i] << " " << std::endl;
	}

	return 0;
}
