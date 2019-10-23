/* Chapter 8.2 | Counting-Sort */

#include "CountingSort_common.h"
#include <stdio.h>
#include <stdlib.h>

void CountingSort(int* a, int* b, int size, int k);

int main(int argc, char* argv[])
{
	int* a1, * a2;
	int i, size, largest;
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
	size = 0;
	for (i = 1; i < argc; i++) {
		a1[size++] = atoi(argv[i]);
	}
	largest = 0;
	for (i = 0; i < size; i++) {
		if (a1[i] > largest) {
			largest = a1[i];
		}
	}
	CountingSort(a1, a2, size, largest);
	printf("\nOriginal array:\n");
	for (i = 0; i < size; i++) {
		printf("%d ", a1[i]);
	}
	printf("\n\nNondecreasing order:\n");
	for (i = 0; i < size; i++) {
		printf("%d ", a2[i]);
	}
	putchar('\n');
	free(a1);
	free(a2);
	return SUCCESS;
}