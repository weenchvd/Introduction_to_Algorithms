#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct RedBlackTree {
	struct RedBlackTree* parent;
	struct RedBlackTree* left;
	struct RedBlackTree* right;
	int key;
	int color;
} RBT_t;

typedef struct RedBlackTreePointers {
	struct RedBlackTree* nil;
	struct RedBlackTree* root;
} RBTPointers_t;

#endif