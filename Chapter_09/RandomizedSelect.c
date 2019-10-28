#include "RandomizedSelect.h"

int RandomizedSelect(int* a, int first, int last, int i)
{
	int k, middle;
	if (first == last) {
		return a[first];
	}
	middle = RandomizedPartition(a, first, last);
	k = middle - first + 1;
	if (i == k) {
		return a[middle];
	}
	else if (i < k) {
		return RandomizedSelect(a, first, middle - 1, i);
	}
	else {
		return RandomizedSelect(a, middle + 1, last, i - k);
	}
}

int RandomizedPartition(int* a, int first, int last)
{
	int i, tmp;
	i = RANDOM(first, last);
	tmp = a[last];
	a[last] = a[i];
	a[i] = tmp;
	return Partition(a, first, last);
}

int Partition(int* a, int first, int last)
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
		}
	}
	return j;
}