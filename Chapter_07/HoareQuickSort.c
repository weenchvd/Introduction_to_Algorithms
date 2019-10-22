#include "HoareQuickSort.h"
#if DEBUG
#include <stdio.h>  
#endif // DEBUG

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void HoareQuickSort(int* a, int first, int last, int type)
{
	if (type) {
		HoareQuickSortNondecreasingOrder(a, first, last);
	}
	else {
		HoareQuickSortNonincreasingOrder(a, first, last);
	}
	return;
}

void HoareQuickSortNondecreasingOrder(int* a, int first, int last)
{
	int middle;
	if (first < last) {
		middle = HoarePartitionNondecreasingOrder(a, first, last);
		HoareQuickSortNondecreasingOrder(a, first, middle - 1);
		HoareQuickSortNondecreasingOrder(a, middle + 1, last);
	}
	return;
}

int HoarePartitionNondecreasingOrder(int* a, int first, int last)
{
	int i, j, target, tmp;
	target = a[first];
	i = first - 1;
	j = last + 1;
	while (TRUE) {
		while (a[--j] > target);
		while (a[++i] < target);
		if (i < j) {
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
		else {
			break;
		}
	}
	if (a[j] != target) {
		i = first - 1;
		while (a[++i] != target);
		if (i <= j) {
			a[i] = a[j];
			a[j] = target;
		}
		else {
			a[i] = a[++j];
			a[j] = target;
		}
	}
#if DEBUG
	else {
		putchar('$');
	}
#endif // DEBUG
	return j;
}

void HoareQuickSortNonincreasingOrder(int* a, int first, int last)
{
	int middle;
	if (first < last) {
		middle = HoarePartitionNonincreasingOrder(a, first, last);
		HoareQuickSortNonincreasingOrder(a, first, middle - 1);
		HoareQuickSortNonincreasingOrder(a, middle + 1, last);
	}
	return;
}

int HoarePartitionNonincreasingOrder(int* a, int first, int last)
{
	int i, j, target, tmp;
	target = a[first];
	i = first - 1;
	j = last + 1;
	while (TRUE) {
		while (a[--j] < target);
		while (a[++i] > target);
		if (i < j) {
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
		else {
			break;
		}
	}
	if (a[j] != target) {
		i = first - 1;
		while (a[++i] != target);
		if (i <= j) {
			a[i] = a[j];
			a[j] = target;
		}
		else {
			a[i] = a[++j];
			a[j] = target;
		}
	}
#if DEBUG
	else {
		putchar('$');
	}
#endif // DEBUG
	return j;
}