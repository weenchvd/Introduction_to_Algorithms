#ifndef _ELEMENTARYGRAPHALGORITHMS_H
#define _ELEMENTARYGRAPHALGORITHMS_H

#include "ElementaryGraphAlgorithms_common.h"
#include "ElementaryGraphAlgorithms_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int CreateGraph(Graph_t* graph);
int IsVertexInAdjacencyList(AdjacencyList_t* adjset, GraphVertex_t* vertex);
void BreadthFirstSearch(Graph_t* graph, GraphVertex_t* vertex);
void DepthFirstSearch(Graph_t* graph, TopologicalList_t* tlist);
void DepthFirstSearchVisit(Graph_t* graph, GraphVertex_t* vertex, TopologicalList_t* tlist);
void Enqueue(Queue_t* q, GraphVertex_t* x);
GraphVertex_t* Dequeue(Queue_t* q);
inline int IsQueueEmpty(Queue_t* q);
inline int IsQueueFull(Queue_t* q);
void TopologicalSort(Graph_t* graph, TopologicalList_t* tlist);
void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void PrintGraph(Graph_t* graph);
void PrintBreadthFirstTree(Graph_t* graph);
void PrintDepthFirstTree(Graph_t* graph);
void PrintVertex(GraphVertex_t* vertex);
void PrintAdjacencyList(AdjacencyList_t* adjset);

#endif