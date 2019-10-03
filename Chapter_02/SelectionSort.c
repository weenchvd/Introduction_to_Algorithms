#include "SelectionSort.h"

/* nondecreasing order: type = 1
   nonincreasing order: type = 0 */
void SelectionSort(int* a, size_t length, int type)
{
	int tmp;
	long long int i, j, index;
	if (type) {
		for (i = 0; i < length - 1; ++i) {
			tmp = a[i];
			index = i;
			j = i + 1;
			while (j < length) {
				if (a[j] < a[index]) {
					index = j;
				}
				++j;
			}
			a[i] = a[index];
			a[index] = tmp;
		}
	}
	else {
		for (i = length - 1; i > 0; --i) {
			tmp = a[i];
			index = i;
			j = i - 1;
			while (j >= 0) {
				if (a[j] < a[index]) {
					index = j;
				}
				--j;
			}
			a[i] = a[index];
			a[index] = tmp;
		}
	}
	return;
}