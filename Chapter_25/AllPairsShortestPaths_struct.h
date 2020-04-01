#ifndef _STRUCT_H
#define _STRUCT_H

#include "AllPairsShortestPaths_common.h"

#define INFINITY INT_MAX
#define INFINITYMINUS INT_MIN
#define NIL 0
/* i - row number, j - column number, n - number of rows */
#define item(i, j, n) ((i - DIFFERENCE) * n + (j - DIFFERENCE))
#define GetClosureSizeInBytes(rows) (rows * rows / CHAR_BIT + (((rows * rows) % CHAR_BIT > 0) ? 1 : 0))

typedef struct Graph {
	struct AdjacencyList** adjlist;
	struct GraphVertex** vertlist;
	struct GraphEdge** edgelist;
	struct AdjacencyMatrix* adjmatrix;
	struct GraphVertex* auxVertex;
	struct AdjacencyList* auxAdjList;
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
	union {
		int rank;
		int key;
		int index;
	} u1;
	union {
		char color;
		char mark;
	} u2;
} GraphVertex_t;

typedef struct GraphEdge {
	struct GraphVertex* vertex1;			/* source vertex */
	struct GraphVertex* vertex2;			/* destination vertex */
	int weight;
} GraphEdge_t;

typedef struct AdjacencyList {
	struct GraphVertex* vertex;
	struct AdjacencyList* next;
	int weight;
} AdjacencyList_t;

typedef struct AdjacencyMatrix {
	int* weight;
	int rows;
} AdjacencyMatrix_t;

typedef struct AdjacencyAndPredecessorMatrices {
	struct AdjacencyMatrix* shortestPath;
	struct AdjacencyMatrix* predSubgraph;
	int isNegativeWeightCycle;
} AdjPredSet_t;

typedef struct TransitiveClosure {
	char* key;
	int rows;
} TClosure_t;

typedef struct HeapQueue {
	struct GraphVertex** handle;
	int* priority;
	int heapsize;
	int heapsizelimit;
} HeapQueue_t;

typedef struct HeapQueueSet {
	struct GraphVertex* handle;
	int priority;
} HeapQueueSet_t;

#endif