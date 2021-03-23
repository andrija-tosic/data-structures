#include <iostream>
#include "MDArray.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int dim[] = { 2, 3, 4 }, m = 0;
	MDArray<int> a1(dim, 3);
	memset(dim, 0, sizeof(dim));
	for (int i = 0; i < 2; i++)
	{
		dim[0] = i;
		for (int j = 0; j < 3; j++)
		{
			dim[1] = j;
			for (int k = 0; k < 4; k++)
			{
				dim[2] = k;
				a1.setAt(m++, dim, 3);
				cout << "a1[" << i << "][" << j << "][" << k << "] = " << a1.getAt(dim, 3) << endl;
				dim[2]++;
			}
		}
	}
}