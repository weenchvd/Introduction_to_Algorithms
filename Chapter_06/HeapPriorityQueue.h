#ifndef _HEAPPRIORITYQUEUE_H
#define _HEAPPRIORITYQUEUE_H

#include "HeapPriorityQueue_common.h"
#include "HeapPriorityQueue_struct.h"
#include <stdio.h>

#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) (i << 1 | 1)
#define HEAPMAXIMUM(a) a[FIRSTITEMOFARRAY]
#define HEAPMINIMUM(a) a[FIRSTITEMOFARRAY]

void InitializeHeap(void);
Handle_t* HeapMax(Handle_t* set);
Handle_t* HeapExtractMax(Handle_t* set);
void HeapIncreaseKey(int index, int key);
void MaxHeapInsert(int key, int handle);
void MaxHeapDelete(int index);
void MaxHeapify(int index);
Handle_t* HeapMin(Handle_t* set);
Handle_t* HeapExtractMin(Handle_t* set);
void HeapDecreaseKey(int index, int key);
void MinHeapInsert(int key, int handle);
void MinHeapDelete(int index);
void MinHeapify(int index);
void PrintQueue();

#endif