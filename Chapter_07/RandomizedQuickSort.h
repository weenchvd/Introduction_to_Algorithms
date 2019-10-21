#ifndef _RANDOMIZEDQUICKSORT_H
#define _RANDOMIZEDQUICKSORT_H

#include "RandomizedQuickSort_common.h"
#include <stdlib.h>

#define RANDOM(a, b) rand() % (b - a + 1) + a

void RandomizedQuickSort(int* a, int first, int last, int type);
void RandomizedQuickSortNondecreasingOrder(int* a, int first, int last);
int RandomizedPartitionNondecreasingOrder(int* a, int first, int last);
int PartitionNondecreasingOrder(int* a, int first, int last);
void RandomizedQuickSortNonincreasingOrder(int* a, int first, int last);
int RandomizedPartitionNonincreasingOrder(int* a, int first, int last);
int PartitionNonincreasingOrder(int* a, int first, int last);

#endif