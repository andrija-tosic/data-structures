#pragma once
#include "BinarySearchNode.h"
#include <iostream>

template <typename T>
class BinarySearchTree {
	BinarySearchNode<T>* root;
	unsigned count;

public:
	BinarySearchTree();
	~BinarySearchTree();
	void insert(T key);
	BinarySearchNode<T>* search(T key);
	void preorder(BinarySearchNode<T>* node);
	void inorder(BinarySearchNode<T>* node);
	void postorder(BinarySearchNode<T>* node);
	void print();
	void deleteTree(BinarySearchNode<T>* node);
	void deleteByCopying(T key);
	void deleteByMerging(T key);
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
	root = NULL;
	count = 0;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	deleteTree(root);
}

template <typename T>
void BinarySearchTree<T>::insert(T key) {
	BinarySearchNode<T>* p = root, *prev = NULL;
	if (root == NULL) { // prazno stablo
		root = new BinarySearchNode<T>(key);
		count++;
	}
	else {
		while (p != NULL) {
			prev = p;
			if (p->key < key) {
				p = p->right;
			}
			else {
				p = p->left;
			}
		}
		if (prev->key < key) {
			prev->right = new BinarySearchNode<T>(key);
		}
		else if (prev->key > key) {
			prev->left = new BinarySearchNode<T>(key);
		}
		count++;
	}
}

template <typename T>
void BinarySearchTree<T>::deleteByCopying(T key) {
	BinarySearchNode<T>* node = root;
	BinarySearchNode<T>* parent = NULL;
	while (node != NULL && node->key != key) {
		parent = node;
		if (node->key < key) {
			node = node->right;
		}
		else {
			node = node->left;
		}
	}
			
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) { // ako je list

			if (parent != NULL) {
				if (parent->left == node) {
					parent->left = NULL;
				}
				else {
					parent->right = NULL;
				}
			}

			delete node;
			count--;
		}
		else if (node->left == NULL) { // ako nema levo podstablo

			if (parent != NULL) {
				if (parent->left == node) {
					parent->left = node->right;
				}
				else {
					parent->right = node->left;
				}
			}
			delete node;
			count--;
		}
		else { // ako ima levo podstablo
			BinarySearchNode<T>* kd = node->left;
			BinarySearchNode<T>* prev = NULL;

			while (kd->right != NULL) { // trazi se krajnji desni iz levog podstabla
				prev = kd;
				kd = kd->right;
			}
					
			if (parent != NULL && parent->left == node) {
				parent->left = kd;
			}
			else if (parent != NULL) {
				parent->right = kd;
			}
					

			if (prev != NULL) // ako je levo podstablo nije samo 1 cvor
				prev->right = kd->left; // ako krajnji desni ima levo podstablo

			if (node->left != kd)
				kd->left = node->left;
					
			if (node->right != kd)
				kd->right = node->right;
					
			if (node == root)
				root = kd;

			delete node;
			count--;
		}
	}
}

template <typename T>
void BinarySearchTree<T>::deleteByMerging(T key) {
	BinarySearchNode<T>* node = root; // node to delete
	BinarySearchNode<T>* parent = NULL;

	while (node != NULL && node->key != key) {
		parent = node;
		if (node->key < key) {
			node = node->right;
		}
		else {
			node = node->left;
		}
	}

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) { // ako je list

			if (parent != NULL) {
				if (parent->left == node) {
					parent->left = NULL;
				}
				else {
					parent->right = NULL;
				}
			}

			delete node;
			count--;
		}
		else if (node->left == NULL) { // ako nema levo podstablo
			if (parent != NULL) {
				if (parent->left == node) {
					parent->left = node->right;
				}
				else {
					parent->right = node->left;
				}
			}

			delete node;
			count--;
		}
		else { // ako ima levo podstablo
			BinarySearchNode<T>* levo_podstablo = node->left;
			BinarySearchNode<T>* kd = node->left;
			BinarySearchNode<T>* prev = NULL;
			while (kd->right != NULL) { // trazi se krajnji desni iz levog podstabla
				prev = kd;
				kd = kd->right;
			}

			if (parent != NULL) {
				if (parent->left == node) {
					parent->left = levo_podstablo;
				}
				else {
					parent->right = levo_podstablo;
				}
			}

			if (node == root)
				root = levo_podstablo;

			kd->right = node->right; // vazno

			delete node;
			count--;

		}
	}
}

template <typename T>
BinarySearchNode<T>* BinarySearchTree<T>::search(T key) {
	BinarySearchNode<T>* p = root, prev = NULL;
	while (p != NULL && p->key != key) {
		prev = p;

		if (p->key < key) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return p;
}

template <typename T>
void BinarySearchTree<T>::preorder(BinarySearchNode<T>* node) {
	if (node != NULL) {
		std::cout << node->key << std::endl;
		preorder(node->left);
		preorder(node->right);
	}
}

template <typename T>
void BinarySearchTree<T>::inorder(BinarySearchNode<T>* node) {
	if (node != NULL) {
		inorder(node->left);
		std::cout << node->key << std::endl;
		inorder(node->right);
	}
}

template <typename T>
void BinarySearchTree<T>::postorder(BinarySearchNode<T>* node) {
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		std::cout << node->key << std::endl;
	}
}

template <typename T>
void BinarySearchTree<T>::print() {
	inorder(root);
}

template <typename T>
void BinarySearchTree<T>::deleteTree(BinarySearchNode<T>* node) {
	// std::cout << "Deleteing tree" << std::endl;
	if (node != NULL) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
		count--;
	}
}
