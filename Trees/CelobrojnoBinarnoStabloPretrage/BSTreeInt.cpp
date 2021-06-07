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

void BSTreeInt::iterativeInorder() const {
	BSTNodeInt* ptr = root;
	StackAsArrayBSTNodeInt stack(numOfElements);
	while (ptr != nullptr) {
		while (ptr != nullptr) {
			if (ptr->right != nullptr)
				stack.push(ptr->right);

			stack.push(ptr);
			ptr = ptr->left;
		}
		ptr = stack.pop();
		while (!stack.isEmpty() && ptr->right != nullptr) {
			ptr->visit();
			ptr = stack.pop();
		}
		ptr->visit();
		if (!stack.isEmpty()) {
			ptr = stack.pop();
		}
		else
			ptr = nullptr;
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
	int i = indexOfMax(levels, height());
	delete[] levels;
	return i;
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
	if (node == nullptr)
		return true;

	int razlika = apsolutna(height(node->left) - height(node->right));
	
	if (razlika > 1)
		return false;

	return isBalanced(node->left) && isBalanced(node->right);
}

int BSTreeInt::maxDifference(int& maxDif) {
	return maxDifference(maxDif, root);
}

int BSTreeInt::maxDifference(int& maxDif, BSTNodeInt* node) {
	return maxDiffNode(maxDif, node)->getKey();
}

BSTNodeInt* BSTreeInt::maxDiffNode(int& maxDif, BSTNodeInt* node) {
	if (node == nullptr) {
		maxDif = 0;
		return nullptr;
	}

	int maxDifL, maxDifR;

	BSTNodeInt* diffL = maxDiffNode(maxDifL, node->left);
	BSTNodeInt* diffR = maxDiffNode(maxDifR, node->right);

	int razlika = apsolutna(height(node->left) - height(node->right));

	BSTNodeInt* maxPtr = node;
	maxDif = razlika;
	
	if (maxDifL > maxDif) {
		maxDif = maxDifL;
		maxPtr = diffL;
	}

	if (maxDifR > maxDif) {
		maxDif = maxDifR;
		maxPtr = diffR;
	}

	return maxPtr;
}

int BSTreeInt::longestLeftPath() {
	int l = longestLeftPath(root->left, &root);
	int r = longestLeftPath(root->right, &root);
	return max(l, r);
}

int BSTreeInt::longestLeftPath(BSTNodeInt* node, BSTNodeInt** start) { // ova f menja start
	int maxL, maxR;
	BSTNodeInt** startL = start, ** startR = start, ** longestStart = start;
	if (start != nullptr) {

		maxL = 0;
		maxR = 0;
		longestLeftPath((*start)->left, start, maxL);
		longestLeftPath((*start)->right, start, maxR);


		maxL = 0;
		maxR = 0;
		longestLeftPath((*start)->left, &(*start)->left, maxL);
		longestLeftPath((*start)->right, &(*start)->right, maxR);

		if (maxL > maxR)
			longestStart = &(*start)->left;
		else
			longestStart = &(*start)->right;
	}

	start = longestStart;
	return max(maxL, maxR);
}

void BSTreeInt::longestLeftPath(BSTNodeInt* node, BSTNodeInt** start, int& maxP) {
	if (node == nullptr) {
		return;
	}

	longestLeftPath(node->left, start, ++maxP); // ova ide ulevo menja start
}

void BSTreeInt::balance(int* arr, int first, int last) {
	if (first <= last) {
		int s = (first + last) / 2;
		insert(arr[s]);
		balance(arr, first, s - 1);
		balance(arr, s + 1, last);
	}
}

void BSTreeInt::topmostNoChildren(int* resultLevel) {
	*resultLevel = INT_MAX;
	topmostNoChildren(root, 0, nullptr, resultLevel);
}

void BSTreeInt::topmostNoChildren(BSTNodeInt* root, int level, BSTNodeInt** result, int* resultLevel)
{
	if (root == nullptr)
		return;

	if (root->left == nullptr && root->right == nullptr && level < *resultLevel) {
		*resultLevel = level;
		result = &root;
	}
	else {
		topmostNoChildren(root->left, level + 1, result, resultLevel);
		topmostNoChildren(root->right, level + 1, result, resultLevel);
	}
}

int BSTreeInt::closestValueLeaf(int value) {
	return closestValueLeaf(root, value)->getKey();
}

BSTNodeInt* BSTreeInt::closestValueLeaf(BSTNodeInt* root, int value) {
	if (root == nullptr)
		return nullptr;

	BSTNodeInt* ptr = nullptr;
	int min = INT_MAX;

	closestValueLeafDiff(root, value, &ptr, min);

	return ptr;
}

void BSTreeInt::closestValueLeafDiff(BSTNodeInt* node, int value, BSTNodeInt** minNode, int& min) {
	if (node == nullptr)
		return;

	closestValueLeafDiff(node->left, value, minNode, min);
	closestValueLeafDiff(node->right, value, minNode, min);

	if (node->left == nullptr && node->right == nullptr) {
		if (abs(node->getKey() - value) < min) {
			min = abs(node->getKey() - value);
			*minNode = node;
		}
	}
}

int BSTreeInt::getDepth(int val) {
	int l = 0;
	return getDepth(root, val, l);
}

int BSTreeInt::getDepth(BSTNodeInt* node, int dest, int level) {
	if (node == nullptr)
		return 0;

	if (node->getKey() == dest)
		return level;

	int retVal = 0;
	retVal += getDepth(node->left, dest, level + 1);
	retVal += getDepth(node->right, dest, level + 1);

	return retVal;
}
