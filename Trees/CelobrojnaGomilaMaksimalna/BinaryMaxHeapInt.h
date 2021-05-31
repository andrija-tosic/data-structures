#pragma once

class BinaryMaxHeapInt
{
private:
	int* array;
	long length;
	long numOfElements;

	int find(int number);
public:
	BinaryMaxHeapInt(long len);
	~BinaryMaxHeapInt() { delete[] array; };

	bool isEmpty() const { return numOfElements == 0; };
	int getFirst() const;

	void insert(int el);
	int deleteRoot();

	static void heapSort(int* array, unsigned n);
	bool isInHeap(int number);
};
