#ifndef _ENHANCEDRANDOMIZEDQUICKSORT_H
#define _ENHANCEDRANDOMIZEDQUICKSORT_H

#include "EnhancedRandomizedQuickSort_common.h"
#include <stdlib.h>

#define RANDOM(a, b) rand() % (b - a + 1) + a

void EnhancedRandomizedQuickSort(int* a, int first, int last, int type);
void EnhancedRandomizedQuickSortNondecreasingOrder(int* a, int first, int last);
MiddleSet_t EnhancedRandomizedPartitionNondecreasingOrder(int* a, int first, int last);
MiddleSet_t EnhancedPartitionNondecreasingOrder(int* a, int first, int last);
void EnhancedRandomizedQuickSortNonincreasingOrder(int* a, int first, int last);
MiddleSet_t EnhancedRandomizedPartitionNonincreasingOrder(int* a, int first, int last);
MiddleSet_t EnhancedPartitionNonincreasingOrder(int* a, int first, int last);

#endif