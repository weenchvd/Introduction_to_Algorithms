/* Exercise 9.3-3 | Quick-Sort-Median */

#include "QuickSortMedian_common.h"
#include <stdio.h>
#include <stdlib.h>

#define AMOUNTOFNUMBERS 1000000
#define MINNUMBER -9999
#define MAXNUMBER 9999
#define RANDOMNUMBER rand() % (MAXNUMBER - MINNUMBER + 1) + MINNUMBER

void QuickSortMedian(int* a, int first, int last);

int main(int argc, char* argv[])
{
	int* a1;
	int i, size, error, lasterror;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter an amount of numbers to sort as arguments to the program |\n");
		return FAILURE;
	}
	if ((size = atoi(argv[1])) < 1 || size > AMOUNTOFNUMBERS) {
		printf("\n\n\t| ERROR | The amount of numbers must be between 1 and %d |\n", AMOUNTOFNUMBERS);
		return FAILURE;
	}
	if ((a1 = malloc(sizeof(int) * size)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	for (i = ARRAYSTARTINDEX; i < size; i++) {
		a1[i] = RANDOMNUMBER;
	}
	printf("\nOriginal array:\n");
	for (i = 0; i < size; i++) {
		printf("%d ", a1[i]);
	}
	putchar('\n');
	QuickSortMedian(a1, ARRAYSTARTINDEX, size - 1);
	printf("\nNondecreasing order:\n");
	for (i = ARRAYSTARTINDEX; i < size; i++) {
		printf("%d ", a1[i]);
	}
	putchar('\n');
	error = 0;
	lasterror = INT_MIN;
	for (i = ARRAYSTARTINDEX + 1; i < size; i++) {
		if (a1[i - 1] > a1[i]) {
			error++;
			lasterror = a1[i];
		}
	}
	printf("\nErrors in sorting: %d", error);
	if (lasterror != INT_MIN) {
		printf("\nLast error on number: %d", lasterror);
	}
	putchar('\n');
	free(a1);
	return SUCCESS;
}