/* Chapter 2.3 | Binary-Search */

#include <stdio.h>
#include <stdlib.h>
#include "BinarySearch.h"

enum returntype { ERROR = -1, SUCCESS };

long long int BinarySearch(int* a, long long int first, long long int last, int target);

int main(int argc, char* argv[])
{
	int* a;
	int i, target;
	size_t length;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter a list of numbers to sort as arguments to the program |\n");
		return ERROR;
	}
	if ((a = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	printf("\nPlease enter a number to search: ");
	if ((i = scanf("%d", &target)) == EOF || i == 0) {
		printf("\n\n\t| ERROR | Invalid input |\n");
		return ERROR;
	}
	length = 0;
	for (i = 1; i < argc; ++i) {
		a[length] = atoi(argv[i]);
		++length;
	}
	if ((i = BinarySearch(a, 0, length - 1, target)) == NOTFOUND) {
		printf("Number not found\n");
	}
	else {
		printf("The index of the number: %d\n", i + 1);
	}
	free(a);
	return SUCCESS;
}