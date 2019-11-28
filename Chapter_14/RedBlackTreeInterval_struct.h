#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct Interval {
	int low;
	int high;
} Interval_t;

typedef struct RedBlackTree {
	struct RedBlackTree* parent;
	struct RedBlackTree* left;
	struct RedBlackTree* right;
	struct Interval invl;
	int color;
	int max;
} RBT_t;

typedef struct RedBlackTreePointers {
	struct RedBlackTree* nil;
	struct RedBlackTree* root;
} RBTPointers_t;

#endif