#pragma once
#include <stddef.h>

template <typename T>
class BinarySearchNode {
	template <typename T>
	friend class BinarySearchTree;
	T key;
	BinarySearchNode<T> *left, *right;

	BinarySearchNode(T k) {
		key = k;
		left = NULL;
		right = NULL;
	}
};