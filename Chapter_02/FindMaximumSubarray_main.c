/* Chapter 4.1 | Find-Maximum-Subarray */

#include <stdio.h>
#include <stdlib.h>
#include "FindMaximumSubarray_struct.h"

enum returntype { ERROR = -1, SUCCESS };

MaxSubarraySet_t FindMaximumSubarrayR(int* a, int first, int last);
MaxSubarraySet_t FindMaximumSubarrayBF(int* a, int first, int last);
MaxSubarraySet_t FindMaximumSubarray(int* a, int first, int last);

int main(int argc, char* argv[])
{
	int* a;
	int i, length;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter a list of numbers to find maximum subarray as arguments to the program |\n");
		return ERROR;
	}
	if ((a = malloc(sizeof(int) * ((size_t)argc - 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	length = 0;
	for (i = 1; i < argc; i++) {
		a[length] = atoi(argv[i]);
		length++;
	}
	MaxSubarraySet_t setr = FindMaximumSubarrayR(a, 0, length - 1);
	printf("\nRecursive algorithm\n\tMaximum subarray: A[%d..%d]\n\tSum: %lld\n",
		setr.first + 1, setr.last + 1, setr.sum);
	MaxSubarraySet_t setbf = FindMaximumSubarrayBF(a, 0, length - 1);
	printf("\nBrute-force algorithm\n\tMaximum subarray: A[%d..%d]\n\tSum: %lld\n",
		setbf.first + 1, setbf.last + 1, setbf.sum);
	MaxSubarraySet_t set = FindMaximumSubarray(a, 0, length - 1);
	printf("\nLinear-time algorithm\n\tMaximum subarray: A[%d..%d]\n\tSum: %lld\n",
		set.first + 1, set.last + 1, set.sum);
	free(a);
	return SUCCESS;
}