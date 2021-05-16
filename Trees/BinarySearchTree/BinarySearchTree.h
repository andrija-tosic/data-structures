#pragma once
#include "BinarySearchNode.h"
#include <iostream>

template <typename T>
class BinarySearchTree {
	BinarySearchNode<T>* root;
	unsigned count;

public:
	BinarySearchTree() {
		root = NULL;
		count = 0;
	}

	~BinarySearchTree() {
		deleteTree(root);
	}

	void insert(T key) {
		BinarySearchNode<T>* p = root, *prev = NULL;
		if (root == NULL) {
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

	void deleteByCopying(T key) {
		BinarySearchNode<T>* node = root;
		BinarySearchNode<T>* node_left_parent = NULL;
		BinarySearchNode<T>* node_right_parent = NULL;
		while (node != NULL && node->key != key) {
				
			if (node->key < key) {
				node_left_parent = node;
				node = node->right;
			}
			else {
				node_right_parent = node;
				node = node->left;
			}
		}
			
		if (node != NULL) {
			if (node->left == NULL && node->right == NULL) { // ako je list

				if (node_right_parent != NULL && node_right_parent->left == node) {
					node_right_parent->left = NULL;
				}
				else if (node_left_parent != NULL) {
					node_left_parent->right = NULL;
				}

				delete node;
				count--;
			}
			else if (node->left == NULL) { // ako nema levo podstablo
				if (node_right_parent != NULL && node_right_parent->left == node) {
					node_right_parent->left = node->right;
				}
				else if (node_left_parent != NULL) {
					node_left_parent->right = node->left;
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

					
				if (node_right_parent != NULL && node_right_parent->left == node) {
					node_right_parent->left = kd;
				}
				else if (node_left_parent != NULL) {
					node_left_parent->right = kd;
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

	void deleteByMerging(T key) {
		BinarySearchNode<T>* node = root;
		BinarySearchNode<T>* node_left_parent = NULL;
		BinarySearchNode<T>* node_right_parent = NULL;
		while (node != NULL && node->key != key) {

			if (node->key < key) {
				node_left_parent = node;
				node = node->right;
			}
			else {
				node_right_parent = node;
				node = node->left;
			}
		}

		if (node != NULL) {
			if (node->left == NULL && node->right == NULL) { // ako je list

				if (node_right_parent != NULL && node_right_parent->left == node) {
					node_right_parent->left = NULL;
				}
				else if (node_left_parent != NULL) {
					node_left_parent->right = NULL;
				}

				delete node;
				count--;
			}
			else if (node->left == NULL) { // ako nema levo podstablo
				if (node_right_parent != NULL && node_right_parent->left == node) {
					node_right_parent->left = node->right;
				}
				else if (node_left_parent != NULL) {
					node_left_parent->right = node->left;
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


				if (node_right_parent != NULL && node_right_parent->left == node) {
					node_right_parent->left = levo_podstablo;
				}
				else if (node_left_parent != NULL) {
					node_left_parent->right = levo_podstablo;
				}

				if (node == root)
					root = levo_podstablo;

				kd->right = node->right; // vazno

				delete node;
				count--;

			}
		}
	}

	BinarySearchNode<T>* search(T key) {
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

	void preorder(BinarySearchNode<T>* node) {
		if (node != NULL) {
			std::cout << node->key << std::endl;
			preorder(node->left);
			preorder(node->right);
		}
	}

	void inorder(BinarySearchNode<T>* node) {
		if (node != NULL) {
			inorder(node->left);
			std::cout << node->key << std::endl;
			inorder(node->right);
		}
	}

	void postorder(BinarySearchNode<T>* node) {
		if (node != NULL) {
			postorder(node->left);
			postorder(node->right);
			std::cout << node->key << std::endl;
		}
	}

	void print() {
		inorder(root);
	}

	void deleteTree(BinarySearchNode<T>* node) {
		std::cout << "Deleteing tree" << std::endl;
		postorder(node);
		delete node;
		count--;
	}
};