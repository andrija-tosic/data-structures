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
public:
	int maxWidthLevel();
private:
	void maxWidthLevel(BSTNodeInt* node, int& maxCount, int& maxLvl, int levels[], int d);
public:
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

	void iterativeInorder() const;
	void iterativePostorder() const;


	unsigned numberOfDistinctNodes() const;
	unsigned height() const;
	unsigned weight() const;
	void deleteLeaves();
	static BSTreeInt* merge(BSTreeInt* tree1, BSTreeInt* tree2);
	int sumOfLeaves();
	bool isBalanced();
	int maxDifference(int& maxDif);
	int longestLeftPath();
private:
	void longestLeftPath(BSTNodeInt* node, int& l, int depth);
public:
	void balance(int* arr, int first, int last);
	void topmostNoChildren(BSTNodeInt* root, int level, BSTNodeInt** result, int* resultLevel);
	void topmostNoChildren(int* resultLevel);
public:
	int closestValueLeaf(int value);
private:
	BSTNodeInt* closestValueLeaf(BSTNodeInt* root, int value); // jun 2 2020.
private:
	void closestValueLeafDiff(BSTNodeInt* node, int value, BSTNodeInt** minNode, int& min);
public:
	int getDepth(int val);
private:
	int getDepth(BSTNodeInt* node, int dest, int level);
public:
	int CountGreater(int value); // popravni 2. kolokvijum 2015.
private:
	int countGreater(BSTNodeInt* node, int value);
public:
public:
	bool balanced();// 2. kolokvijum 2014.
private:
	int count(BSTNodeInt* node, bool& bal); // 2. kolokvijum 2014.
public:
	int maxSum();
private:
	BSTNodeInt* maxSum(BSTNodeInt* p, int& maxS);
};
