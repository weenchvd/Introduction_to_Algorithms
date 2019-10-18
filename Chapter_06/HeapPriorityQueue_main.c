/* Chapter 6.5 | Heap-Priority-Queue */

#include "HeapPriorityQueue_common.h"
#include "HeapPriorityQueue_struct.h"
#include <stdio.h>
#include <stdlib.h>

void InitializeHeap(void);
Handle_t* HeapMax(Handle_t* set);
Handle_t* HeapExtractMax(Handle_t* set);
void HeapIncreaseKey(int index, int key);
void MaxHeapInsert(int key, int handle);
void MaxHeapDelete(int index);
Handle_t* HeapMin(Handle_t* set);
Handle_t* HeapExtractMin(Handle_t* set);
void HeapDecreaseKey(int index, int key);
void MinHeapInsert(int key, int handle);
void MinHeapDelete(int index);
void PrintQueue();

int main(void)
{
	int key, handle, index, action;
	Handle_t set;
	InitializeHeap();
	printf("List of action:\n1 (HeapMax), 2 (HeapMin)\n");
	if (scanf("%d", &action) <= 0) {
		printf("\n\n\t| ERROR | Incorrect input |\n");
		return FAILURE;
	}
	if (action == 1) {
		printf("List of action:\n1 (HeapExtractMax), 2 (HeapIncreaseKey), 3 (MaxHeapInsert), 4 (MaxHeapDelete), "
			"5 (PrintQueue), 6 (HeapMax)\n");
		while (TRUE) {
			printf("\nPlease enter an action: ");
			if (scanf("%d", &action) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				continue;
			}
			switch (action) {
			case 1:
				if (HeapExtractMax(&set) == NULL) {
					continue;
				}
				printf("Extracted \"KEY, HANDLE\" pair:    %d, %d", set.priority, set.handle);
				break;
			case 2:
				printf("Please enter a pair of \"KEY, INDEX\": ");
				if (scanf("%d, %d", &key, &index) <= 0) {
					printf("\n\n\t| ERROR | Unacceptable \"KEY, INDEX\" pair |\n");
					continue;
				}
				HeapIncreaseKey(index, key);
				break;
			case 3:
				printf("Please enter a pair of \"KEY, HANDLE\": ");
				if (scanf("%d, %d", &key, &handle) <= 0) {
					printf("\n\n\t| ERROR | Unacceptable \"KEY, HANDLE\" pair |\n");
					continue;
				}
				MaxHeapInsert(key, handle);
				break;
			case 4:
				printf("Please enter \"INDEX\": ");
				if (scanf("%d", &index) <= 0) {
					printf("\n\n\t| ERROR | Unacceptable \"INDEX\" |\n");
					continue;
				}
				MaxHeapDelete(index);
				break;
			case 5:
				PrintQueue();
				break;
			case 6:
				if (HeapMax(&set) == NULL) {
					continue;
				}
				printf("Maximum \"KEY, HANDLE\" pair:    %d, %d", set.priority, set.handle);
				break;
			default:
				printf("\n\n\t| ERROR | Incorrect input |\n");
				break;
			}
		}
	}
	else if (action == 2) {
		printf("List of action:\n1 (HeapExtractMin), 2 (HeapDecreaseKey), 3 (MinHeapInsert), 4 (MinHeapDelete), "
			"5 (PrintQueue), 6 (HeapMin)\n");
		while (TRUE) {
			printf("\nPlease enter an action: ");
			if (scanf("%d", &action) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				continue;
			}
			switch (action) {
			case 1:
				if (HeapExtractMin(&set) == NULL) {
					continue;
				}
				printf("Extracted \"KEY, HANDLE\" pair:    %d, %d", set.priority, set.handle);
				break;
			case 2:
				printf("Please enter a pair of \"KEY, INDEX\": ");
				if (scanf("%d, %d", &key, &index) <= 0) {
					printf("\n\n\t| ERROR | Unacceptable \"KEY, INDEX\" pair |\n");
					continue;
				}
				HeapDecreaseKey(index, key);
				break;
			case 3:
				printf("Please enter a pair of \"KEY, HANDLE\": ");
				if (scanf("%d, %d", &key, &handle) <= 0) {
					printf("\n\n\t| ERROR | Unacceptable \"KEY, HANDLE\" pair |\n");
					continue;
				}
				MinHeapInsert(key, handle);
				break;
			case 4:
				printf("Please enter \"INDEX\": ");
				if (scanf("%d", &index) <= 0) {
					printf("\n\n\t| ERROR | Unacceptable \"INDEX\" |\n");
					continue;
				}
				MinHeapDelete(index);
				break;
			case 5:
				PrintQueue();
				break;
			case 6:
				if (HeapMin(&set) == NULL) {
					continue;
				}
				printf("Minimum \"KEY, HANDLE\" pair:    %d, %d", set.priority, set.handle);
				break;
			default:
				printf("\n\n\t| ERROR | Incorrect input |\n");
				break;
			}
		}
	}
	else {
		printf("\n\n\t| ERROR | Incorrect input |\n");
	}
	return SUCCESS;
}