#ifndef _SINGLESOURCESHORTESTPATHS_H
#define _SINGLESOURCESHORTESTPATHS_H

#include "SingleSourceShortestPaths_common.h"
#include "SingleSourceShortestPaths_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define INFINITY INT_MAX
#define INFINITYMINUS INT_MIN

#define HEAPSTARTINDEX 1
#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) (i << 1 | 1)
#define HEAPMINIMUM(a) a[HEAPSTARTINDEX]

int CreateGraph(Graph_t* graph);
GraphVertex_t* CreateVertex();
AdjacencyList_t* CreateAdjacencySet();
int IsVertexInAdjacencyList(AdjacencyList_t* adjset, GraphVertex_t* vertex);
void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void PrintGraph(Graph_t* graph);
void PrintVertex(GraphVertex_t* vertex);
void PrintAdjacencyList(AdjacencyList_t* adjset);
void InitializeSingleSource(Graph_t* graph, GraphVertex_t* source);
void Relax(GraphVertex_t* source, GraphVertex_t* destination, int edgeweight);
int WeightSummarization(int weight1, int weight2);
bool BellmanFord(Graph_t* graph, GraphVertex_t* source);
void DAGShortestPaths(Graph_t* graph, GraphVertex_t* source);
void Dijkstra(Graph_t* graph, GraphVertex_t* source);
void DepthFirstSearch(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order);
void DepthFirstSearchVisit(Graph_t* graph, GraphVertex_t* vertex, TopologicalList_t* tlist);
void TopologicalSort(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order);
void Enqueue(Queue_t* q, GraphVertex_t* x);
GraphVertex_t* Dequeue(Queue_t* q);
inline int IsQueueEmpty(Queue_t* q);
inline int IsQueueFull(Queue_t* q);
HeapQueue_t* CreateHeapQueue(int heapsizelimit);
int InitializeHeap(HeapQueue_t* queue, int heapsizelimit);
HeapQueueSet_t* HeapMin(HeapQueue_t* queue, HeapQueueSet_t* set);
HeapQueueSet_t* HeapExtractMin(HeapQueue_t* queue, HeapQueueSet_t* set);
void HeapDecreaseKey(HeapQueue_t* queue, int index, int newpriority);
void MinHeapInsert(HeapQueue_t* queue, GraphVertex_t* handle);
void MinHeapDelete(HeapQueue_t* queue, int index);
void MinHeapify(HeapQueue_t* queue, int index);
void FreeHeapQueue(HeapQueue_t* queue);

void FreeAdjacencyList(AdjacencyList_t* adjset);

#endif