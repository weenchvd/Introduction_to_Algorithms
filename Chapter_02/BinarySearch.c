#include "BinarySearch.h"

long long int BinarySearch(int* a, long long int first, long long int last, int target)
{
	long long int middle;
	while (first <= last) {
		middle = (first + last) / 2;
		if (target == a[middle]) {
			return middle;
		}
		else if (target > a[middle]) {
			first = middle + 1;
		}
		else {
			last = middle - 1;
		}
	}
	return NOTFOUND;
}