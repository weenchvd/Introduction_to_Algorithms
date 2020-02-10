/* Chapter 19.1 | Fibonacci-Heaps */
/* Chapter 19.2 | Fibonacci-Heaps */
/* Chapter 19.3 | Fibonacci-Heaps */

#include "FibonacciHeaps_common.h"
#include "FibonacciHeaps_struct.h"
#include <stdio.h>
#include <stdlib.h>

FibonacciHeap_t* CreateFibonacciHeap(void);
FibonacciHeapNode_t* CreateFibonacciHeapNode(int key);
void FibonacciHeapInsert(FibonacciHeap_t* heap, FibonacciHeapNode_t* node);
FibonacciHeap_t* FibonacciHeapUnion(FibonacciHeap_t* heap1, FibonacciHeap_t* heap2);
FibonacciHeapNode_t* FibonacciHeapExtractMin(FibonacciHeap_t* heap);
void FibonacciHeapDecreaseKey(FibonacciHeap_t* heap, FibonacciHeapNode_t* node, int newkey);
void FibonacciHeapDelete(FibonacciHeap_t* heap, FibonacciHeapNode_t* node);
void PrintFibonacciHeap(FibonacciHeap_t* heap);
void PrintFibonacciHeapNode(FibonacciHeapNode_t* node);
int GetHeapNumber(void);
FibonacciHeap_t* GetHeapAddress(FibonacciHeap_t* heap1, FibonacciHeap_t* heap2);
FibonacciHeapNode_t* FindFibonacciHeapNode(FibonacciHeapNode_t* root, int key);

int main(void)
{
	int cond, action, key, number;
	FibonacciHeap_t* heap, * heap1, * heap2;
	FibonacciHeapNode_t* node;
	char* list = "\tList of action: -1 (EXIT), 0 (List of action),\n"
		"1 (CreateFibonacciHeap), 2 (FibonacciHeapInsert), 3 (FibonacciHeapUnion),\n"
		"4 (FibonacciHeapExtractMin), 5 (FibonacciHeapDecreaseKey), 6 (FibonacciHeapDelete)\n"
		"7 (PrintFibonacciHeap)\n\n";
	printf(list);
	heap = heap1 = heap2 = NULL;
	node = NULL;
	cond = TRUE;
	while (cond) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\t| ERROR | Incorrect input |\n\n");
			return FAILURE;
		}
		switch (action) {
		case -1:
			cond = FALSE;
			break;
		case 0:
			printf(list);
			break;
		case 1:
			number = GetHeapNumber();
			if (number == 1) {
				if (heap1 == NULL) {
					heap1 = CreateFibonacciHeap();
					printf("Heap #1 created\n");
				}
				else {
					printf("\n\t| ERROR | Heap #1 already exists |\n\n");
				}
			}
			else if (number == 2) {
				if (heap2 == NULL) {
					heap2 = CreateFibonacciHeap();
					printf("Heap #2 created\n");
				}
				else {
					printf("\n\t| ERROR | Heap #2 already exists |\n\n");
				}
			}
			break;
		case 2:
			heap = GetHeapAddress(heap1, heap2);
			if (heap == NULL) {
				break;
			}
			printf("Please enter a key for the node: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				return FAILURE;
			}
			if (key > INT_MIN && key <= INT_MAX) {
				FibonacciHeapInsert(heap, CreateFibonacciHeapNode(key));
				printf("Node with key %d inserted in the Fibonacci Heap\n", key);
			}
			else {
				printf("\n\t| ERROR | Key must be greater than %d and less or equal to %d |\n\n", INT_MIN, INT_MAX);
			}
			break;
		case 3:
			if (heap1 != NULL && heap2 != NULL) {
				heap1 = FibonacciHeapUnion(heap1, heap2);
				heap2 = NULL;
				printf("Heap 1 and heap 2 are combined\n");
			}
			else if (heap1 == NULL) {
				printf("\n\t| ERROR | Heap #1 does not exist |\n\n");
			}
			else {
				printf("\n\t| ERROR | Heap #2 does not exist |\n\n");
			}
			break;
		case 4:
			heap = GetHeapAddress(heap1, heap2);
			if (heap == NULL) {
				break;
			}
			node = FibonacciHeapExtractMin(heap);
			if (node != NULL) {
				printf("The node\n");
				PrintFibonacciHeapNode(node);
				printf("is extracted\n");
				free(node);
			}
			else {
				printf("\n\t| ERROR | The heap is empty |\n\n");
			}
			break;
		case 5:
			heap = GetHeapAddress(heap1, heap2);
			if (heap == NULL) {
				break;
			}
			printf("Please enter the current key of the node: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				return FAILURE;
			}
			if (key > INT_MIN && key <= INT_MAX) {
				node = FindFibonacciHeapNode(heap->min, key);
				if (node == NULL) {
					printf("\n\t| ERROR | The node with this key was not found |\n\n");
					break;
				}
				printf("Please enter the new key for the node: ");
				if (scanf("%d", &key) <= 0) {
					printf("\n\t| ERROR | Incorrect input |\n\n");
					return FAILURE;
				}
				if (key > INT_MIN && key <= INT_MAX) {
					FibonacciHeapDecreaseKey(heap, node, key);
					printf("The node key was decreased\n");
				}
				else {
					printf("\n\t| ERROR | New key must be greater than %d and less or equal to %d |\n\n", INT_MIN, INT_MAX);
				}
			}
			else {
				printf("\n\t| ERROR | Key must be greater than %d and less or equal to %d |\n\n", INT_MIN, INT_MAX);
			}
			break;
		case 6:
			heap = GetHeapAddress(heap1, heap2);
			if (heap == NULL) {
				break;
			}
			printf("Please enter the current key of the node: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				return FAILURE;
			}
			if (key > INT_MIN && key <= INT_MAX) {
				node = FindFibonacciHeapNode(heap->min, key);
				if (node == NULL) {
					printf("\n\t| ERROR | The node with this key was not found |\n\n");
					break;
				}
				FibonacciHeapDelete(heap, node);
				printf("The node was deleted\n");
			}
			else {
				printf("\n\t| ERROR | Key must be greater than %d and less or equal to %d |\n\n", INT_MIN, INT_MAX);
			}
			break;
		case 7:
			heap = GetHeapAddress(heap1, heap2);
			PrintFibonacciHeap(heap);
			break;
		default:
			printf("\n\t| ERROR | Incorrect input |\n\n");
			break;
		}
	}
	free(heap1);
	free(heap2);
	return SUCCESS;
}

int GetHeapNumber(void)
{
	int number;
	printf("Please enter a number of the heap (1 or 2): ");
	if (scanf("%d", &number) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (number != 1 && number != 2) {
		printf("\n\t| ERROR | The number must be 1 or 2 |\n\n");
		number = FALSE;
	}
	return number;
}

FibonacciHeap_t* GetHeapAddress(FibonacciHeap_t* heap1, FibonacciHeap_t* heap2)
{
	int number;
	FibonacciHeap_t* heap;
	printf("Please enter a number of the heap (1 or 2): ");
	if (scanf("%d", &number) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (number == 1) {
		heap = heap1;
		if (heap == NULL) {
			printf("\n\t| ERROR | Heap #1 does not exist |\n\n");
		}
	}
	else if (number == 2) {
		heap = heap2;
		if (heap == NULL) {
			printf("\n\t| ERROR | Heap #2 does not exist |\n\n");
		}
	}
	else {
		heap = NULL;
		printf("\n\t| ERROR | The number must be 1 or 2 |\n\n");
	}
	return heap;
}