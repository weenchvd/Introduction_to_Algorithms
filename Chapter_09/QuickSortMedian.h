#ifndef _QUICKSORTMEDIAN_H
#define _QUICKSORTMEDIAN_H

#include "QuickSortMedian_common.h"
#include <stdio.h>
#include <stdlib.h>

#define SORTSIZE 5
#define GROUPSIZE 5

enum ReturnTypeFindMedianOfMedians { ERROR = INT_MIN };

void QuickSortMedian(int* a, int first, int last);
int FindMedianOfMedians(int* a, int first, int last);
int SortAndFindMedian(int* a, int first, int last);
int PartitionM(int* a, int first, int last, int target);

#endif