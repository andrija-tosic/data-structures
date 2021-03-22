#include "SparseMatrix.h"

int main() {
	SparseMatrix<int> mat(3);
	mat.SetAt(1, 0, 0);
	mat.SetAt(2, 1, 1);
	mat.SetAt(3, 2, 2);
	mat.Print();

	return 0;
}