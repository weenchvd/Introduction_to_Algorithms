/* Chapter 9.1 | Minimum-Maximum */

#include "MinimumMaximum_common.h"
#include <stdio.h>
#include <stdlib.h>

int Minimum(int* a, int size);
int Maximum(int* a, int size);
void MinimumMaximum(int* a, int size, int* min, int* max);

int main(int argc, char* argv[])
{
	int* a1;
	int i, size, min, max;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter a list of numbers to sort as arguments to the program |\n");
		return FAILURE;
	}
	if ((a1 = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	size = 0;
	for (i = 1; i < argc; i++) {
		a1[size++] = atoi(argv[i]);
	}
	MinimumMaximum(a1, size, &min, &max);
	printf("\nA pair of \"MIN, MAX\": %d, %d", min, max);
	printf("\nMIN: %d", Minimum(a1, size));
	printf("\nMAX: %d", Maximum(a1, size));
	putchar('\n');
	free(a1);
	return SUCCESS;
}