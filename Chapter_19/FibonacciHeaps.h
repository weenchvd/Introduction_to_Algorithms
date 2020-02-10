#ifndef _FIBONACCIHEAPS_H
#define _FIBONACCIHEAPS_H

#include "FibonacciHeaps_common.h"
#include "FibonacciHeaps_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

FibonacciHeap_t* CreateFibonacciHeap(void);
FibonacciHeapNode_t* CreateFibonacciHeapNode(int key);
void FibonacciHeapInsert(FibonacciHeap_t* heap, FibonacciHeapNode_t* node);
FibonacciHeap_t* FibonacciHeapUnion(FibonacciHeap_t* heap1, FibonacciHeap_t* heap2);
FibonacciHeapNode_t* FibonacciHeapExtractMin(FibonacciHeap_t* heap);
void FibonacciHeapConsolidate(FibonacciHeap_t* heap);
void FibonacciHeapLink(FibonacciHeapNode_t* node, FibonacciHeapNode_t* node2);
void FibonacciHeapExtractNodeFromLL(FibonacciHeapNode_t* node);
void FibonacciHeapCreateLL(FibonacciHeapNode_t* node);
void FibonacciHeapConcatenateLL(FibonacciHeapNode_t* nodefromlist1, FibonacciHeapNode_t* nodefromlist2);
int Log2(int n);
void FibonacciHeapDecreaseKey(FibonacciHeap_t* heap, FibonacciHeapNode_t* node, int newkey);
void FibonacciHeapCut(FibonacciHeap_t* heap, FibonacciHeapNode_t* node, FibonacciHeapNode_t* parent);
void FibonacciHeapCascadingCut(FibonacciHeap_t* heap, FibonacciHeapNode_t* node);
void FibonacciHeapDelete(FibonacciHeap_t* heap, FibonacciHeapNode_t* node);
void PrintFibonacciHeap(FibonacciHeap_t* heap);
void PrintFibonacciHeapAllNodes(FibonacciHeapNode_t* node);
void PrintFibonacciHeapNode(FibonacciHeapNode_t* node);
FibonacciHeapNode_t* FindFibonacciHeapNode(FibonacciHeapNode_t* root, int key);

#endif