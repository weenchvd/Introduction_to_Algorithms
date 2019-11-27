#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct RedBlackTree {
	struct RedBlackTree* parent;
	struct RedBlackTree* left;
	struct RedBlackTree* right;
	struct RedBlackTree* suc;				/* successor */
	struct RedBlackTree* pred;				/* predecessor */
	int key;
	int color;
	int size;
} RBT_t;

typedef struct RedBlackTreePointers {
	struct RedBlackTree* nil;
	struct RedBlackTree* root;
	struct RedBlackTree* min;				/* minimum */
	struct RedBlackTree* max;				/* maximum */
} RBTPointers_t;

#endif