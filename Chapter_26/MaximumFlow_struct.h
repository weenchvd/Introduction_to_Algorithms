#ifndef _STRUCT_H
#define _STRUCT_H

#include "MaximumFlow_common.h"

#define INFINITY INT_MAX
#define INFINITYMINUS INT_MIN
#define NIL 0

/* i - row number, j - column number, n - number of rows */
#define ItemOfAdjMatrix(i, j, n) ((i - FIRSTVERTEXNUMBER) * n + (j - FIRSTVERTEXNUMBER))

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
	union {
		struct GraphVertex* parent;
		struct SinglyLinkedListSetPtr* currentNeighborSet;
	};
	int number;								/* vertex number (1, 2, ..., n) */
	union {
		int distance;
		int height;
	};
	int discovered;
	int finished;
	union {
		int rank;
		int key;
		int index;
		int excess;
	};
	union {
		char color;
		char mark;
	};
} GraphVertex_t;

typedef struct GraphEdge {
	struct GraphVertex* sourceVertex;		/* source vertex */
	struct GraphVertex* destVertex;			/* destination vertex */
	union {
		int weight;
		int capacity;
	};
	union {
		int flow;
	};
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

typedef struct SinglyLinkedListSetPtr {
	void* ptr;
	struct SinglyLinkedListSetPtr* next;
}SinglyLLSetPtr_t;

#endif