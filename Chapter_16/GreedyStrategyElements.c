#include "GreedyStrategyElements.h"

void ZeroOneKnapsackConstruct(KI_t* items)
{
	KATables_t t;
	ZeroOneKnapsackSolution(items, &t);
	printf("Items with the highest value of %d and a total weight of %d: ",
		t.v[vtitem(1, items->n, items->n)], t.w[wtitem(1, items->n, items->n)]);
	ZeroOneKnapsackSolutionPrint(&t, 1, items->n, items->n);
	printf("\b\b \n");
	free(t.v);
	free(t.w);
	return;
}

void ZeroOneKnapsackSolution(KI_t* items, KATables_t* t)		/* O(n^3) time */
{
	int i, j, n, l, k, maxv, maxw, cw;
	int* vt, * wt, * st;
	n = items->n;
	maxw = items->maxw;
	if ((t->v = t->s = vt = st = malloc(sizeof(int) * n * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	if ((t->w = wt = malloc(sizeof(int) * n * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 1; i <= n; i++) {
		vt[vtitem(i, i, n)] = items->v[i - 1];
		wt[wtitem(i, i, n)] = items->w[i - 1];
	}
	for (l = 2; l <= n; l++) {
		for (i = 1; i <= n - l + 1; i++) {
			j = i + l - 1;
			vt[vtitem(i, j, n)] = INT_MIN;
			wt[wtitem(i, j, n)] = INT_MAX;
			for (k = i; k <= j - 1; k++) {
				if ((cw = wt[wtitem(i, k, n)] + wt[wtitem(k + 1, j, n)]) <= maxw) {
					maxv = vt[vtitem(i, k, n)] + vt[vtitem(k + 1, j, n)];
					if (maxv > vt[vtitem(i, j, n)]) {
						vt[vtitem(i, j, n)] = maxv;
						wt[wtitem(i, j, n)] = cw;
						st[stitem(i, j, n)] = k;
					}
					else if (maxv == vt[vtitem(i, j, n)] && cw < wt[wtitem(i, j, n)]) {
						wt[wtitem(i, j, n)] = cw;
						st[stitem(i, j, n)] = k;
					}
				}
				else {
					if (vt[vtitem(k + 1, j, n)] > vt[vtitem(i, j, n)]) {
						vt[vtitem(i, j, n)] = vt[vtitem(k + 1, j, n)];
						wt[wtitem(i, j, n)] = wt[wtitem(k + 1, j, n)];
						st[stitem(i, j, n)] = IPLUS1;
					}
					else if (vt[vtitem(k + 1, j, n)] == vt[vtitem(i, j, n)] && wt[wtitem(k + 1, j, n)] < wt[wtitem(i, j, n)]) {
						wt[wtitem(i, j, n)] = wt[wtitem(k + 1, j, n)];
						st[stitem(i, j, n)] = IPLUS1;
					}
					if (vt[vtitem(i, k, n)] > vt[vtitem(i, j, n)]) {
						vt[vtitem(i, j, n)] = vt[vtitem(i, k, n)];
						wt[wtitem(i, j, n)] = wt[wtitem(i, k, n)];
						st[stitem(i, j, n)] = JMINUS1;
					}
					else if (vt[vtitem(i, k, n)] == vt[vtitem(i, j, n)] && wt[wtitem(i, k, n)] < wt[wtitem(i, j, n)]) {
						wt[wtitem(i, j, n)] = wt[wtitem(i, k, n)];
						st[stitem(i, j, n)] = JMINUS1;
					}
				}
				/*else {
					if (vt[vtitem(i, k, n)] < vt[vtitem(k + 1, j, n)]) {
						maxv = vt[vtitem(k + 1, j, n)];
						cw = wt[wtitem(k + 1, j, n)];
						cs = IPLUS1;
					}
					else if (vt[vtitem(i, k, n)] > vt[vtitem(k + 1, j, n)]) {
						maxv = vt[vtitem(i, k, n)];
						cw = wt[wtitem(i, k, n)];
						cs = JMINUS1;
					}
					else {
						maxv = vt[vtitem(i, k, n)];
						if (wt[wtitem(i, k, n)] < wt[wtitem(k + 1, j, n)]) {
							cw = wt[wtitem(k + 1, j, n)];
							cs = IPLUS1;
						}
						else if (wt[wtitem(i, k, n)] > wt[wtitem(k + 1, j, n)]) {
							cw = wt[wtitem(i, k, n)];
							cs = JMINUS1;
						}
						else {
							cs = 0;
						}
					}
					if (cs) {
						vt[vtitem(i, j, n)] = maxv;
						wt[wtitem(i, j, n)] = cw;
						st[stitem(i, j, n)] = cs;
					}
				}*/
			}
		}
	}
	return;
}

void ZeroOneKnapsackSolutionPrint(KATables_t* t, int i, int j, int n)
{
	int k;
	if (i == j) {
		printf("%d, ", i);
	}
	else if ((k = t->s[stitem(i, j, n)]) > 0) {
		ZeroOneKnapsackSolutionPrint(t, i, k, n);
		ZeroOneKnapsackSolutionPrint(t, k + 1, j, n);
	}
	else {
		if (k == IPLUS1) {
			ZeroOneKnapsackSolutionPrint(t, i + 1, j, n);
		}
		else {
			ZeroOneKnapsackSolutionPrint(t, i, j - 1, n);
		}
	}
	return;
}