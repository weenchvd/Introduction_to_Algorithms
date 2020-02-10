#ifndef _STRUCT_H
#define _STRUCT_H

#include "FibonacciHeaps_common.h"

typedef struct FibonacciHeapNode {
	struct FibonacciHeapNode* parent;
	struct FibonacciHeapNode* child;		/* pointer to any of the child nodes */
	struct FibonacciHeapNode* lsib;			/* left sibling */
	struct FibonacciHeapNode* rsib;			/* right sibling */
	int degree;								/* number of children in the child list */
	int key;
	char mark;
} FibonacciHeapNode_t;

typedef struct FibonacciHeap {
	struct FibonacciHeapNode* min;
	int n;									/* the number of nodes currently in FibonacciHeap */
} FibonacciHeap_t;

#endif