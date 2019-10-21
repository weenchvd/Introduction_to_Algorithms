#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include "QuickSort_common.h"

void QuickSort(int* a, int first, int last, int type);
void QuickSortNondecreasingOrder(int* a, int first, int last);
int PartitionNondecreasingOrder(int* a, int first, int last);
void QuickSortNonincreasingOrder(int* a, int first, int last);
int PartitionNonincreasingOrder(int* a, int first, int last);

#endif