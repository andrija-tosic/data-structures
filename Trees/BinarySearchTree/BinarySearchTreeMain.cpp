#include "BinarySearchTree.h"

int main() {
	BinarySearchTree<double> bst;

	bst.insert(7);
	bst.insert(10);
	bst.insert(6);
	bst.insert(1);
	bst.insert(6.5);
	bst.insert(6.2);
	bst.insert(8);
	bst.insert(9);
	bst.insert(12);
	bst.insert(11);
	bst.insert(11.5);

	bst.print();

	std::cout << std::endl;

	bst.deleteByMerging(7);

	bst.deleteByCopying(10);

	bst.deleteByMerging(6.2);

	bst.deleteByCopying(11.5);

	bst.print();

	std::cout << std::endl;
	
	return 0;
}