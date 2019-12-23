#include "OptimalBinarySearchTrees.h"

void BSTOptimalConstruct(BSTPr_t* pr)
{
	int ci;
	BSTATables_t t;
	BSTOptimal(pr, &t);
	printf("BSTOptimalPrint:\n");
	BSTOptimalPrint(pr, &t, 1, pr->n);
	printf("BSTOptimalPrint2:\n");
	ci = t.r[rtitem(1, pr->n, pr->n)];
	printf("\tk%d is the root\n", ci);
	BSTOptimalPrint2(pr, &t, 1, ci - 1, LEFT, ci);
	BSTOptimalPrint2(pr, &t, ci + 1, pr->n, RIGHT, ci);
	free(t.e);
	free(t.w);
	return;
}

void BSTOptimal(BSTPr_t* pr, BSTATables_t* t)
{
	int i, j, n, l, r, min;
	int* et, * wt, * rt;
	n = pr->n;
	if ((t->e = t->r = et = rt = malloc(sizeof(int) * (n + 1) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	if ((t->w = wt = malloc(sizeof(int) * (n + 1) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 1; i <= n + 1; i++) {
		et[etitem(i, (i - 1), n)] = wt[wtitem(i, (i - 1), n)] = pr->q[i - 1];
	}
	for (l = 1; l <= n; l++) {
		for (i = 1; i <= n - l + 1; i++) {
			j = i + l - 1;
			et[etitem(i, j, n)] = INT_MAX;
			wt[wtitem(i, j, n)] = wt[wtitem(i, (j - 1), n)] + pr->p[j] + pr->q[j];
			for (r = i; r <= j; r++) {
				min = et[etitem(i, (r - 1), n)] + et[etitem((r + 1), j, n)] + wt[wtitem(i, j, n)];
				if (min < et[etitem(i, j, n)]) {
					et[etitem(i, j, n)] = min;
					rt[rtitem(i, j, n)] = r;
				}
			}
		}
	}
	return;
}

void BSTOptimalPrint(BSTPr_t* pr, BSTATables_t* t, int i, int j)
{
	int ci;
	ci = t->r[rtitem(i, j, pr->n)];
	if (i == 1 && j == pr->n) {
		printf("\tk%d is the root\n", ci);
	}
	if (i > ci - 1) {
		printf("\td%d is the left child of k%d\n", i - 1, ci);
	}
	else {
		printf("\tk%d is the left child of k%d\n", t->r[rtitem(i, (ci - 1), pr->n)], ci);
		BSTOptimalPrint(pr, t, i, ci - 1);
	}
	if (j < ci + 1) {
		printf("\td%d is the right child of k%d\n", j, ci);
	}
	else {
		printf("\tk%d is the right child of k%d\n", t->r[rtitem((ci + 1), j, pr->n)], ci);
		BSTOptimalPrint(pr, t, ci + 1, j);
	}
	return;
}

void BSTOptimalPrint2(BSTPr_t* pr, BSTATables_t* t, int i, int j, int direction, int last)
{
	int ci;
	if (i <= j) {
		ci = t->r[rtitem(i, j, pr->n)];
		printf("\tk%d is the %s child of k%d\n", ci, (direction == LEFT) ? "left" : "right", last);
		BSTOptimalPrint2(pr, t, i, ci - 1, LEFT, ci);
		BSTOptimalPrint2(pr, t, ci + 1, j, RIGHT, ci);
	}
	else if (direction == LEFT) {
		printf("\td%d is the left child of k%d\n", i - 1, last);
	}
	else {
		printf("\td%d is the right child of k%d\n", j, last);
	}
	return;
}