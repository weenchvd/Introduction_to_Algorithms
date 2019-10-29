/* Chapter 9.2 | Randomized-Select */
/* Exercise 9.2-3 | Randomized-Select-Iterative */

#include "RandomizedSelect_common.h"
#include <stdio.h>
#include <stdlib.h>

int RandomizedSelect(int* a, int first, int last, int i);
int RandomizedSelectI(int* a, int first, int last, int i);

int main(int argc, char* argv[])
{
	int* a1;
	int i, size, num;
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
	while (TRUE) {
		printf("Please enter the number of the smallest element of the array: ");
		if (scanf("%d", &num) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		else if (num < 1 || num > size) {
			printf("The array element number must be between 1 and %d\n", size);
		}
		else {
			break;
		}
	}
	printf("\nThe smallest element of the array at number %d: %d", num, RandomizedSelect(a1, 0, size - 1, num));
	printf("\nThe smallest element of the array at number %d (iterative): %d\n", num, RandomizedSelectI(a1, 0, size - 1, num));
	free(a1);
	return SUCCESS;
}