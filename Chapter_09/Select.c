#include "Select.h"

int Select(int* a, int first, int last, int i)
{
	int* b, * c;
	int j, q, f, l, size, tmp, middle;
	if (first == last) {
		return a[first];
	}
	size = last - first + 1;
	tmp = size % GROUPSIZE;
	q = size / GROUPSIZE;
	size = tmp ? q + 1 : q;
	if ((b = malloc(sizeof(int) * (size_t)size)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	f = first - GROUPSIZE;
	l = first - 1;
	for (j = 0; j < q; j++) {
		f += GROUPSIZE;
		l += GROUPSIZE;
		b[j] = FindMedian(a, f, l);
	}
	if (tmp) {
		f += GROUPSIZE;
		l += tmp;
		b[q++] = FindMedian(a, f, l);
	}
	tmp = q % GROUPSIZE;
	q = q / GROUPSIZE;
	size = tmp ? q + 1 : q;
	if ((c = malloc(sizeof(int) * (size_t)size)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	f = ARRAYSTARTINDEX - GROUPSIZE;
	l = ARRAYSTARTINDEX - 1;
	for (j = 0; j < q; j++) {
		f += GROUPSIZE;
		l += GROUPSIZE;
		c[j] = FindMedian(b, f, l);
	}
	if (tmp) {
		f += GROUPSIZE;
		l += tmp;
		c[q] = FindMedian(b, f, l);
	} // q++, then q-- is omitted
	tmp = c[q / 2]; // tmp is a median
	free(b);
	free(c);
	middle = PartitionM(a, first, last, tmp);
	j = middle - first + 1;
	if (i == j) {
		return a[middle];
	}
	else if (i < j) {
		return Select(a, first, middle - 1, i);
	}
	else {
		return Select(a, middle + 1, last, i - j);
	}
}

int FindMedian(int* a, int first, int last)
{
	int i, j, key;
	for (i = first + 1; i <= last; i++) {
		key = a[i];
		j = i - 1;
		while (j >= first && a[j] > key) {
			a[j + 1] = a[j--];
		}
		a[j + 1] = key;
	}
	return a[(first + last) / 2];
}

int PartitionM(int* a, int first, int last, int target)
{
	int i, j, s, tmp;
	i = first - 1;
	for (j = first; j <= last; j++) {
		if (a[j] < target) {
			tmp = a[++i];
			a[i] = a[j];
			a[j] = tmp;
		}
		else if (a[j] == target) {
			tmp = a[++i];
			a[i] = a[j];
			a[j] = tmp;
			s = i;
		}
	}
	a[s] = a[i];
	a[i] = target;
	if (i == last) {
		tmp = 1;
		for (i = first; i <= last; i++) {
			if (a[i] != target) {
				tmp = 0;
				break;
			}
		}
		if (tmp) {
			i = (first + last) / 2;
		}
	}
	return i;
}