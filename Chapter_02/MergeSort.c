#include "MergeSort.h"

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void MergeSort(int* a, long long int first, long long int last, int type)
{
	if (type) {
		MergeSortNondecreasingOrder(a, first, last);
		return;
	}
	else {
		MergeSortNonincreasingOrder(a, first, last);
		return;
	}
	return;
}

void MergeSortNondecreasingOrder(int* a, long long int first, long long int last)
{
	long long int middle;
	if (first < last) {
		middle = (first + last) / 2;
		MergeSortNondecreasingOrder(a, first, middle);
		MergeSortNondecreasingOrder(a, middle + 1, last);
		MergeNondecreasingOrder(a, first, middle, last);
	}
	return;
}

void MergeSortNonincreasingOrder(int* a, long long int first, long long int last)
{
	long long int middle;
	if (first < last) {
		middle = (first + last) / 2;
		MergeSortNonincreasingOrder(a, first, middle);
		MergeSortNonincreasingOrder(a, middle + 1, last);
		MergeNonincreasingOrder(a, first, middle, last);
	}
	return;
}

void MergeNondecreasingOrder(int* a, long long int first, long long int middle, long long int last)
{
	int* left, * right;
	long long int l1, l2, i, j, k;
	l1 = middle - first + 1;
	l2 = last - middle;
	if ((left = malloc(sizeof(int) * ((size_t)l1 + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	if ((right = malloc(sizeof(int) * ((size_t)l2 + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 0; i < l1; ++i) {
		left[i] = a[first + i];
	}
	for (j = 0; j < l2; ++j) {
		right[j] = a[middle + j + 1];
	}
	left[l1] = INT_MAX;
	right[l2] = INT_MAX;
	i = j = 0;
	for (k = first; k <= last; ++k) {
		if (left[i] <= right[j]) {
			a[k] = left[i++];
		}
		else {
			a[k] = right[j++];
		}
	}
	free(left);
	free(right);
	return;
}

void MergeNonincreasingOrder(int* a, long long int first, long long int middle, long long int last)
{
	int* left, * right;
	long long int l1, l2, i, j, k;
	l1 = middle - first + 1;
	l2 = last - middle;
	if ((left = malloc(sizeof(int) * ((size_t)l1 + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	if ((right = malloc(sizeof(int) * ((size_t)l2 + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 0; i < l1; ++i) {
		left[i] = a[first + i];
	}
	for (j = 0; j < l2; ++j) {
		right[j] = a[middle + j + 1];
	}
	left[l1] = INT_MIN;
	right[l2] = INT_MIN;
	i = j = 0;
	for (k = first; k <= last; ++k) {
		if (left[i] >= right[j]) {
			a[k] = left[i++];
		}
		else {
			a[k] = right[j++];
		}
	}
	free(left);
	free(right);
	return;
}