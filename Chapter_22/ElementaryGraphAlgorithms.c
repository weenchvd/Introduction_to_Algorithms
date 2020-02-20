﻿#include "ElementaryGraphAlgorithms.h"

int CreateGraph(GraphSet_t* graph)
{
	int i, j, k;
	GraphVertex_t* vertex;
	AdjacencyListSet_t* adjset, * adjset2;
	printf("Please enter a type of the graph (%d - Directed or %d - Undirected): ", DIRECTED, UNDIRECTED);
	if (scanf("%d", &i) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (i != DIRECTED && i != UNDIRECTED) {
		printf("\n\t| ERROR | The number must be %d or %d |\n\n", DIRECTED, UNDIRECTED);
		return FAILURE;
	}
	graph->type = i;
	printf("Please enter number of vertices: ");
	if (scanf("%d", &graph->vertexnum) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (graph->vertexnum < 1 || graph->vertexnum > INT_MAX) {
		printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", INT_MAX);
		return FAILURE;
	}
	if ((graph->adjlist = malloc(sizeof(AdjacencyListSet_t*) * graph->vertexnum)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	if ((graph->vertlist = malloc(sizeof(GraphVertex_t*) * graph->vertexnum)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	for (i = j = 0; i < graph->vertexnum; i++) {
		if ((vertex = malloc(sizeof(GraphVertex_t))) == NULL) {
			printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
			j = i;
			break;
		}
		vertex->parent = NULL;
		vertex->number = i + DIFFERENCE;
		vertex->distance = 0;
		vertex->color = NOCOLOR;
		graph->vertlist[i] = vertex;
		graph->adjlist[i] = NULL;
	}
	if (j > 0) {
		for (i = 0; i < j; i++) {
			free(graph->vertlist[i]);
		}
		return FAILURE;
	}
	for (i = 0; i < graph->vertexnum; i++) {
		for (j = 1; j < graph->vertexnum; j++) {
			printf("For vertex #%d, enter the number of the next vertex between which there is a edge. "
				"Enter 0 to go to the next vertex: ", i + DIFFERENCE);
			if (scanf("%d", &k) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				j--;
				continue;
			}
			if (k < 0 || k > graph->vertexnum) {
				printf("\n\t| ERROR | The number must from %d to %d |\n\n", 0, graph->vertexnum);
				j--;
				continue;
			}
			if (k == 0) {
				break;
			}
			else {
				if ((adjset = malloc(sizeof(AdjacencyListSet_t))) == NULL) {
					printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
					j--;
					continue;
				}
				adjset->vertex = graph->vertlist[k - DIFFERENCE];
				if (IsVertexInAdjacencyList(graph->adjlist[i], adjset->vertex) == FALSE) {
					adjset->next = graph->adjlist[i];
					graph->adjlist[i] = adjset;
				}
				else {
					free(adjset);
					printf("\n\t| ERROR | The vertex is already in the list |\n\n");
					j--;
					continue;
				}
			}
		}
	}
	if (graph->type == UNDIRECTED) {
		for (i = 0; i < graph->vertexnum; i++) {
			adjset = graph->adjlist[i];
			while (adjset != NULL) {
				k = adjset->vertex->number - DIFFERENCE;
				if (IsVertexInAdjacencyList(graph->adjlist[k], graph->vertlist[i]) == FALSE) {
					if ((adjset2 = malloc(sizeof(AdjacencyListSet_t))) == NULL) {
						printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
						continue;
					}
					adjset2->vertex = graph->vertlist[i];
					adjset2->next = graph->adjlist[k];
					graph->adjlist[k] = adjset2;
				}
				adjset = adjset->next;
			}
		}
	}
	return SUCCESS;
}

int IsVertexInAdjacencyList(AdjacencyListSet_t* adjset, GraphVertex_t* vertex)
{
	while (adjset != NULL) {
		if (adjset->vertex == vertex) {
			return TRUE;
		}
		adjset = adjset->next;
	}
	return FALSE;
}

void BreadthFirstSearch(GraphSet_t* graph, GraphVertex_t* vertex)
{
	int i;
	QueueSet_t q;
	GraphVertex_t* current, * descendant;
	AdjacencyListSet_t* adjset;
	for (i = 0; i < graph->vertexnum; i++) {
		if (graph->vertlist[i] != vertex) {
			graph->vertlist[i]->color = WHITE;
			graph->vertlist[i]->distance = INT_MAX;
			graph->vertlist[i]->parent = NULL;
		}
	}
	vertex->color = GRAY;
	vertex->distance = 0;
	vertex->parent = NULL;
	q.size = graph->vertexnum;
	if ((q.queue = malloc(sizeof(GraphVertex_t*) * q.size)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return;
	}
	q.head = q.tail = 0;
	Enqueue(&q, vertex);
	while (IsQueueEmpty(&q) != TRUE) {
		current = Dequeue(&q);
		adjset = graph->adjlist[current->number - DIFFERENCE];
		while (adjset != NULL) {
			descendant = adjset->vertex;
			if (descendant->color == WHITE) {
				descendant->color = GRAY;
				descendant->distance = current->distance + 1;
				descendant->parent = current;
				Enqueue(&q, descendant);
			}
			adjset = adjset->next;
		}
		current->color = BLACK;
	}
	free(q.queue);
	return;
}

void Enqueue(QueueSet_t* q, GraphVertex_t* x)
{
	if (IsQueueFull(q) == TRUE) {
		printf("\n\t| ERROR | Queue overflow |\n\n");
	}
	else {
		q->queue[q->tail] = x;
		q->tail = (q->tail == q->size - 1) ? ARRAYSTARTINDEX : q->tail + 1;
	}
	return;
}

GraphVertex_t* Dequeue(QueueSet_t* q)
{
	GraphVertex_t* x;
	if (IsQueueEmpty(q) == TRUE) {
		printf("\n\t| ERROR | Queue underflow |\n\n");
		return NULL;
	}
	x = q->queue[q->head];
	q->head = (q->head == q->size - 1) ? ARRAYSTARTINDEX : q->head + 1;
	return x;
}

inline int IsQueueEmpty(QueueSet_t* q)
{
	return (q->head == q->tail) ? TRUE : FALSE;
}

inline int IsQueueFull(QueueSet_t* q)
{
	return (q->head == ((q->tail + 1 == q->size) ? ARRAYSTARTINDEX : q->tail + 1)) ? TRUE : FALSE;
}

void PrintGraph(GraphSet_t* graph)
{
	int i;
	for (i = 0; i < graph->vertexnum; i++) {
		PrintVertex(graph->vertlist[i]);
		PrintAdjacencyList(graph->adjlist[i]);
		putchar('\n');
	}
	return;
}

void PrintBreadthFirstTree(GraphSet_t* graph)
{
	int i, j;
	printf("Breadth-first tree:\n");
	for (i = 0; i < graph->vertexnum; i++) {
		for (j = 0; j < graph->vertexnum; j++) {
			if (graph->vertlist[j]->distance == i) {
				PrintVertex(graph->vertlist[j]);
				putchar('\n');
			}
		}
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
		printf("  Addr: %p  Num: %4d  Dist: %10d  Color: %-9s  Par: %p",
			vertex, vertex->number, vertex->distance, color, vertex->parent);
	}
	return;
}

void PrintAdjacencyList(AdjacencyListSet_t* adjset)
{
	if (adjset != NULL) {
		printf("  AdjList:");
		while (adjset != NULL) {
			printf(" %d,", adjset->vertex->number);
			adjset = adjset->next;
		}
		printf("\b ");
	}
	return;
}