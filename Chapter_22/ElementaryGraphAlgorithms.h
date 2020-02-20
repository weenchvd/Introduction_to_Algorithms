#ifndef _ELEMENTARYGRAPHALGORITHMS_H
#define _ELEMENTARYGRAPHALGORITHMS_H

#include "ElementaryGraphAlgorithms_common.h"
#include "ElementaryGraphAlgorithms_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int CreateGraph(GraphSet_t* graph);
int IsVertexInAdjacencyList(AdjacencyListSet_t* adjset, GraphVertex_t* vertex);
void BreadthFirstSearch(GraphSet_t* graph, GraphVertex_t* vertex);
void Enqueue(QueueSet_t* q, GraphVertex_t* x);
GraphVertex_t* Dequeue(QueueSet_t* q);
inline int IsQueueEmpty(QueueSet_t* q);
inline int IsQueueFull(QueueSet_t* q);
void PrintGraph(GraphSet_t* graph);
void PrintBreadthFirstTree(GraphSet_t* graph);
void PrintVertex(GraphVertex_t* vertex);
void PrintAdjacencyList(AdjacencyListSet_t* adjset);

#endif