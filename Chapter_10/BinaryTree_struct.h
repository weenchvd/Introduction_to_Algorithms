#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct BinaryTree {
	struct BinaryTree* parent;
	struct BinaryTree* left;
	struct BinaryTree* right;
	int key;
} BinaryTree_t;

typedef struct StackSet {
	int* stack;
	int ptr;
} StackSet_t;

#endif