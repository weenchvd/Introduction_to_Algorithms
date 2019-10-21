#include "RandomizedQuickSort.h"
#if DEBUG
#include <stdio.h>  
#endif // DEBUG

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void RandomizedQuickSort(int* a, int first, int last, int type)
{
	if (type) {
		RandomizedQuickSortNondecreasingOrder(a, first, last);
	}
	else {
		RandomizedQuickSortNonincreasingOrder(a, first, last);
	}
	return;
}

void RandomizedQuickSortNondecreasingOrder(int* a, int first, int last)
{
	int middle;
	if (first < last) {
		middle = RandomizedPartitionNondecreasingOrder(a, first, last);
		RandomizedQuickSortNondecreasingOrder(a, first, middle - 1);
		RandomizedQuickSortNondecreasingOrder(a, middle + 1, last);
	}
	return;
}

int RandomizedPartitionNondecreasingOrder(int* a, int first, int last)
{
	int i, tmp;
	i = RANDOM(first, last);
	tmp = a[last];
	a[last] = a[i];
	a[i] = tmp;
	return PartitionNondecreasingOrder(a, first, last);
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

void RandomizedQuickSortNonincreasingOrder(int* a, int first, int last)
{
	int middle;
	if (first < last) {
		middle = RandomizedPartitionNonincreasingOrder(a, first, last);
		RandomizedQuickSortNonincreasingOrder(a, first, middle - 1);
		RandomizedQuickSortNonincreasingOrder(a, middle + 1, last);
	}
	return;
}

int RandomizedPartitionNonincreasingOrder(int* a, int first, int last)
{
	int i, tmp;
	i = RANDOM(first, last);
	tmp = a[last];
	a[last] = a[i];
	a[i] = tmp;
	return PartitionNonincreasingOrder(a, first, last);
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