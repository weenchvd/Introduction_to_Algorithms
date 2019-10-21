#include "QuickSort.h"
#if DEBUG
#include <stdio.h>  
#endif // DEBUG

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void QuickSort(int* a, int first, int last, int type)
{
	if (type) {
		QuickSortNondecreasingOrder(a, first, last);
	}
	else {
		QuickSortNonincreasingOrder(a, first, last);
	}
	return;
}

void QuickSortNondecreasingOrder(int* a, int first, int last)
{
	int middle;
	if (first < last) {
		middle = PartitionNondecreasingOrder(a, first, last);
		QuickSortNondecreasingOrder(a, first, middle - 1);
		QuickSortNondecreasingOrder(a, middle + 1, last);
	}
	return;
}

int PartitionNondecreasingOrder(int* a, int first, int last)
{
	int i, j, target, tmp;
	target = a[last];
	i = first - 1;
	for (j = first; j < last; j++) {
		if (a[j] <= target) {
			tmp = a[++i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}
	j = i + 1;
	tmp = a[j];
	a[j] = a[last];
	a[last] = tmp;
	if (j == last) {
		tmp = 1;
		for (i = first; i < last; i++) {
			if (a[i] != target) {
				tmp = 0;
				break;
			}
		}
		if (tmp) {
			j = (first + last) / 2;
#if DEBUG
			putchar('!');
#endif // DEBUG
		}
	}
	return j;
}

void QuickSortNonincreasingOrder(int* a, int first, int last)
{
	int middle;
	if (first < last) {
		middle = PartitionNonincreasingOrder(a, first, last);
		QuickSortNonincreasingOrder(a, first, middle - 1);
		QuickSortNonincreasingOrder(a, middle + 1, last);
	}
	return;
}

int PartitionNonincreasingOrder(int* a, int first, int last)
{
	int i, j, target, tmp;
	target = a[last];
	i = first - 1;
	for (j = first; j < last; j++) {
		if (a[j] >= target) {
			tmp = a[++i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}
	j = i + 1;
	tmp = a[j];
	a[j] = a[last];
	a[last] = tmp;
	if (j == last) {
		tmp = 1;
		for (i = first; i < last; i++) {
			if (a[i] != target) {
				tmp = 0;
				break;
			}
		}
		if (tmp) {
			j = (first + last) / 2;
#if DEBUG
			putchar('!');
#endif // DEBUG
		}
	}
	return j;
}