#include "EnhancedRandomizedQuickSort.h"
#if DEBUG
#include <stdio.h>  
#endif // DEBUG

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void EnhancedRandomizedQuickSort(int* a, int first, int last, int type)
{
	if (type) {
		EnhancedRandomizedQuickSortNondecreasingOrder(a, first, last);
	}
	else {
		EnhancedRandomizedQuickSortNonincreasingOrder(a, first, last);
	}
	return;
}

void EnhancedRandomizedQuickSortNondecreasingOrder(int* a, int first, int last)
{
	MiddleSet_t middle;
	if (first < last) {
		middle = EnhancedRandomizedPartitionNondecreasingOrder(a, first, last);
		EnhancedRandomizedQuickSortNondecreasingOrder(a, first, middle.first - 1);
		EnhancedRandomizedQuickSortNondecreasingOrder(a, middle.last + 1, last);
	}
	return;
}

MiddleSet_t EnhancedRandomizedPartitionNondecreasingOrder(int* a, int first, int last)
{
	int i, tmp;
	i = RANDOM(first, last);
	tmp = a[last];
	a[last] = a[i];
	a[i] = tmp;
	return EnhancedPartitionNondecreasingOrder(a, first, last);
}

MiddleSet_t EnhancedPartitionNondecreasingOrder(int* a, int first, int last)
{
	int i, j, target, tmp;
	MiddleSet_t middle;
	target = a[last];
	i = first - 1;
	middle.first = middle.last = last;
	for (j = first; j < middle.first; j++) {
		if (a[j] < target) {
			tmp = a[++i];
			a[i] = a[j];
			a[j] = tmp;
		}
		else if (a[j] == target) {
			a[j--] = a[--middle.first];
		}
	}
	tmp = middle.last - middle.first + 1;
	for (j = ++i; middle.first <= middle.last; middle.first++, j++) {
		a[middle.first] = a[j];
	}
#if DEBUG
	if (tmp > 1) {
		putchar('%');
	}
#endif // DEBUG
	middle.first = i;
	for (; tmp > 0; tmp--, i++) {
		a[i] = target;
	}
	middle.last = i - 1;
	return middle;
}

void EnhancedRandomizedQuickSortNonincreasingOrder(int* a, int first, int last)
{
	MiddleSet_t middle;
	if (first < last) {
		middle = EnhancedRandomizedPartitionNonincreasingOrder(a, first, last);
		EnhancedRandomizedQuickSortNonincreasingOrder(a, first, middle.first - 1);
		EnhancedRandomizedQuickSortNonincreasingOrder(a, middle.last + 1, last);
	}
	return;
}

MiddleSet_t EnhancedRandomizedPartitionNonincreasingOrder(int* a, int first, int last)
{
	int i, tmp;
	i = RANDOM(first, last);
	tmp = a[last];
	a[last] = a[i];
	a[i] = tmp;
	return EnhancedPartitionNonincreasingOrder(a, first, last);
}

MiddleSet_t EnhancedPartitionNonincreasingOrder(int* a, int first, int last)
{
	int i, j, target, tmp;
	MiddleSet_t middle;
	target = a[last];
	i = first - 1;
	middle.first = middle.last = last;
	for (j = first; j < middle.first; j++) {
		if (a[j] > target) {
			tmp = a[++i];
			a[i] = a[j];
			a[j] = tmp;
		}
		else if (a[j] == target) {
			a[j--] = a[--middle.first];
		}
	}
	tmp = middle.last - middle.first + 1;
	for (j = ++i; middle.first <= middle.last; middle.first++, j++) {
		a[middle.first] = a[j];
	}
#if DEBUG
	if (tmp > 1) {
		putchar('%');
	}
#endif // DEBUG
	middle.first = i;
	for (; tmp > 0; tmp--, i++) {
		a[i] = target;
	}
	middle.last = i - 1;
	return middle;
}