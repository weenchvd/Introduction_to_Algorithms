/* Problem 7.4 | Enhanced-Randomized-Tail-Recursive-Quick-Sort */

#include "TailRecursiveQuickSort_common.h"
#include <stdio.h>
#include <stdlib.h>

void TailRecursiveQuickSort(int* a, int first, int last, int type);

int main(int argc, char* argv[])
{
	int* a1, * a2;
	int i, size;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter a list of numbers to sort as arguments to the program |\n");
		return FAILURE;
	}
	if ((a1 = malloc(sizeof(int) * ((size_t)argc - 1 + FIRSTITEMOFARRAY))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	if ((a2 = malloc(sizeof(int) * ((size_t)argc - 1 + FIRSTITEMOFARRAY))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}

	size = FIRSTITEMOFARRAY - 1;
	for (i = 1; i < argc; ++i) {
		size++;
		a1[size] = a2[size] = atoi(argv[i]);
	}
	TailRecursiveQuickSort(a1, FIRSTITEMOFARRAY, size, 1);
#if DEBUG
	putchar('\n');
#endif // DEBUG
	TailRecursiveQuickSort(a2, FIRSTITEMOFARRAY, size, 0);
	printf("\nNondecreasing order:\n");
	for (i = FIRSTITEMOFARRAY; i <= size; ++i) {
		printf("%d ", a1[i]);
	}
	printf("\n\nNonincreasing order:\n");
	for (i = FIRSTITEMOFARRAY; i <= size; ++i) {
		printf("%d ", a2[i]);
	}
	putchar('\n');
	free(a1);
	free(a2);
	return SUCCESS;
}