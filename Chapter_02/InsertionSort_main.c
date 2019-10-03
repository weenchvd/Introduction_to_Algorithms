/* Chapter 2.1 | Insertion-Sort */

#include <stdio.h>
#include <stdlib.h>

enum returntype { ERROR = -1, SUCCESS };

void InsertionSort(int* a, size_t length, int type);

int main(int argc, char* argv[])
{
	int* a1, * a2;
	int i;
	size_t length;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter a list of numbers to sort as arguments to the program |\n");
		return ERROR;
	}
	if ((a1 = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	if ((a2 = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	length = 0;
	for (i = 1; i < argc; ++i) {
		a1[length] = a2[length] = atoi(argv[i]);
		length++;
	}
	InsertionSort(a1, length, 1);
	InsertionSort(a2, length, 0);
	printf("\nNondecreasing order:\n");
	for (i = 0; i < length; ++i) {
		printf("%d ", a1[i]);
	}
	printf("\n\nNonincreasing order:\n");
	for (i = 0; i < length; ++i) {
		printf("%d ", a2[i]);
	}
	putchar('\n');
	free(a1);
	free(a2);
	return SUCCESS;
}