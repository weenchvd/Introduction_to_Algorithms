#ifndef _HEAPSORT_H
#define _HEAPSORT_H

#include "HeapSort_common.h"

#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) (i << 1 | 1)

void HeapSortRecursive(int* a, int size, int type);
void HeapSortNondecreasingOrderR(int* a, int size);
void BuildMaxHeapR(int* a, int size);
void MaxHeapifyR(int* a, int size, int index);
void HeapSortNonincreasingOrderR(int* a, int size);
void BuildMinHeapR(int* a, int size);
void MinHeapifyR(int* a, int size, int index);
void HeapSortIterative(int* a, int size, int type);
void HeapSortNondecreasingOrderI(int* a, int size);
void BuildMaxHeapI(int* a, int size);
void MaxHeapifyI(int* a, int size, int index);
void HeapSortNonincreasingOrderI(int* a, int size);
void BuildMinHeapI(int* a, int size);
void MinHeapifyI(int* a, int size, int index);

#endif