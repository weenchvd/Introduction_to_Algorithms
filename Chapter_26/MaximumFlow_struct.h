#ifndef _STRUCT_H
#define _STRUCT_H

#include "MaximumFlow_common.h"

#define INFINITY INT_MAX
#define INFINITYMINUS INT_MIN
#define NIL 0

/* i - row number, j - column number, n - number of rows */
#define ItemOfAdjMatrix(i, j, n) ((i - FIRSTVERTEXNUMBER) * n + (j - FIRSTVERTEXNUMBER))
#define GetClosureSizeInBytes(nRows) (nRows * nRows / CHAR_BIT + (((nRows * nRows) % CHAR_BIT > 0) ? 1 : 0))

typedef struct Graph {
	struct AdjacencyLinkedListSet** adjList;
	struct GraphVertex** vertList;
	struct GraphEdge** edgeList;
	struct AdjacencyMatrix* adjMatrix;
	struct GraphVertex* auxVertex;
	struct AdjacencyLinkedListSet* auxAdjList;
	int nVertices;							/* number of vertices */
	int nEdges;								/* number of edges */
	char graphType;							/* graph type: directed or undirected */
} Graph_t;

typedef struct GraphVertex {
	struct GraphVertex* parent;
	int number;								/* vertex number (1, 2, ..., n) */
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
	struct GraphVertex* sourceVertex;		/* source vertex */
	struct GraphVertex* destVertex;			/* destination vertex */
	union WeightCapacity {
		int weight;
		int capacity;
	} u1;
	union Flow {
		int flow;
	} u2;
} GraphEdge_t;

typedef struct AdjacencyLinkedListSet {		/* set of adjacency linked list */
	struct GraphEdge* edge;
	struct AdjacencyLinkedListSet* next;
} AdjLLSet_t;

typedef struct AdjacencyMatrix {
	int* value;
	int nRows;
} AdjacencyMatrix_t;

typedef struct Queue {
	void** queue;
	unsigned int size;
	unsigned int head;
	unsigned int tail;
} Queue_t;

#endif