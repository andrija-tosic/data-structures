#include <iostream>
#include "Array.h"

using std::cin;
using std::cout;
using std::endl;

int binarySearch(int niz[], int el, int mini, int maxi)
{
	if (maxi < mini)
		return -1;

	int m = (mini + maxi) / 2;
	if (el < niz[m])
		return binarySearch(niz, el, mini, m - 1);
	else if (el > niz[m])
		return binarySearch(niz, el, m + 1, maxi);
	else
		return m;
}

void bubbleSort(int* niz, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (niz[j] < niz[j - 1])
			{
				int tmp = niz[j];
				niz[j] = niz[j - 1];
				niz[j - 1] = tmp;
			}
		}
	}
}

void selectionSort(int* niz, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int least = i;
		for (int j = i + 1; j < n; j++)
		{
			if (niz[j] < niz[least])
				least = j;
		}
		int tmp = niz[i];
		niz[i] = niz[least];
		niz[least] = tmp;
	}
}

void insertionSort(int* niz, int n)
{
	int j, tmp;
	for (int i = 0; i < n; i++)
	{
		tmp = niz[i];
		for (j = i; j > 0 && tmp < niz[j - 1]; j--)
		{
			niz[j] = niz[j - 1];
		}
		niz[j] = tmp;
	}
}

void mergeSort(int* niz, int n)
{

}

int main()
{
	int niz[] = { 1, 6, 21, 54, 66, 122, 655 };
	cout << binarySearch(niz, 21, 0, 6) << endl;

	Array<int> a1(5);
	for (int i = 0; i < a1.getLength(); i++)
		a1.setAt(i, i);
	a1.print();

	cout << "==========" << endl;

	Array<int> a2(2, 7);
	for (int i = 0; i < a2.getLength(); i++)
		a2.setAt(i, i + a2.getBase());
	a2.print();

	cout << "==========" << endl;

	a2 = a1;
	a2.print();

	cout << "==========" << endl;

	a2.setBase(5);
	a2.setAt(88, 7);
	a2.print();

	cout << "==========" << endl;

	int niz2[] = { 2, 5, 1, 4, 23, 41, 3, 4 };

	for (auto& x : niz2)
	{
		cout << x << " ";
	}

	selectionSort(niz2, 8);

	cout << endl;
	for (auto& x : niz2)
		cout << x << " ";
}