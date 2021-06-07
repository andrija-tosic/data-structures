#include "BSTreeInt.h"
#include <iostream>

int main()
{
	BSTreeInt bst;

	/*
	bst.insert(4);
	bst.insert(1);
	bst.insert(5);
	bst.insert(6);
	bst.insert(2);
	bst.insert(3);
	bst.insert(3);
	bst.insert(2);
	bst.insert(1);
	*/

	/*
	bst.insert(1);
	bst.insert(2);
	bst.insert(3);
	bst.insert(4);
	bst.insert(5);
	*/

	bst.insert(4);
	bst.insert(1);
	bst.insert(5);
	bst.insert(2);
	bst.insert(3);
	bst.insert(6);

	std::cout << bst.numberOfDistinctNodes() << std::endl;
	std::cout << bst.height() << std::endl;
	bst.deleteLeaves();
	bst.inorder();
	std::cout << "Weight: " <<  bst.weight() << std::endl;

	BSTreeInt bst1, bst2;

	bst1.insert(1);
	bst1.insert(3);
	bst1.insert(5);
	bst1.insert(4);
	bst1.insert(5);
	bst1.insert(6);
	bst1.insert(2);


	bst2.insert(2);
	bst2.insert(4);
	bst2.insert(6);
	bst2.insert(1);
	bst2.insert(3);
	bst2.insert(4);


	BSTreeInt* bst3 = BSTreeInt::merge(&bst1, &bst2);

	std::cout << "Merged preorder: " << std::endl;
	
	bst3->preorder();

	BSTreeInt bst4;

	bst4.insert(7);
	bst4.insert(4);
	bst4.insert(10);
	bst4.insert(6);
	bst4.insert(5);
	bst4.insert(8);
	bst4.insert(9);
	bst4.insert(12);


	std::cout << std::endl << std::endl;

	std::cout << "BST4 Max width on level: " << bst4.maxWidthLevel() << std::endl;

	std::cout << "BST4 Sum of leaves: " << bst4.sumOfLeaves() << std::endl;

	
	bst4.insert(2);
	bst4.insert(1);
	bst4.insert(0);
	bst4.insert(-1);
	bst4.insert(-2);
	

	std::cout << "BST4 Balanced: " << bst4.isBalanced() << std::endl;

	BSTreeInt bst5;

	bst5.insert(15);
	bst5.insert(13);
	bst5.insert(2);
	bst5.insert(3);
	bst5.insert(4);
	bst5.insert(5);
	bst5.insert(14);
	bst5.insert(16);
	bst5.insert(17);
	bst5.insert(18);
	bst5.insert(19);
	bst5.insert(20);

	int maxDif;

	std::cout << "BST5 Max difference: " << bst5.maxDifference(maxDif) << std::endl;

	std::cout << "BST4 Longest left path: " << bst4.longestLeftPath() << std::endl;
	std::cout << "BST5 Longest left path: " << bst5.longestLeftPath() << std::endl;

	BSTreeInt bst6;
	bst6.insert(4);
	bst6.insert(1);
	bst6.insert(5);
	bst6.insert(2);
	bst6.insert(3);
	bst6.insert(6);

	int level;
	bst6.topmostNoChildren(&level);
	std::cout << "Topmost no children bst6: " << level << std::endl;

	std::cout << "BST6 closestValueLeaf node: " << bst6.closestValueLeaf(6) << std::endl;

	std::cout << "BST6 Depth of node 1: " << bst6.getDepth(1) << std::endl;
	std::cout << "BST6 Depth of node 2: " << bst6.getDepth(2) << std::endl;
	std::cout << "BST6 Depth of node 3: " << bst6.getDepth(3) << std::endl;
	std::cout << "BST6 Depth of node 4: " << bst6.getDepth(4) << std::endl;
	std::cout << "BST6 Depth of node 5: " << bst6.getDepth(5) << std::endl;
	std::cout << "BST6 Depth of node 6: " << bst6.getDepth(6) << std::endl;
	return 0;
}
