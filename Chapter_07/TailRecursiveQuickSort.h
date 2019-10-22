#ifndef _TAILRECURSIVEQUICKSORT_H
#define _TAILRECURSIVEQUICKSORT_H

#include "TailRecursiveQuickSort_common.h"
#include <stdlib.h>

#define RANDOM(a, b) rand() % (b - a + 1) + a

void TailRecursiveQuickSort(int* a, int first, int last, int type);
void TailRecursiveQuickSortNondecreasingOrder(int* a, int first, int last);
MiddleSet_t TailRecursivePartitionNondecreasingOrder(int* a, int first, int last);
MiddleSet_t EnhancedPartitionNondecreasingOrder(int* a, int first, int last);
void TailRecursiveQuickSortNonincreasingOrder(int* a, int first, int last);
MiddleSet_t TailRecursivePartitionNonincreasingOrder(int* a, int first, int last);
MiddleSet_t EnhancedPartitionNonincreasingOrder(int* a, int first, int last);

#endif