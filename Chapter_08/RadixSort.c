#include "RadixSort.h"
#include <stdlib.h>
#include <stdio.h>

void RadixSort(int* a, int* b, int size)
{
	int* pa, * pb, * tmp;
	int i, j;
	int c[NUMBERSYSTEM];
	pa = a;
	pb = b;
	for (i = 0; i < NUMBEROFBITININTEGER; i++) {
		for (j = 0; j < NUMBERSYSTEM; j++) {
			c[j] = 0;
		}
		for (j = 0; j < size; j++) {
			c[(pa[j] & 1 << i) >> i]++;
		}
		for (j = 1; j < NUMBERSYSTEM; j++) {
			c[j] = c[j] + c[j - 1];
		}
		for (j = 0; j < NUMBERSYSTEM; j++) {
			c[j]--;
		}
		for (j = size - 1; j >= 0; j--) {
			pb[c[(pa[j] & 1 << i) >> i]] = pa[j];
			c[(pa[j] & 1 << i) >> i]--;
		}
		tmp = pa;
		pa = pb;
		pb = tmp;
	}
	if (pa != b) {
		for (j = 0; j < size; j++) {
			b[j] = pa[j];
		}
	}
	return;
}