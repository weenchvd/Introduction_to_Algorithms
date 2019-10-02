#include "InsertionSort.h"

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void InsertionSort(int* a, size_t length, int type)
{
	int key;
	long long int i, j;
	if (type) {
		for (i = 1; i < length; ++i) {
			key = a[i];
			j = i - 1;
			while (j >= 0 && a[j] > key) {
				a[j + 1] = a[j--];
			}
			a[j + 1] = key;
		}
	}
	else {
		for (i = length - 2; i >= 0; --i) {
			key = a[i];
			j = i + 1;
			while (j < length && a[j] > key) {
				a[j - 1] = a[j++];
			}
			a[j - 1] = key;
		}
	}
	return;
}