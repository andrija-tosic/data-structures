#include "BTreeInt.h"

#include <exception>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"

void BTreeInt::deleteTree(BTNodeInt* ptr)
{
	if (ptr != nullptr) {
		deleteTree(ptr->left);
		deleteTree(ptr->right);
		delete ptr;
	}
}

void BTreeInt::preorder(const BTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		ptr->visit();
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void BTreeInt::inorder(const BTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		inorder(ptr->left);
		ptr->visit();
		inorder(ptr->right);
	}
}

void BTreeInt::postorder(const BTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		ptr->visit();
	}
}

void BTreeInt::iterativePreorder() const
{
	BTNodeInt* ptr = root;
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

void BTreeInt::breadthFirstSearch() const
{
	BTNodeInt* ptr = root;
	QueueAsArrayBSTNodeInt queue(numOfElements);
	if (ptr != nullptr) {
		queue.enqueue(ptr);
		while (!queue.isEmpty()) {
			ptr = queue.dequeue();
			ptr->visit();
			if (ptr->left != nullptr)
				queue.enqueue(ptr->left);
			if (ptr->right != nullptr)
				queue.enqueue(ptr->right);
		}
	}
}

void BTreeInt::insertSorted(BTNodeInt* node, BinaryMinHeapInt& minHeap, QueueAsArrayBSTNodeInt& q) {
	if (node == nullptr && !minHeap.isEmpty()) {
		root = new BTNodeInt(minHeap.deleteRoot());
		q.enqueue(root);
	}

	if (node != nullptr) {
		if (!minHeap.isEmpty()) {
			node->left = new BTNodeInt(minHeap.deleteRoot());
			q.enqueue(node->left);
		}
		if (!minHeap.isEmpty()) {
			node->right = new BTNodeInt(minHeap.deleteRoot());
			q.enqueue(node->right);
		}
	}

	if (!q.isEmpty())
		insertSorted(q.dequeue(), minHeap, q);

}

void BTreeInt::createFromMinHeap(BinaryMinHeapInt& minHeap)
{
	QueueAsArrayBSTNodeInt q(20);
	insertSorted(root, minHeap, q);
}

