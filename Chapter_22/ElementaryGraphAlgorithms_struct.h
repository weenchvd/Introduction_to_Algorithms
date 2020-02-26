#ifndef _STRUCT_H
#define _STRUCT_H

#include "ElementaryGraphAlgorithms_common.h"

typedef struct Graph {
	struct AdjacencyList** adjlist;
	struct GraphVertex** vertlist;
	int vertexnum;							/* number of vertices */
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

typedef struct AdjacencyList {
	struct GraphVertex* vertex;
	struct AdjacencyList* next;
} AdjacencyList_t;

typedef struct TopologicalList {
	struct AdjacencyList* head;
} TopologicalList_t;

typedef struct Queue {
	struct GraphVertex** queue;
	unsigned int size;
	unsigned int head;
	unsigned int tail;
} Queue_t;

#endif