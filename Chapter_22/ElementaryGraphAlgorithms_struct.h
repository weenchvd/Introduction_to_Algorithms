#ifndef _STRUCT_H
#define _STRUCT_H

#include "ElementaryGraphAlgorithms_common.h"

typedef struct GraphSet {
	struct AdjacencyListSet** adjlist;
	struct GraphVertex** vertlist;
	int vertexnum;							/* number of vertices */
	char type;								/* graph type: directed or undirected */
} GraphSet_t;

typedef struct GraphVertex {
	struct GraphVertex* parent;
	int number;
	int distance;
	char color;
} GraphVertex_t;

typedef struct AdjacencyListSet {
	struct GraphVertex* vertex;
	struct AdjacencyListSet* next;
} AdjacencyListSet_t;

typedef struct QueueSet {
	struct GraphVertex** queue;
	unsigned int size;
	unsigned int head;
	unsigned int tail;
} QueueSet_t;

#endif