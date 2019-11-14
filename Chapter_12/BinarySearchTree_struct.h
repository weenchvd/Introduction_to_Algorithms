#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct BinarySearchTree {
	struct BinarySearchTree* parent;
	struct BinarySearchTree* left;
	struct BinarySearchTree* right;
	int key;
} BinarySearchTree_t;

typedef struct BSTStackSet {
	struct BinarySearchTree** stack;
	size_t ptr;
} BSTStackSet_t;

#endif