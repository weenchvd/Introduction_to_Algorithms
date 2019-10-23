/* Exercise 8.2-4 | Counting-Range */

#include "CountingRange_common.h"
#include <stdio.h>
#include <stdlib.h>

int CountingRangeQuery(int* c, int a, int b);

int main(int argc, char* argv[])
{
	int* a1, * c;
	int i, size, largest, a, b;
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
	largest = 0;
	for (i = 0; i < size; i++) {
		if (a1[i] > largest) {
			largest = a1[i];
		}
	}
	if ((c = malloc(sizeof(int) * ((size_t)largest + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	for (i = 0; i <= largest; i++) {
		c[i] = 0;
	}
	for (i = 0; i < size; i++) {
		c[a1[i]]++;
	}
	for (i = 1; i <= largest; i++) {
		c[i] = c[i] + c[i - 1];
	}
	while (TRUE) {
		printf("Please enter a range of \"A, B\": ");
		if (scanf("%d, %d", &a, &b) <= 0) {
			printf("\n\n\t| ERROR | Unacceptable \"A, B\" range |\n");
			break;
		}
		i = (b > largest) ? largest : b;
		printf("\n%d integer(s) fall into a range [%d..%d]\n", CountingRangeQuery(c, a, i), a, b);
	}
	putchar('\n');
	free(a1);
	free(c);
	return SUCCESS;
}