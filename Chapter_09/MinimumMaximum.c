#include "MinimumMaximum.h"

int Minimum(int* a, int size)
{
	int i, min;
	min = a[0];
	for (i = 1; i < size; i++) {
		if (min > a[i]) {
			min = a[i];
		}
	}
	return min;
}

int Maximum(int* a, int size)
{
	int i, max;
	max = a[0];
	for (i = 1; i < size; i++) {
		if (max < a[i]) {
			max = a[i];
		}
	}
	return max;
}

void MinimumMaximum(int* a, int size, int* min, int* max)
{
	int i, lmin, lmax;
	if (size % 2) {
		lmin = lmax = a[0];
		i = 1;
	}
	else if (a[0] < a[1]) {
		lmin = a[0];
		lmax = a[1];
		i = 2;
	}
	else {
		lmax = a[0];
		lmin = a[1];
		i = 2;
	}
	for (; i < size; i += 2) {
		if (a[i] < a[i + 1]) {
			if (lmin > a[i]) {
				lmin = a[i];
			}
			if (lmax < a[i + 1]) {
				lmax = a[i + 1];
			}
		}
		else {
			if (lmin > a[i + 1]) {
				lmin = a[i + 1];
			}
			if (lmax < a[i]) {
				lmax = a[i];
			}
		}
	}
	*min = lmin;
	*max = lmax;
	return;
}