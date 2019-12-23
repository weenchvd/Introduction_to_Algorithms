#include "ActivitySelectionProblem.h"

void RecursiveActivitySelector(AS_t* as, int k)
{
	int m;
	m = k + 1;
	while (m <= as->n && as->s[m] < as->f[k]) {
		m++;
	}
	if (m <= as->n) {
		printf("%d, ", m);
		RecursiveActivitySelector(as, m);
	}
	return;
}

void GreedyActivitySelector(AS_t* as)
{
	int m, k;
	printf("%d, ", 1);
	for (k = 0, m = 1; m < as->n; m++) {
		if (as->s[m] >= as->f[k]) {
			printf("%d, ", m + 1);
			k = m;
		}
	}
	return;
}