#include "CountingRange.h"
#include <stdlib.h>
#include <stdio.h>  

int CountingRangeQuery(int* c, int a, int b)
{
	int j;
	if (a > 0) {
		j = c[b] - c[a - 1];
	}
	else {
		j = c[b];
	}
	return j;
}