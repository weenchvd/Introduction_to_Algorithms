#include "CountingSort.h"
#include <stdlib.h>
#include <stdio.h>  

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void CountingSort(int* a, int* b, int size, int k)
{
	int* c;
	int i, j;
	if ((c = malloc(sizeof(int) * ((size_t)k + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated (CountingSort()) |\n");
		return;
	}
	for (i = 0; i <= k; i++) {
		c[i] = 0;
	}
	for (j = 0; j < size; j++) {
		c[a[j]]++;
	}
	for (i = 1; i <= k; i++) {
		c[i] = c[i] + c[i - 1];
	}
	for (i = 0; i <= k; i++) {
		c[i]--;
	}
	for (j = size - 1; j >= 0; j--) {
		b[c[a[j]]] = a[j];
		c[a[j]]--;
	}
	free(c);
	return;
}