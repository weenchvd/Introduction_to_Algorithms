#ifndef _STRUCT_H
#define _STRUCT_H

#include "MinimumSpanningTrees_common.h"

typedef struct Graph {
	struct AdjacencyList** adjlist;
	struct GraphVertex** vertlist;
	int vertexnum;							/* number of vertices */
	int edgenum;							/* number of edges */
	char type;								/* graph type: directed or undirected */
} Graph_t;

typedef struct GraphVertex {
	struct GraphVertex* parent;
	int number;
	int distance;
	int discovered;
	int finished;
	char color;
} GraphVertex_t;

typedef struct GraphEdge {
	struct GraphVertex* vertex1;
	struct GraphVertex* vertex2;
	int weight;
} GraphEdge_t;

typedef struct AdjacencyList {
	struct GraphVertex* vertex;
	struct AdjacencyList* next;
	int weight;
} AdjacencyList_t;

typedef struct Queue {
	struct GraphEdge** queue;
	unsigned int size;
	unsigned int head;
	unsigned int tail;
} Queue_t;


typedef struct HeapQueue {
	struct GraphEdge_t** handle;
	int* priority;
	int heapsize;
	int heapsizelimit;
} HeapQueue_t;

typedef struct HeapQueueSet {
	struct GraphEdge_t* handle;
	int priority;
} HeapQueueSet_t;

#endif