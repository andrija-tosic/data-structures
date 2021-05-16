#include "BSTreeInt.h"

#include <exception>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"

void BSTreeInt::deleteTree(BSTNodeInt* ptr)
{
	if (ptr != nullptr) {
		deleteTree(ptr->left);
		deleteTree(ptr->right);
		delete ptr;
	}
}

BSTNodeInt* BSTreeInt::search(int el) const
{
	BSTNodeInt* ptr = root;
	while (ptr != nullptr)
		if (ptr->isEQ(el))
			return ptr;
		else if (ptr->isGT(el))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	return nullptr;
}

void BSTreeInt::insert(int el)
{
	BSTNodeInt* ptr = root, * par = nullptr;
	while (ptr != nullptr) {  // trazenje mesta za umetanje novog cvora
		par = ptr;
		if (ptr->isLT(el))
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if (root == nullptr)    // stablo je prazno
		root = new BSTNodeInt(el);
	else if (par->isLT(el))
		par->right = new BSTNodeInt(el);
	else
		par->left = new BSTNodeInt(el);
	numOfElements++;
}

void BSTreeInt::deleteByCopying(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) { 	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)             // cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)         // cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			BSTNodeInt* parent = node;
			while (tmp->right != nullptr) {		// nalazenje krajnjeg desnog cvora
				parent = tmp;             		// u levom podstablu
				tmp = tmp->right;
			}
			node->setKey(tmp->getKey());		// prepisivanje reference na kljuc 
			if (parent == node)           		// tmp je direktni levi potomak node-a
				parent->left = tmp->left;		// ostaje isti raspored u levom podstablu
			else
				parent->right = tmp->left; 		// levi potomak tmp-a 
			delete tmp;							// se pomera na mesto tmp-a
			numOfElements--;
			return;
		}
		if (ptr == root)						// u slucaju (1) i (2) samo je pomerena
			root = node;						// referenca node pa je potrebno
		else if (par->left == ptr)				// izmeniti i link prethodnog cvora
			par->left = node;					// u slucaju (3) ovo nema dejstva
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::deleteByMerging(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) {	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)				// cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)			// cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			while (tmp->right != nullptr)		// nalazenje krajnjeg desnog cvora
				tmp = tmp->right;				// u levom podstablu
			tmp->right = node->right;			// prebacivanje desnog linka node-a u tmp
			node = node->left;					// na tekucem mestu bice prvi levi potomak
		}
		if (ptr == root)
			root = node;
		else if (par->left == ptr)
			par->left = node;
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::preorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		ptr->visit();
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void BSTreeInt::inorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		inorder(ptr->left);
		ptr->visit();
		inorder(ptr->right);
	}
}

void BSTreeInt::postorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		ptr->visit();
	}
}

void BSTreeInt::iterativePreorder() const
{
	BSTNodeInt* ptr = root;
	StackAsArrayBSTNodeInt stack(numOfElements);
	if (ptr != nullptr) {
		stack.push(ptr);
		while (!stack.isEmpty()) {
			ptr = stack.pop();
			ptr->visit();
			if (ptr->right != nullptr)	// levi potomak se stavlja u magacin
				stack.push(ptr->right); // posle desnog, da bi se prvi obradio
			if (ptr->left != nullptr)
				stack.push(ptr->left);
		}
	}
}

void BSTreeInt::breadthFirstSearch() const
{
	BSTNodeInt* ptr = root;
	QueueAsArrayBSTNodeInt queue(numOfElements);
	if (ptr != nullptr) {
		queue.enqueue(ptr);
		while (!queue.isEmpty()) {
			ptr = queue.dequeue();
			ptr->visit();
			if (ptr->left != nullptr) {
				queue.enqueue(ptr->left);
			}
			if (ptr->right != nullptr)
				queue.enqueue(ptr->right);
		}
	}
}

unsigned BSTreeInt::numberOfDistinctNodes() const {
	BSTreeInt distinct;
	unsigned br = numberOfDistinctNodes(root, distinct);
	return br;
}

unsigned BSTreeInt::numberOfDistinctNodes(BSTNodeInt* node, BSTreeInt& tmp) const {
	if (node != nullptr) {		
		if (!tmp.isInTree(node->getKey())) {
			tmp.insert(node->getKey());
		}
		numberOfDistinctNodes(node->left, tmp);
		numberOfDistinctNodes(node->right, tmp);
	}
	else {
		return tmp.numOfElements;
	}
}

unsigned BSTreeInt::height() const {
	return height(root);
}

unsigned BSTreeInt::height(BSTNodeInt* node) const {
	if (node == nullptr) {
		return 0;
	}

	if (height(node->left) > height(node->right))
		return 1 + height(node->left);
	else
		return 1 + height(node->right);
}

unsigned BSTreeInt::weight() const {
	return weight(root);
}

unsigned BSTreeInt::weight(BSTNodeInt* node) const {
	if (node == nullptr)
		return 0;

	if (node->left == nullptr && node->right == nullptr)
		return 1;

	return weight(node->left) + weight(node->right);
}

void BSTreeInt::deleteLeaves() {
	deleteLeaves(root);
}

BSTNodeInt* BSTreeInt::deleteLeaves(BSTNodeInt* node) {
	if (node == nullptr) {
		return nullptr;
	}
	if (node->left == nullptr && node->right == nullptr) {
		delete node;
		return nullptr;
	}
	node->left = deleteLeaves(node->left);
	node->right = deleteLeaves(node->right);

	return node;
}

BSTreeInt* BSTreeInt::merge(BSTreeInt* tree1, BSTreeInt* tree2) {
	BSTreeInt* merged = new BSTreeInt();

	merge(merged, tree1->root, tree2->root);

	return merged;
}

void BSTreeInt::merge(BSTreeInt* merged, BSTNodeInt* node1, BSTNodeInt* node2) {
	if (node1 != nullptr) {
		merge(merged, node1->left, nullptr);
		merged->insert(node1->getKey());
		merge(merged, node1->right, nullptr);
	}
	if (node2 != nullptr) {
		merge(merged, nullptr, node2->left);
		merged->insert(node2->getKey());
		merge(merged, nullptr, node2->right);

	}	
}

int indexOfMax(int* arr, int n) {
	int maxi = 0;

	for (int i = 0; i < n; i++)
		if (arr[i] > arr[maxi])
			maxi = i;
	return maxi;
}

int BSTreeInt::maxWidthLevel() {
	int* levels = new int[height()]();
	maxWidthLevel(root, 0, levels);
	return indexOfMax(levels, height());
}

void BSTreeInt::maxWidthLevel(BSTNodeInt* node, int level, int* levels) {
	if (node == nullptr)
		return;

	levels[level]++;

	maxWidthLevel(node->left, level + 1, levels);
	maxWidthLevel(node->right, level + 1, levels);
}

int BSTreeInt::sumOfLeaves() {
	return sumOfLeaves(root);
}

int BSTreeInt::sumOfLeaves(BSTNodeInt* node) {
	if (node == nullptr)
		return 0;

	if (node->left == nullptr && node->right == nullptr)
		return node->getKey();

	return sumOfLeaves(node->left) + sumOfLeaves(node->right);	
}

bool BSTreeInt::isBalanced() {
	return isBalanced(root);
}

int apsolutna(int x) {
	if (x >= 0)
		return x;
	else
		return -x;
}

bool BSTreeInt::isBalanced(BSTNodeInt* node) {
	if (node != nullptr)
	{
		if (apsolutna(height(node->left) - height(node->right)) <= 1)
			return true;
		else 
			return false;
	}
}
