#ifndef _HOAREQUICKSORT_H
#define _HOAREQUICKSORT_H

#include "HoareQuickSort_common.h"

void HoareQuickSort(int* a, int first, int last, int type);
void HoareQuickSortNondecreasingOrder(int* a, int first, int last);
int HoarePartitionNondecreasingOrder(int* a, int first, int last);
void HoareQuickSortNonincreasingOrder(int* a, int first, int last);
int HoarePartitionNonincreasingOrder(int* a, int first, int last);

#endif