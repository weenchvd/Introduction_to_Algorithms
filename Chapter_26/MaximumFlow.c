#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MaximumFlow_common.h"
#include "MaximumFlow_struct.h"
#include "MaximumFlow.h"

int CreateGraph(Graph_t* graph)
{
	int i, j, y, k, w, nRows;
	long long int n;
	GraphVertex_t* vertex;
	GraphEdge_t* edge;
	AdjLLSet_t* adjSet, * adjSet2;
	printf("  Please enter a type of the graph (%d - Directed or %d - Undirected): ", DIRECTED, UNDIRECTED);
	if (scanf("%d", &i) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (i != DIRECTED && i != UNDIRECTED) {
		printf("\n\t| ERROR | The number must be %d or %d |\n\n", DIRECTED, UNDIRECTED);
		return FAILURE;
	}
	graph->graphType = i;
	printf("  Please enter number of vertices: ");
	if (scanf("%lld", &n) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (n < 1 || n > INT_MAX) {
		printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", INT_MAX);
		return FAILURE;
	}
	graph->nVertices = n;
	if ((graph->adjList = malloc(sizeof(AdjLLSet_t*) * (graph->nVertices + FIRSTVERTEXNUMBER))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	if ((graph->vertList = malloc(sizeof(GraphVertex_t*) * (graph->nVertices + FIRSTVERTEXNUMBER))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	printf("  Please enter number of edges: ");
	if (scanf("%lld", &n) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (n < 0 || n > INT_MAX) {
		printf("\n\t| ERROR | The number must be from 0 to %d |\n\n", INT_MAX);
		return FAILURE;
	}
	graph->nEdges = n;
	if ((graph->edgeList = malloc(sizeof(GraphEdge_t*) * graph->nEdges)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	if ((graph->adjMatrix = CreateAdjacencyMatrix(graph->nVertices)) == NULL) {
		return FAILURE;
	}
	nRows = graph->adjMatrix->nRows;
	for (i = 0, j = nRows * nRows; i < j; i++) {
		graph->adjMatrix->value[i] = INFINITY;
	}
	for (i = 1; i <= nRows; i++) {
		graph->adjMatrix->value[ItemOfAdjMatrix(i, i, nRows)] = 0;
	}
	for (i = 0; i < FIRSTVERTEXNUMBER; i++) {
		graph->vertList[i] = graph->adjList[i] = NULL;
	}
	for (i = j = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		if ((vertex = CreateVertex()) == NULL) {
			j = i;
			break;
		}
		vertex->parent = NULL;
		vertex->number = i;
		vertex->distance = vertex->discovered = vertex->finished = 0;
		vertex->color = NOCOLOR;
		graph->vertList[i] = vertex;
		graph->adjList[i] = NULL;
	}
	if (j > FIRSTVERTEXNUMBER) {
		for (i = FIRSTVERTEXNUMBER; i < j; i++) {
			free(graph->vertList[i]);
		}
		return FAILURE;
	}
	for (i = 0; i < graph->nEdges; i++) {
		graph->edgeList[i] = NULL;
	}
	y = 0;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		for (j = FIRSTVERTEXNUMBER; j < graph->nVertices + FIRSTVERTEXNUMBER - 1; j++) {
			printf("  For vertex #%d, enter the number of the next vertex between which there is an edge. "
				"Enter 0 to go to the next vertex: ", i);
			if (scanf("%d", &n) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				j--;
				continue;
			}
			if (n < 0 || n > graph->nVertices) {
				printf("\n\t| ERROR | The number must from %d to %d |\n\n", 0, graph->nVertices);
				j--;
				continue;
			}
			k = n;
			if (k == 0) {
				break;
			}
			else {
				if (y < graph->nEdges) {
					printf("  For the edge between the vertices #%d - #%d, enter the weight (capacity): ", i, k);
					if (scanf("%d", &n) <= 0) {
						printf("\n\t| ERROR | Incorrect input |\n\n");
						j--;
						continue;
					}
					if (n < INT_MIN || n > INT_MAX) {
						printf("\n\t| ERROR | The weight (capacity) must from %d to %d |\n\n", INT_MIN, INT_MAX);
						j--;
						continue;
					}
					w = n;
					if (IsVertexInAdjacencyList(graph->adjList[i], graph->vertList[k]) == false) {
						if ((adjSet = CreateAdjacencyLLSet()) == NULL) {
							j--;
							continue;
						}
						if ((edge = CreateEdge()) == NULL) {
							j--;
							free(adjSet);
							continue;
						}
						edge->sourceVertex = graph->vertList[i];
						edge->destVertex = graph->vertList[k];
						edge->weight = w;
						adjSet->edge = edge;
						adjSet->next = graph->adjList[i];
						graph->adjList[i] = adjSet;
						graph->edgeList[y++] = edge;
						graph->adjMatrix->value[ItemOfAdjMatrix(edge->sourceVertex->number, edge->destVertex->number, nRows)] = w;
					}
					else {
						printf("\n\t| ERROR | The vertex is already in the list |\n\n");
						j--;
						continue;
					}
				}
				else {
					printf("\n\t| ERROR | The number of the edges exceeds the specified number |\n\n");
				}
			}
		}
	}
	if (graph->graphType == UNDIRECTED) {
		for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
			adjSet = graph->adjList[i];
			while (adjSet != NULL) {
				k = adjSet->edge->destVertex->number;
				if (IsVertexInAdjacencyList(graph->adjList[k], graph->vertList[i]) == false) {
					if ((adjSet2 = CreateAdjacencyLLSet()) == NULL) {
						continue;
					}
					adjSet2->edge = adjSet->edge;
					adjSet2->next = graph->adjList[k];
					graph->adjList[k] = adjSet2;
					graph->adjMatrix->value[ItemOfAdjMatrix(k, i, nRows)] = adjSet2->edge->weight;
				}
				adjSet = adjSet->next;
			}
		}
	}
	return SUCCESS;
}

GraphVertex_t* CreateVertex()
{
	GraphVertex_t* vertex;
	if ((vertex = malloc(sizeof(GraphVertex_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	return vertex;
}

GraphEdge_t* CreateEdge()
{
	GraphEdge_t* edge;
	if ((edge = malloc(sizeof(GraphEdge_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	return edge;
}

AdjLLSet_t* CreateAdjacencyLLSet()
{
	AdjLLSet_t* adjSet;
	if ((adjSet = malloc(sizeof(AdjLLSet_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	return adjSet;
}

int IsVertexInAdjacencyList(AdjLLSet_t* adjSet, GraphVertex_t* vertex)
{
	while (adjSet != NULL) {
		if (adjSet->edge->destVertex == vertex) {
			return true;
		}
		adjSet = adjSet->next;
	}
	return false;
}

AdjacencyMatrix_t* CreateAdjacencyMatrix(const int nRows)
{
	AdjacencyMatrix_t* adjMatrix;
	if ((adjMatrix = malloc(sizeof(AdjacencyMatrix_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	if ((adjMatrix->value = malloc(sizeof(int) * nRows * nRows)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		free(adjMatrix);
		return NULL;
	}
	adjMatrix->nRows = nRows;
	return adjMatrix;
}

AdjacencyMatrix_t* MakeCopyAdjacencyMatrix(const AdjacencyMatrix_t* source)
{
	int i, n;
	AdjacencyMatrix_t* destination;
	n = source->nRows;
	if ((destination = CreateAdjacencyMatrix(n)) == NULL) {
		return NULL;
	}
	for (i = 0; i < n * n; i++) {
		destination->value[i] = source->value[i];
	}
	return destination;
}

void FreeAdjacencyMatrix(AdjacencyMatrix_t* adjMatrix)
{
	free(adjMatrix->value);
	free(adjMatrix);
	return;
}

void PrintGraph(Graph_t* graph)
{
	int i;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		PrintVertex(graph->vertList[i]);
		PrintAdjacencyList(graph->adjList[i]);
		putchar('\n');
	}
	return;
}

void PrintVertex(GraphVertex_t* vertex)
{
	char color[10];
	if (vertex != NULL) {
		switch (vertex->color) {
		case NOCOLOR:
			strcpy(color, "NOCOLOR");
			break;
		case WHITE:
			strcpy(color, "WHITE");
			break;
		case GRAY:
			strcpy(color, "GRAY");
			break;
		case BLACK:
			strcpy(color, "BLACK");
			break;
		default:
			strcpy(color, "ERROR");
			break;
		}
		printf("  Addr: %p  Num: %4d  Dist: %10d  Disc: %4d  Fin: %4d  Color: %-9s  Par: %p",
			vertex, vertex->number, vertex->distance, vertex->discovered, vertex->finished, color, vertex->parent);
	}
	return;
}

void PrintAdjacencyList(AdjLLSet_t* adjSet)
{
	if (adjSet != NULL) {
		printf("  AdjList:");
		while (adjSet != NULL) {
			printf(" %d(%d),", adjSet->edge->destVertex->number, adjSet->edge->weight);
			adjSet = adjSet->next;
		}
		printf("\b ");
	}
	return;
}

int EdmondsKarp(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination)
{
	int i, flow, residualCapacity;
	Graph_t* residualGraph;
	/* the source vertex of the edge on the shortest path from the 'source' to the 'destination' of the residual graph */
	GraphVertex_t* sourceVertexResidual;
	/* the destination vertex of the edge on the shortest path from the 'source' to the 'destination' of the residual graph */
	GraphVertex_t* destVertexResidual;
	GraphEdge_t* edge, * edgeResidual, * reverseEdgeResidual;
	AdjLLSet_t* adjSet, * adjSetResidual, * prevAdjSetResidual, * adjSetResidual2, * prevAdjSetResidual2;
	for (i = 0; i < graph->nEdges; i++) {
		graph->edgeList[i]->flow = 0;
	}
	if ((residualGraph = MakeResidualGraph(graph)) == NULL) {
		return FAILURE;
	}
	flow = 0;
	while (true) {
		BreadthFirstSearch(residualGraph, source);
		if (destination->parent == NULL) {
			break;
		}
		residualCapacity = INT_MAX;
		destVertexResidual = destination;
		/* go through every edge of the shortest path to determine the 'residualCapacity' */
		do {
			sourceVertexResidual = destVertexResidual->parent;
			edge = NULL;
			/* determine if the edge from 'sourceVertexResidual' to 'destVertexResidual' belongs the source graph 'graph' */
			adjSet = graph->adjList[sourceVertexResidual->number];
			while (adjSet != NULL) {
				if (adjSet->edge->destVertex == destVertexResidual) {
					edge = adjSet->edge;
					break;
				}
				adjSet = adjSet->next;
			}
			if (edge != NULL) {
				if (edge->capacity - edge->flow < residualCapacity) {
					residualCapacity = edge->capacity - edge->flow;
				}
			}
			else {
				/* determine if the edge from 'destVertexResidual' to 'sourceVertexResidual' belongs the source graph 'graph' */
				adjSet = graph->adjList[destVertexResidual->number];
				while (adjSet != NULL) {
					if (adjSet->edge->destVertex == sourceVertexResidual) {
						edge = adjSet->edge;
						break;
					}
					adjSet = adjSet->next;
				}
				if (edge != NULL) {
					if (edge->flow < residualCapacity) {
						residualCapacity = edge->flow;
					}
				}
			}
			destVertexResidual = sourceVertexResidual;
		} while (sourceVertexResidual != source);
		destVertexResidual = destination;
		/* go through every edge of the shortest path to increase the flow in the 'graph' and modify the 'residualGraph' */
		do {
			sourceVertexResidual = destVertexResidual->parent;
			edge = NULL;
			/* determine if the edge from 'sourceVertexResidual' to 'destVertexResidual' belongs the source graph 'graph' */
			adjSet = graph->adjList[sourceVertexResidual->number];
			while (adjSet != NULL) {
				if (adjSet->edge->destVertex == destVertexResidual) {
					edge = adjSet->edge;
					break;
				}
				adjSet = adjSet->next;
			}
			if (edge != NULL) {
				edge->flow += residualCapacity;
			}
			else {
				/* determine if the edge from 'destVertexResidual' to 'sourceVertexResidual' belongs the source graph 'graph' */
				adjSet = graph->adjList[destVertexResidual->number];
				while (adjSet != NULL) {
					if (adjSet->edge->destVertex == sourceVertexResidual) {
						edge = adjSet->edge;
						break;
					}
					adjSet = adjSet->next;
				}
				if (edge != NULL) {
					edge->flow -= residualCapacity;
				}
			}
			/* find the edge from 'sourceVertexResidual' to 'destVertexResidual' of the residual graph 'residualGraph' */
			adjSetResidual = residualGraph->adjList[sourceVertexResidual->number];
			prevAdjSetResidual = NULL;
			edgeResidual = NULL;
			while (adjSetResidual != NULL) {
				if (adjSetResidual->edge->destVertex == destVertexResidual) {
					edgeResidual = adjSetResidual->edge;
					break;
				}
				prevAdjSetResidual = adjSetResidual;
				adjSetResidual = adjSetResidual->next;
			}
			/* find the edge from 'destVertexResidual' to 'sourceVertexResidual' of the residual graph 'residualGraph' */
			adjSetResidual2 = residualGraph->adjList[destVertexResidual->number];
			prevAdjSetResidual2 = NULL;
			reverseEdgeResidual = NULL;
			while (adjSetResidual2 != NULL) {
				if (adjSetResidual2->edge->destVertex == sourceVertexResidual) {
					reverseEdgeResidual = adjSetResidual2->edge;
					break;
				}
				prevAdjSetResidual2 = adjSetResidual2;
				adjSetResidual2 = adjSetResidual2->next;
			}
			/* modify the residual graph 'residualGraph' */
			edgeResidual->capacity -= residualCapacity;
			/* if the edge capacity of 'residualEdge' is 0, remove the edge */
			if (edgeResidual->capacity == 0) {
				if (prevAdjSetResidual != NULL) {
					prevAdjSetResidual->next = adjSetResidual->next;
				}
				else {
					residualGraph->adjList[sourceVertexResidual->number] = adjSetResidual->next;
				}
				free(edgeResidual);
				free(adjSetResidual);
			}
			/* if the edge 'reverseEdgeResidual' does not exist, create an edge and insert it into the adjacency list */
			if (reverseEdgeResidual == NULL) {
				if ((adjSetResidual2 = CreateAdjacencyLLSet()) == NULL) {
					continue;
				}
				if ((reverseEdgeResidual = CreateEdge()) == NULL) {
					free(adjSet);
					continue;
				}
				reverseEdgeResidual->sourceVertex = destVertexResidual;
				reverseEdgeResidual->destVertex = sourceVertexResidual;
				reverseEdgeResidual->capacity = residualCapacity;
				reverseEdgeResidual->flow = 0;
				adjSetResidual2->edge = reverseEdgeResidual;
				adjSetResidual2->next = residualGraph->adjList[destVertexResidual->number];
				residualGraph->adjList[destVertexResidual->number] = adjSetResidual2;
			}
			destVertexResidual = sourceVertexResidual;
		} while (sourceVertexResidual != source);
		flow += residualCapacity;
	}
	FreeResidualGraph(residualGraph);
	return flow;
}

Graph_t* MakeResidualGraph(Graph_t* sourceGraph)
{
	int i;
	Graph_t* residualGraph;
	AdjLLSet_t* adjSet, * adjSetResidual;
	GraphEdge_t* edgeResidual;
	if ((residualGraph = malloc(sizeof(Graph_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	if ((residualGraph->adjList = malloc(sizeof(AdjLLSet_t*) * (sourceGraph->nVertices + FIRSTVERTEXNUMBER))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	residualGraph->vertList = sourceGraph->vertList;
	residualGraph->edgeList = residualGraph->adjMatrix = residualGraph->auxVertex = residualGraph->auxAdjList = NULL;
	residualGraph->nVertices = sourceGraph->nVertices;
	residualGraph->nEdges = 0;
	residualGraph->graphType = sourceGraph->graphType;
	for (i = FIRSTVERTEXNUMBER; i < residualGraph->nVertices + FIRSTVERTEXNUMBER; i++) {
		residualGraph->adjList[i] = NULL;
		adjSet = sourceGraph->adjList[i];
		while (adjSet != NULL) {
			if ((adjSetResidual = CreateAdjacencyLLSet()) == NULL) {
				continue;
			}
			if ((edgeResidual = CreateEdge()) == NULL) {
				free(adjSet);
				continue;
			}
			edgeResidual->sourceVertex = adjSet->edge->sourceVertex;
			edgeResidual->destVertex = adjSet->edge->destVertex;
			edgeResidual->capacity = adjSet->edge->capacity;
			edgeResidual->flow = adjSet->edge->flow;
			adjSetResidual->edge = edgeResidual;
			adjSetResidual->next = residualGraph->adjList[i];
			residualGraph->adjList[i] = adjSetResidual;
			adjSet = adjSet->next;
		}
	}
	return residualGraph;
}

void FreeResidualGraph(Graph_t* residualGraph)
{
	int i;
	AdjLLSet_t* adjSet, * nextAdjSet;
	for (i = FIRSTVERTEXNUMBER; i < residualGraph->nVertices + FIRSTVERTEXNUMBER; i++) {
		adjSet = residualGraph->adjList[i];
		while (adjSet != NULL) {
			nextAdjSet = adjSet->next;
			free(adjSet->edge);
			free(adjSet);
			adjSet = nextAdjSet;
		}
	}
	return;
}

void BreadthFirstSearch(Graph_t* graph, GraphVertex_t* sourceVertex)
{
	int i;
	Queue_t q;
	GraphVertex_t* currentVertex, * descendantVertex;
	AdjLLSet_t* adjSet;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		graph->vertList[i]->color = WHITE;
		graph->vertList[i]->distance = INT_MAX;
		graph->vertList[i]->parent = NULL;
	}
	sourceVertex->color = BLACK;
	sourceVertex->distance = 0;
	sourceVertex->parent = NULL;
	q.size = graph->nVertices;
	if ((q.queue = malloc(sizeof(void*) * q.size)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return;
	}
	q.head = q.tail = 0;
	Enqueue(&q, sourceVertex);
	while (IsQueueEmpty(&q) != true) {
		currentVertex = Dequeue(&q);
		adjSet = graph->adjList[currentVertex->number];
		while (adjSet != NULL) {
			descendantVertex = adjSet->edge->destVertex;
			if (descendantVertex->color == WHITE) {
				descendantVertex->color = BLACK;
				descendantVertex->distance = currentVertex->distance + 1;
				descendantVertex->parent = currentVertex;
				Enqueue(&q, descendantVertex);
			}
			adjSet = adjSet->next;
		}
	}
	free(q.queue);
	return;
}

void Enqueue(Queue_t* q, void* x)
{
	if (IsQueueFull(q) == true) {
		printf("\n\t| ERROR | Queue overflow |\n\n");
	}
	else {
		q->queue[q->tail] = x;
		q->tail = (q->tail == q->size - 1) ? ARRAYSTARTINDEX : q->tail + 1;
	}
	return;
}

void* Dequeue(Queue_t* q)
{
	void* x;
	if (IsQueueEmpty(q) == true) {
		printf("\n\t| ERROR | Queue underflow |\n\n");
		return NULL;
	}
	x = q->queue[q->head];
	q->head = (q->head == q->size - 1) ? ARRAYSTARTINDEX : q->head + 1;
	return x;
}

inline int IsQueueEmpty(Queue_t* q)
{
	return (q->head == q->tail) ? true : false;
}

inline int IsQueueFull(Queue_t* q)
{
	return (q->head == ((q->tail + 1 == q->size) ? ARRAYSTARTINDEX : q->tail + 1)) ? true : false;
}

int GenericPushRelabel(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination)
{
	int proceed;
	InitializePreflow(graph, source);
	proceed = true;
	while (proceed == true) {
		proceed = false;
		PushAll(graph, &proceed);
		RelabelAll(graph, destination, &proceed);
	}
	source->excess = ~source->excess + 1;
	return source->excess;
}

void InitializePreflow(Graph_t* graph, GraphVertex_t* source)
{
	int i;
	AdjLLSet_t* adjSet;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		graph->vertList[i]->excess = 0;
		graph->vertList[i]->height = 0;
	}
	for (i = 0; i < graph->nEdges; i++) {
		graph->edgeList[i]->flow = 0;
	}
	source->height = graph->nVertices;
	adjSet = graph->adjList[source->number];
	while (adjSet != NULL) {
		adjSet->edge->flow = adjSet->edge->capacity;
		adjSet->edge->destVertex->excess = adjSet->edge->capacity;
		source->excess -= adjSet->edge->capacity;
		adjSet = adjSet->next;
	}
	return;
}

void PushAll(Graph_t* graph, int* condition)
{
	int i, residualCapacity;
	GraphEdge_t* edge;
	AdjLLSet_t* adjSet;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		adjSet = graph->adjList[i];
		while (adjSet != NULL) {
			edge = adjSet->edge;
			/* original edge */
			residualCapacity = edge->capacity - edge->flow;
			if (edge->sourceVertex->excess > 0 && residualCapacity > 0 && edge->sourceVertex->height == edge->destVertex->height + 1) {
				PushFlowAlongOriginalEdge(edge, residualCapacity);
				*condition = true;
			}
			/* residual edge */
			residualCapacity = edge->flow;
			if (edge->destVertex->excess > 0 && residualCapacity > 0 && edge->destVertex->height == edge->sourceVertex->height + 1) {
				PushFlowAlongResidualEdge(edge, residualCapacity);
				*condition = true;
			}
			adjSet = adjSet->next;
		}
	}
	return;
}

void PushFlowAlongOriginalEdge(GraphEdge_t* originalEdge, int residualCapacity)
{
	int flow;
	flow = min(originalEdge->sourceVertex->excess, residualCapacity);
	originalEdge->flow += flow;
	originalEdge->sourceVertex->excess -= flow;
	originalEdge->destVertex->excess += flow;
	return;
}

void PushFlowAlongResidualEdge(GraphEdge_t* originalEdge, int residualCapacity)
{
	int flow;
	flow = min(originalEdge->destVertex->excess, residualCapacity);
	originalEdge->flow -= flow;
	originalEdge->destVertex->excess -= flow;
	originalEdge->sourceVertex->excess += flow;
	return;
}

void RelabelAll(Graph_t* graph, GraphVertex_t* destination, int* condition)
{
	char relabel;
	int i, j, minHeight, residualCapacity;
	GraphVertex_t* vertex, *adjacentVertex;
	GraphEdge_t* edge;
	AdjLLSet_t* adjSet;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		vertex = graph->vertList[i];
		if (vertex == destination || vertex->excess <= 0) {
			continue;
		}
		relabel = true;
		minHeight = INT_MAX;
		adjSet = graph->adjList[i];
		while (adjSet != NULL) {
			edge = adjSet->edge;
			/* original edge */
			residualCapacity = edge->capacity - edge->flow;
			if (residualCapacity > 0) {
				if (vertex->height <= edge->destVertex->height) {
					if (edge->destVertex->height < minHeight) {
						minHeight = edge->destVertex->height;
					}
				}
				else {
					relabel = false;
					break;
				}
			}
			adjSet = adjSet->next;
		}
		if (relabel == false) {
			continue;
		}
		for (j = FIRSTVERTEXNUMBER; j < graph->nVertices + FIRSTVERTEXNUMBER; j++) {
			adjSet = graph->adjList[j];
			while (adjSet != NULL) {
				if (adjSet->edge->destVertex == vertex) {
					edge = adjSet->edge;
					/* residual edge */
					residualCapacity = edge->flow;
					if (residualCapacity > 0) {
						if (vertex->height <= edge->sourceVertex->height) {
							if (edge->sourceVertex->height < minHeight) {
								minHeight = edge->sourceVertex->height;
							}
						}
						else {
							relabel = false;
							j = graph->nVertices + FIRSTVERTEXNUMBER;
						}
					}
					break;
				}
				adjSet = adjSet->next;
			}
		}
		if (relabel == true) {
			RelabelVertex(vertex, minHeight);
			*condition = true;
		}
	}
	return;
}

void RelabelVertex(GraphVertex_t* vertex, int minHeight)
{
	vertex->height = minHeight + 1;
	return;
}

int RelabelToFront(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination)
{
	int i, oldHeight;
	GraphVertex_t* vertex;
	SinglyLLSetPtr_t** neighborList, * vertexList, *currentVertexSet;
	if ((neighborList = CreateNeighborList(graph)) == NULL) {
		return FAILURE;
	}
	InitializePreflow(graph, source);
	if ((vertexList = CreateVertexList(graph, source, destination)) == NULL) {
		return FAILURE;
	}
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		graph->vertList[i]->currentNeighborSet = neighborList[i];
	}
	currentVertexSet = vertexList;
	while (currentVertexSet != NULL) {
		vertex = currentVertexSet->ptr;
		oldHeight = vertex->height;
		Discharge(vertex, neighborList);
		if (vertex->height > oldHeight) {
			SinglyLinkedListExtractSet(&vertexList, currentVertexSet);
			SinglyLinkedListInsertSet(&vertexList, currentVertexSet);
		}
		currentVertexSet = currentVertexSet->next;
	}
	FreeNeighborList(graph, neighborList);
	FreeVertexList(vertexList);
	source->excess = ~source->excess + 1;
	return source->excess;
}

void Discharge(GraphVertex_t* vertex, SinglyLLSetPtr_t** neighborList)
{
	int residualCapacity, minHeight;
	GraphVertex_t* neighborVertex;
	GraphEdge_t* edge;
	SinglyLLSetPtr_t* currentNeighborSet;
	while (vertex->excess > 0) {
		if (vertex->currentNeighborSet == NULL) {
			vertex->currentNeighborSet = currentNeighborSet = neighborList[vertex->number];
			minHeight = INT_MAX;
			while (currentNeighborSet != NULL) {
				edge = currentNeighborSet->ptr;
				if (vertex == edge->sourceVertex) {
					neighborVertex = edge->destVertex;
					residualCapacity = edge->capacity - edge->flow;
				}
				else {
					neighborVertex = edge->sourceVertex;
					residualCapacity = edge->flow;
				}
				if (residualCapacity > 0 && vertex->height <= neighborVertex->height) {
					if (neighborVertex->height < minHeight) {
						minHeight = neighborVertex->height;
					}
				}
				currentNeighborSet = currentNeighborSet->next;
			}
			RelabelVertex(vertex, minHeight);
		}
		else {
			edge = vertex->currentNeighborSet->ptr;
			if (vertex == edge->sourceVertex) {
				neighborVertex = edge->destVertex;
				residualCapacity = edge->capacity - edge->flow;
			}
			else {
				neighborVertex = edge->sourceVertex;
				residualCapacity = edge->flow;
			}
			if (residualCapacity > 0 && vertex->height == neighborVertex->height + 1) {
				if (vertex == edge->sourceVertex) {
					PushFlowAlongOriginalEdge(edge, residualCapacity);
				}
				else {
					PushFlowAlongResidualEdge(edge, residualCapacity);
				}
			}
			else {
				vertex->currentNeighborSet = vertex->currentNeighborSet->next;
			}
		}
	}
	return;
}

int PushRelabelFIFOQueue(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination)
{
	int i;
	Queue_t q;
	GraphVertex_t* vertex;
	SinglyLLSetPtr_t** neighborList;
	AdjLLSet_t* adjSet;
	q.size = graph->nVertices + 1;
	if ((q.queue = malloc(sizeof(void*) * q.size)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	q.head = q.tail = 0;
	if ((neighborList = CreateNeighborList(graph)) == NULL) {
		return FAILURE;
	}
	InitializePreflow(graph, source);
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		graph->vertList[i]->currentNeighborSet = neighborList[i];
		graph->vertList[i]->mark = false;
	}
	/* Source and Sink are not actually in the queue */
	source->mark = true;
	destination->mark = true;
	adjSet = graph->adjList[source->number];
	while (adjSet != NULL) {
		/* Source and Sink marks are 'true', hence they will never be queued */
		if (adjSet->edge->destVertex->mark == false) {
			Enqueue(&q, adjSet->edge->destVertex);
			adjSet->edge->destVertex->mark = true;
		}
		adjSet = adjSet->next;
	}
	while (IsQueueEmpty(&q) != true) {
		vertex = Dequeue(&q);
		vertex->mark = false;
		DischargeFIFOQueue(vertex, neighborList, &q);
	}
	FreeNeighborList(graph, neighborList);
	free(q.queue);
	source->excess = ~source->excess + 1;
	return source->excess;
}

void DischargeFIFOQueue(GraphVertex_t* vertex, SinglyLLSetPtr_t** neighborList, Queue_t* q)
{
	int residualCapacity, minHeight;
	GraphVertex_t* neighborVertex;
	GraphEdge_t* edge;
	SinglyLLSetPtr_t* currentNeighborSet;
	while (vertex->excess > 0) {
		if (vertex->currentNeighborSet == NULL) {
			vertex->currentNeighborSet = currentNeighborSet = neighborList[vertex->number];
			minHeight = INT_MAX;
			while (currentNeighborSet != NULL) {
				edge = currentNeighborSet->ptr;
				if (vertex == edge->sourceVertex) {
					neighborVertex = edge->destVertex;
					residualCapacity = edge->capacity - edge->flow;
				}
				else {
					neighborVertex = edge->sourceVertex;
					residualCapacity = edge->flow;
				}
				if (residualCapacity > 0 && vertex->height <= neighborVertex->height) {
					if (neighborVertex->height < minHeight) {
						minHeight = neighborVertex->height;
					}
				}
				currentNeighborSet = currentNeighborSet->next;
			}
			RelabelVertex(vertex, minHeight);
		}
		else {
			edge = vertex->currentNeighborSet->ptr;
			if (vertex == edge->sourceVertex) {
				neighborVertex = edge->destVertex;
				residualCapacity = edge->capacity - edge->flow;
			}
			else {
				neighborVertex = edge->sourceVertex;
				residualCapacity = edge->flow;
			}
			if (residualCapacity > 0 && vertex->height == neighborVertex->height + 1) {
				if (vertex == edge->sourceVertex) {
					PushFlowAlongOriginalEdge(edge, residualCapacity);
					/* Source and Sink marks are 'true', hence they will never be queued */
					if (edge->destVertex->mark == false) {
						Enqueue(q, edge->destVertex);
						edge->destVertex->mark = true;
					}
				}
				else {
					PushFlowAlongResidualEdge(edge, residualCapacity);
					/* Source and Sink marks are 'true', hence they will never be queued */
					if (edge->sourceVertex->mark == false) {
						Enqueue(q, edge->sourceVertex);
						edge->sourceVertex->mark = true;
					}
				}
			}
			else {
				vertex->currentNeighborSet = vertex->currentNeighborSet->next;
			}
		}
	}
	return;
}

SinglyLLSetPtr_t** CreateNeighborList(Graph_t* graph)
{
	int i;
	GraphEdge_t* edge;
	AdjLLSet_t* adjSet;
	SinglyLLSetPtr_t** neighborList, * neighborSet;
	if ((neighborList = malloc(sizeof(SinglyLLSetPtr_t*) * (graph->nVertices + FIRSTVERTEXNUMBER))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		neighborList[i] = NULL;
	}
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		adjSet = graph->adjList[i];
		while (adjSet != NULL) {
			edge = adjSet->edge;
			if ((neighborSet = SinglyLinkedListCreateSet()) == NULL) {
				return NULL;
			}
			neighborSet->ptr = edge;
			SinglyLinkedListInsertSet(&neighborList[i], neighborSet);
			if ((neighborSet = SinglyLinkedListCreateSet()) == NULL) {
				return NULL;
			}
			neighborSet->ptr = edge;
			SinglyLinkedListInsertSet(&neighborList[edge->destVertex->number], neighborSet);
			adjSet = adjSet->next;
		}
	}
	return neighborList;
}

void FreeNeighborList(Graph_t* graph, SinglyLLSetPtr_t** neighborList)
{
	int i;
	SinglyLLSetPtr_t* neighborSet, *neighborSetNext;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		neighborSet = neighborList[i];
		while (neighborSet != NULL) {
			neighborSetNext = neighborSet->next;
			free(neighborSet);
			neighborSet = neighborSetNext;
		}
	}
	free(neighborList);
	return;
}

SinglyLLSetPtr_t* CreateVertexList(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination)
{
	int i;
	GraphVertex_t* vertex;
	SinglyLLSetPtr_t* vertexSet, * vertexList;
	vertexList = NULL;
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		vertex = graph->vertList[i];
		if (vertex == source || vertex == destination) {
			continue;
		}
		if ((vertexSet = SinglyLinkedListCreateSet()) == NULL) {
			return NULL;
		}
		vertexSet->ptr = vertex;
		SinglyLinkedListInsertSet(&vertexList, vertexSet);
	}
	return vertexList;
}

void FreeVertexList(SinglyLLSetPtr_t* vertexList)
{
	SinglyLLSetPtr_t* vertexSet, * vertexSetNext;
	vertexSet = vertexList;
	while (vertexSet != NULL) {
		vertexSetNext = vertexSet->next;
		free(vertexSet);
		vertexSet = vertexSetNext;
	}
	return;
}

SinglyLLSetPtr_t* SinglyLinkedListCreateSet()
{
	SinglyLLSetPtr_t* set;
	if ((set = malloc(sizeof(SinglyLLSetPtr_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	return set;
}

SinglyLLSetPtr_t* SinglyLinkedListSearchSet(SinglyLLSetPtr_t** head, void* ptr)
{
	SinglyLLSetPtr_t* set;
	set = *head;
	while (set != NULL && set->ptr != ptr) {
		set = set->next;
	}
	return set;
}

SinglyLLSetPtr_t** SinglyLinkedListGetPointerToNextPointerOfPreviousSet(SinglyLLSetPtr_t** head, SinglyLLSetPtr_t* set)
{
	SinglyLLSetPtr_t* current, ** prevNextPtr;
	prevNextPtr = head;
	current = *head;
	while (current != set) {
		prevNextPtr = &current->next;
		current = current->next;
	}
	return prevNextPtr;
}

void SinglyLinkedListInsertSet(SinglyLLSetPtr_t** head, SinglyLLSetPtr_t* set)
{
	set->next = *head;
	*head = set;
	return;
}

void SinglyLinkedListExtractSet(SinglyLLSetPtr_t** head, SinglyLLSetPtr_t* set)
{
	SinglyLLSetPtr_t** prevNextPtr;
	prevNextPtr = SinglyLinkedListGetPointerToNextPointerOfPreviousSet(head, set);
	*prevNextPtr = set->next;
	return;
}
