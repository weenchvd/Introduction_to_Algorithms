#include "FindMaximumSubarray.h"
#include "FindMaximumSubarray_struct.h"

/* recursive algorithm */
MaxSubarraySet_t FindMaximumSubarrayR(int* a, int first, int last)
{
	int middle;
	if (first == last) {
		MaxSubarraySet_t set = { first, last, a[first] };
		return set;
	}
	else {
		middle = (first + last) / 2;
		MaxSubarraySet_t left = FindMaximumSubarrayR(a, first, middle);
		MaxSubarraySet_t right = FindMaximumSubarrayR(a, middle + 1, last);
		MaxSubarraySet_t cross = FindMaxCrossingSubarray(a, first, middle, last);
		if (left.sum >= right.sum && left.sum >= cross.sum) {
			return left;
		}
		else if (right.sum >= left.sum && right.sum >= cross.sum) {
			return right;
		}
		else {
			return cross;
		}
	}
}

MaxSubarraySet_t FindMaxCrossingSubarray(int* a, int first, int middle, int last)
{
	int i, maxleft, maxright;
	long long int leftsum, rightsum, sum;
	MaxSubarraySet_t cross;
	leftsum = LLONG_MIN;
	sum = 0;
	for (i = middle; i >= first; i--) {
		sum = sum + a[i];
		if (sum > leftsum) {
			leftsum = sum;
			maxleft = i;
		}
	}
	rightsum = LLONG_MIN;
	sum = 0;
	for (i = middle + 1; i <= last; i++) {
		sum = sum + a[i];
		if (sum > rightsum) {
			rightsum = sum;
			maxright = i;
		}
	}
	cross.first = maxleft;
	cross.last = maxright;
	cross.sum = leftsum + rightsum;
	return cross;
}

/* brute-force algorithm */
MaxSubarraySet_t FindMaximumSubarrayBF(int* a, int first, int last)
{
	int i, j, k, maxleft, maxright;
	long long int sum, tmp;
	MaxSubarraySet_t set;
	maxleft = first;
	maxright = first;
	sum = a[first];
	for (i = first; i <= last; i++) {
		for (j = i; j <= last; j++) {
			for (k = i, tmp = 0; k <= j; k++) {
				tmp += a[k];
			}
			if (tmp > sum) {
				sum = tmp;
				maxleft = i;
				maxright = j;
			}
		}
	}
	set.first = maxleft;
	set.last = maxright;
	set.sum = sum;
	return set;
}

/* linear-time algorithm */
MaxSubarraySet_t FindMaximumSubarray(int* a, int first, int last)
{
	int i, j, k, maxleft, maxright;
	long long int sum, tmp;
	MaxSubarraySet_t set;
	maxleft = first;
	maxright = first;
	sum = LLONG_MIN;
	for (j = first; j <= last; j++) {
		for (k = first, tmp = 0; k <= j; k++) {
			tmp += a[k];
		}
		if (tmp > sum) {
			sum = tmp;
			maxright = j;
		}
		else {
			break;
		}
	}
	for (; j <= last; j++) {
		for (i = maxleft; i <= j; i++) {
			for (k = i, tmp = 0; k <= j; k++) {
				tmp += a[k];
			}
			if (tmp > sum) {
				sum = tmp;
				maxleft = i;
				maxright = j;
			}
		}
	}
	set.first = maxleft;
	set.last = maxright;
	set.sum = sum;
	return set;
}