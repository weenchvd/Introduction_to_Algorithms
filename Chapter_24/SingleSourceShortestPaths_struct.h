#ifndef _STRUCT_H
#define _STRUCT_H

#include "SingleSourceShortestPaths_common.h"

typedef struct Graph {
	struct AdjacencyList** adjlist;
	struct GraphVertex** vertlist;
	struct GraphEdge** edgelist;
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

/*typedef struct Queue {
	struct GraphEdge** queue;
	unsigned int size;
	unsigned int head;
	unsigned int tail;
} Queue_t;*/

#endif