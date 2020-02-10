#include "FibonacciHeaps.h"

FibonacciHeap_t* CreateFibonacciHeap(void)
{
	FibonacciHeap_t* heap;
	if ((heap = malloc(sizeof(FibonacciHeap_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	heap->min = NULL;
	heap->n = 0;
	return heap;
}

FibonacciHeapNode_t* CreateFibonacciHeapNode(int key)
{
	FibonacciHeapNode_t* node;
	if ((node = malloc(sizeof(FibonacciHeapNode_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	node->parent = node->child = NULL;
	node->lsib = node->rsib = NULL;
	node->degree = 0;
	node->key = key;
	node->mark = FALSE;
	return node;
}

void FibonacciHeapInsert(FibonacciHeap_t* heap, FibonacciHeapNode_t* node)
{
	node->degree = 0;
	node->parent = NULL;
	node->child = NULL;
	node->mark = FALSE;
	if (heap->min == NULL) {
		node->lsib = node;
		node->rsib = node;
		heap->min = node;
	}
	else {
		node->lsib = heap->min->lsib;
		node->lsib->rsib = node;
		node->rsib = heap->min;
		node->rsib->lsib = node;
		if (node->key < heap->min->key) {
			heap->min = node;
		}
	}
	heap->n++;
	return;
}

FibonacciHeap_t* FibonacciHeapUnion(FibonacciHeap_t* heap1, FibonacciHeap_t* heap2)
{
	FibonacciHeap_t* heap;
	heap = CreateFibonacciHeap();
	heap->min = heap1->min;
	if (heap->min != NULL && heap2->min != NULL) {
		FibonacciHeapConcatenateLL(heap->min, heap2->min);
	}
	if (heap1->min == NULL || heap2->min != NULL && heap2->min->key < heap1->min->key) {
		heap->min = heap2->min;
	}
	heap->n = heap1->n + heap2->n;
	free(heap1);
	free(heap2);
	return heap;
}

FibonacciHeapNode_t* FibonacciHeapExtractMin(FibonacciHeap_t* heap)
{
	FibonacciHeapNode_t* node, * tmp;
	node = heap->min;
	if (node != NULL) {
		if (node->child != NULL) {
			tmp = node->child;
			do {
				tmp->parent = NULL;
				tmp = tmp->rsib;
			} while (tmp != node->child);
			FibonacciHeapConcatenateLL(node, node->child);
		}
		FibonacciHeapExtractNodeFromLL(node);
		if (node == node->rsib) {
			heap->min = NULL;
		}
		else {
			heap->min = node->rsib;
			FibonacciHeapConsolidate(heap);
		}
		heap->n--;
	}
	return node;
}

void FibonacciHeapConsolidate(FibonacciHeap_t* heap)
{
	int i, n, d;
	FibonacciHeapNode_t** a, * node, * node2, * next, * last, * current, * tmp;
	n = Log2(heap->n) + 1 + 1;
	if ((a = malloc(sizeof(FibonacciHeapNode_t*) * n)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return;
	}
	for (i = 0; i < n; i++) {
		a[i] = NULL;
	}
	last = heap->min->lsib;
	next = heap->min;
	do {
		current = node = next;
		next = next->rsib;
		d = node->degree;
		while (a[d] != NULL) {
			node2 = a[d];
			if (node->key > node2->key) {
				tmp = node;
				node = node2;
				node2 = tmp;
			}
			FibonacciHeapLink(node, node2);
			a[d] = NULL;
			d++;
		}
		a[d] = node;
	} while (current != last);
	heap->min = NULL;
	for (i = 0; i < n; i++) {
		if (a[i] != NULL) {
			FibonacciHeapCreateLL(a[i]);
			if (heap->min == NULL) {
				heap->min = a[i];
			}
			else {
				FibonacciHeapConcatenateLL(heap->min, a[i]);
				if (a[i]->key < heap->min->key) {
					heap->min = a[i];
				}
			}
		}
	}
	free(a);
	return;
}

/* the function removes NODE2 from the root list and makes NODE2 a child of NODE */
void FibonacciHeapLink(FibonacciHeapNode_t* node, FibonacciHeapNode_t* node2)
{
	node2->parent = node;
	FibonacciHeapCreateLL(node2);
	if (node->child == NULL) {
		node->child = node2;
	}
	else {
		FibonacciHeapConcatenateLL(node->child, node2);
	}
	node->degree++;
	node2->mark = FALSE;
	return;
}

/* the function extracts a root from a linked list */
void FibonacciHeapExtractNodeFromLL(FibonacciHeapNode_t* node)
{
	node->lsib->rsib = node->rsib;
	node->rsib->lsib = node->lsib;
	return;
}

/* the function creates a linked list from a root */
void FibonacciHeapCreateLL(FibonacciHeapNode_t* node)
{
	node->lsib = node->rsib = node;
	return;
}

/* the function inserts LINKEDLIST2 into LINKEDLIST1 */
void FibonacciHeapConcatenateLL(FibonacciHeapNode_t* nodefromlist1, FibonacciHeapNode_t* nodefromlist2)
{
	nodefromlist1->lsib->rsib = nodefromlist2->rsib;
	nodefromlist2->rsib->lsib = nodefromlist1->lsib;
	nodefromlist1->lsib = nodefromlist2;
	nodefromlist2->rsib = nodefromlist1;
	return;
}

int Log2(int n)
{
	int exp;
	for (exp = 0; n >>= 1; exp++);
	return exp;
}

void FibonacciHeapDecreaseKey(FibonacciHeap_t* heap, FibonacciHeapNode_t* node, int newkey)
{
	FibonacciHeapNode_t* parent;
	if (newkey > node->key) {
		printf("\n\t| ERROR | New key is greater than current key |\n\n");
		return;
	}
	node->key = newkey;
	parent = node->parent;
	if (parent != NULL && node->key < parent->key) {
		FibonacciHeapCut(heap, node, parent);
		FibonacciHeapCascadingCut(heap, parent);
	}
	if (node->key < heap->min->key) {
		heap->min = node;
	}
	return;
}

/* the function removes NODE from the child list of PARENT and inserts NODE into the root list */
void FibonacciHeapCut(FibonacciHeap_t* heap, FibonacciHeapNode_t* node, FibonacciHeapNode_t* parent)
{
	if (parent->degree == 1) {
		parent->child = NULL;
	}
	else {
#if DEBUG
		assert(parent->degree > 1);
#endif // DEBUG
		if (parent->child == node) {
			parent->child = node->rsib;
		}
		FibonacciHeapExtractNodeFromLL(node);
	}
	parent->degree--;
	FibonacciHeapCreateLL(node);
	FibonacciHeapConcatenateLL(heap->min, node);
	node->parent = NULL;
	node->mark = FALSE;
	return;
}

void FibonacciHeapCascadingCut(FibonacciHeap_t* heap, FibonacciHeapNode_t* node)
{
	FibonacciHeapNode_t* parent;
	parent = node->parent;
	if (parent != NULL) {
		if (node->mark == FALSE) {
			node->mark = TRUE;
		}
		else {
			FibonacciHeapCut(heap, node, parent);
			FibonacciHeapCascadingCut(heap, parent);
		}
	}
	return;
}

void FibonacciHeapDelete(FibonacciHeap_t* heap, FibonacciHeapNode_t* node)
{
	FibonacciHeapDecreaseKey(heap, node, INT_MIN);
	free(FibonacciHeapExtractMin(heap));
	return;
}

void PrintFibonacciHeap(FibonacciHeap_t* heap)
{
	if (heap != NULL) {
		if (heap->min != NULL) {
			printf("Minimal: Addr: %p  Key: %8d\n", heap->min, heap->min->key);
		}
		else {
			printf("The heap is empty\n");
		}
		PrintFibonacciHeapAllNodes(heap->min);
	}
	return;
}

void PrintFibonacciHeapAllNodes(FibonacciHeapNode_t* root)
{
	FibonacciHeapNode_t* node, * next, * last;
	if (root != NULL) {
		last = root->lsib;
		next = root;
		do {
			node = next;
			next = next->rsib;
			PrintFibonacciHeapNode(node);
			PrintFibonacciHeapAllNodes(node->child);
		} while (node != last);
	}
	return;
}

void PrintFibonacciHeapNode(FibonacciHeapNode_t* node)
{
	if (node != NULL) {
		printf("Addr: %p  Key: %8d  Degree: %3d  Mark: %-5s  Par: %p  Child: %p  Lsib: %p  Rsib: %p\n",
			node, node->key, node->degree, (node->mark == FALSE) ? "FALSE" : "TRUE", node->parent, node->child,
			node->lsib, node->rsib);
	}
	return;
}

FibonacciHeapNode_t* FindFibonacciHeapNode(FibonacciHeapNode_t* root, int key)
{
	FibonacciHeapNode_t* node, * next, * last, * target;
	if (root != NULL) {
		last = root->lsib;
		next = root;
		do {
			node = next;
			next = next->rsib;
			if (key == node->key) {
				return node;
			}
			target = FindFibonacciHeapNode(node->child, key);
			if (target != NULL) {
				return target;
			}
		} while (node != last);
	}
	return NULL;
}