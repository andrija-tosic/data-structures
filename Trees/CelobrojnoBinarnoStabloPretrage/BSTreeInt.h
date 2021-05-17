#pragma once

#include "BSTNodeInt.h"

class BSTreeInt
{
protected:
	BSTNodeInt* root;
	long numOfElements;

	void deleteTree(BSTNodeInt* ptr);

	void inorder(const BSTNodeInt* ptr) const;
	void preorder(const BSTNodeInt* ptr) const;
	void postorder(const BSTNodeInt* ptr) const;


	unsigned numberOfDistinctNodes(BSTNodeInt* node, BSTreeInt& tmp) const;
	unsigned height(BSTNodeInt* node) const;
	unsigned weight(BSTNodeInt* node) const;
	BSTNodeInt* deleteLeaves(BSTNodeInt* node);
	static void merge(BSTreeInt* merged, BSTNodeInt* node1, BSTNodeInt* node2);
	void maxWidthLevel(BSTNodeInt* node, int level, int* levels);
	int sumOfLeaves(BSTNodeInt* node);
	bool isBalanced(BSTNodeInt* node);
	int maxDifference(int& maxDif, BSTNodeInt* node);
	BSTNodeInt* maxDiffNode(int& maxDif, BSTNodeInt* node);
public:
	BSTreeInt() { root = nullptr; numOfElements = 0; }
	~BSTreeInt() { deleteTree(root); }

	bool isEmpty() const { return root == nullptr; }

	bool isInTree(int el) const { return search(el) != nullptr; }
	BSTNodeInt* search(int el) const;

	void insert(int el);
	void deleteByCopying(int el);
	void deleteByMerging(int el);

	void preorder() const { preorder(root); }
	void inorder() const { inorder(root); }
	void postorder() const { postorder(root); }

	void iterativePreorder() const;
	void breadthFirstSearch() const;


	unsigned numberOfDistinctNodes() const;
	unsigned height() const;
	unsigned weight() const;
	void deleteLeaves();
	static BSTreeInt* merge(BSTreeInt* tree1, BSTreeInt* tree2);
	int maxWidthLevel();
	int sumOfLeaves();
	bool isBalanced();
	int maxDifference(int& maxDif);
};
