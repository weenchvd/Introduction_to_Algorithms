/* Chapter 6.1 - 6.4 | Heap-Sort */

#include "HeapSort_common.h"
#include <stdio.h>
#include <stdlib.h>

void HeapSortRecursive(int* a, int size, int type);
void HeapSortIterative(int* a, int size, int type);

int main(int argc, char* argv[])
{
	int* a1, * a2, * a3, * a4;
	int i;
	size_t length;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter a list of numbers to sort as arguments to the program |\n");
		return FAILURE;
	}
	if ((a1 = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	if ((a2 = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	if ((a3 = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	if ((a4 = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	length = 0;
	for (i = 1; i < argc; ++i) {
		a1[length] = a2[length] = a3[length] = a4[length] = atoi(argv[i]);
		length++;
	}
	HeapSortRecursive(a1, length, 1);
	HeapSortRecursive(a2, length, 0);
	HeapSortIterative(a3, length, 1);
	HeapSortIterative(a4, length, 0);
	printf("\nNondecreasing order (recursive):\n");
	for (i = 0; i < length; ++i) {
		printf("%d ", a1[i]);
	}
	printf("\n\nNonincreasing order (recursive):\n");
	for (i = 0; i < length; ++i) {
		printf("%d ", a2[i]);
	}
	printf("\n\nNondecreasing order (iterative):\n");
	for (i = 0; i < length; ++i) {
		printf("%d ", a3[i]);
	}
	printf("\n\nNonincreasing order (iterative):\n");
	for (i = 0; i < length; ++i) {
		printf("%d ", a4[i]);
	}
	putchar('\n');
	free(a1);
	free(a2);
	free(a3);
	free(a4);
	return SUCCESS;
}