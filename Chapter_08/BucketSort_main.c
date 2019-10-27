/* Chapter 8.4 | Bucket-Sort */

#include "BucketSort_common.h"
#include <stdio.h>
#include <stdlib.h>

void BucketSort(double* a, int size);

int main(int argc, char* argv[])
{
	double* a1;
	int i, size;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter a list of numbers to sort as arguments to the program |\n");
		return FAILURE;
	}
	if ((a1 = malloc(sizeof(double) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	size = 0;
	for (i = 1; i < argc; i++) {
		a1[size++] = atof(argv[i]);
	}
	BucketSort(a1, size);
	printf("\n\nNondecreasing order:\n");
	for (i = 0; i < size; i++) {
		printf("%f ", a1[i]);
	}
	putchar('\n');
	free(a1);
	return SUCCESS;
}