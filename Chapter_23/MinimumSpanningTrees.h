#ifndef _MINIMUMSPANNINGTREES_H
#define _MINIMUMSPANNINGTREES_H

#include "MinimumSpanningTrees_common.h"
#include "MinimumSpanningTrees_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define HEAPSTARTINDEX 1
#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) (i << 1 | 1)
#define HEAPMAXIMUM(a) a[HEAPSTARTINDEX]
#define HEAPMINIMUM(a) a[HEAPSTARTINDEX]

int CreateGraph(Graph_t* graph);
GraphVertex_t* CreateVertex();
AdjacencyList_t* CreateAdjacencySet();
int IsVertexInAdjacencyList(AdjacencyList_t* adjset, GraphVertex_t* vertex);
int GenericMST(Graph_t* graph, Queue_t* mst);
void Enqueue(Queue_t* q, GraphEdge_t* x);
GraphEdge_t* Dequeue(Queue_t* q);
inline int IsQueueEmpty(Queue_t* q);
inline int IsQueueFull(Queue_t* q);
void PrintGraph(Graph_t* graph);
void PrintVertex(GraphVertex_t* vertex);
void PrintAdjacencyList(AdjacencyList_t* adjset);
void PrintMST(Queue_t* mst);
HeapQueue_t* CreateHeapQueue(int heapsizelimit);
int InitializeHeap(HeapQueue_t* queue, int heapsizelimit);
HeapQueueSet_t* HeapMin(HeapQueue_t* queue, HeapQueueSet_t* set);
HeapQueueSet_t* HeapExtractMin(HeapQueue_t* queue, HeapQueueSet_t* set);
void HeapDecreaseKey(HeapQueue_t* queue, int index, int newpriority);
void MinHeapInsert(HeapQueue_t* queue, GraphEdge_t* handle);
void MinHeapDelete(HeapQueue_t* queue, int index);
void MinHeapify(HeapQueue_t* queue, int index);

void FreeAdjacencyList(AdjacencyList_t* adjset);

#endif