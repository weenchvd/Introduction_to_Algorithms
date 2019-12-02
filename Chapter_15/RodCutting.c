﻿#include "RodCutting.h"

int MemoizedCutRod(int* price, int n)
{
	int i, maxrev;
	int* rev;
	if ((rev = malloc(sizeof(int) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	for (i = 0; i <= n; i++) {
		rev[i] = INT_MIN;
	}
	maxrev = MemoizedCutRodAux(price, rev, n);
	free(rev);
	return maxrev;
}

int MemoizedCutRodAux(int* price, int* rev, int n)
{
	int i, maxrev;
	if (rev[n] >= 0) {
		return rev[n];
	}
	if (n == 0) {
		maxrev = 0;
	}
	else {
		maxrev = INT_MIN;
		for (i = 1; i <= n; i++) {
			maxrev = max(maxrev, price[i] + MemoizedCutRodAux(price, rev, n - i));
		}
	}
	rev[n] = maxrev;
	return maxrev;
}

int BottomUpCutRod(int* price, int n)
{
	int i, j, maxrev;
	int* rev;
	if ((rev = malloc(sizeof(int) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	rev[0] = 0;
	for (j = 1; j <= n; j++) {
		maxrev = INT_MIN;
		for (i = 1; i <= j; i++) {
			maxrev = max(maxrev, price[i] + rev[j - i]);
		}
		rev[j] = maxrev;
	}
	maxrev = rev[n];
	free(rev);
	return maxrev;
}

void PrintCutRodSolution(int* price, int n)
{
	int cond;
	int* rev, * cutsize;
	if ((rev = malloc(sizeof(int) * (n + 1))) == NULL || (cutsize = malloc(sizeof(int) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	ExtendedBottomUpCutRod(price, rev, cutsize, n);
	cond = n;
	printf("Sizes:");
	while (n > 0) {
		printf(" %d,", cutsize[n]);
		n = n - cutsize[n];
	}
	if (cond) {
		printf("\b ");
	}
	else {
		printf(" -");
	}
	putchar('\n');
	free(rev);
	free(cutsize);
	return;
}

void ExtendedBottomUpCutRod(int* price, int* rev, int* cutsize, int n)
{
	int i, j, maxrev, tmp;
	rev[0] = 0;
	for (j = 1; j <= n; j++) {
		maxrev = INT_MIN;
		for (i = 1; i <= j; i++) {
			if (maxrev < (tmp = price[i] + rev[j - i])) {
				maxrev = tmp;
				cutsize[j] = i;
			}
		}
		rev[j] = maxrev;
	}
	return;
}