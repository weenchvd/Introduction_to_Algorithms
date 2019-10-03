#ifndef _MERGESORT_H
#define _MERGESORT_H

#include <stdio.h>
#include <stdlib.h>

void MergeSortNondecreasingOrder(int* a, long long int first, long long int last);
void MergeSortNonincreasingOrder(int* a, long long int first, long long int last);
void MergeNondecreasingOrder(int* a, long long int first, long long int middle, long long int last);
void MergeNonincreasingOrder(int* a, long long int first, long long int middle, long long int last);

#endif