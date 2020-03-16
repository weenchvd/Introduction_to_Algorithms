#include "SingleSourceShortestPaths.h"

int CreateGraph(Graph_t* graph)
{
	int i, j, y, k, w;
	GraphVertex_t* vertex;
	GraphEdge_t* edge;
	AdjacencyList_t* adjset, * adjset2;
	printf("  Please enter a type of the graph (%d - Directed or %d - Undirected): ", DIRECTED, UNDIRECTED);
	if (scanf("%d", &i) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (i != DIRECTED && i != UNDIRECTED) {
		printf("\n\t| ERROR | The number must be %d or %d |\n\n", DIRECTED, UNDIRECTED);
		return FAILURE;
	}
	graph->type = i;
	printf("  Please enter number of vertices: ");
	if (scanf("%d", &graph->vertexnum) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (graph->vertexnum < 1 || graph->vertexnum > INT_MAX) {
		printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", INT_MAX);
		return FAILURE;
	}
	if ((graph->adjlist = malloc(sizeof(AdjacencyList_t*) * graph->vertexnum)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	if ((graph->vertlist = malloc(sizeof(GraphVertex_t*) * graph->vertexnum)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	printf("  Please enter number of edges: ");
	if (scanf("%d", &graph->edgenum) <= 0) {
		printf("\n\t| ERROR | Incorrect input |\n\n");
		return FAILURE;
	}
	if (graph->edgenum < 0 || graph->edgenum > INT_MAX) {
		printf("\n\t| ERROR | The number must be from 0 to %d |\n\n", INT_MAX);
		return FAILURE;
	}
	if ((graph->edgelist = malloc(sizeof(GraphEdge_t*) * graph->edgenum)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	for (i = j = 0; i < graph->vertexnum; i++) {
		if ((vertex = CreateVertex()) == NULL) {
			j = i;
			break;
		}
		vertex->parent = NULL;
		vertex->number = i + DIFFERENCE;
		vertex->distance = vertex->discovered = vertex->finished = 0;
		vertex->u2.color = NOCOLOR;
		graph->vertlist[i] = vertex;
		graph->adjlist[i] = NULL;
	}
	if (j > 0) {
		for (i = 0; i < j; i++) {
			free(graph->vertlist[i]);
		}
		return FAILURE;
	}
	for (i = 0; i < graph->edgenum; i++) {
		graph->edgelist[i] = NULL;
	}
	y = 0;
	for (i = 0; i < graph->vertexnum; i++) {
		for (j = 1; j < graph->vertexnum; j++) {
			printf("  For vertex #%d, enter the number of the next vertex between which there is an edge. "
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
				printf("  For the edge between the vertices #%d - #%d, enter the weight: ", i + DIFFERENCE, k);
				if (scanf("%d", &w) <= 0) {
					printf("\n\t| ERROR | Incorrect input |\n\n");
					j--;
					continue;
				}
				if (w < INT_MIN || w > INT_MAX) {
					printf("\n\t| ERROR | The weight must from %d to %d |\n\n", INT_MIN, INT_MAX);
					j--;
					continue;
				}
				if ((adjset = CreateAdjacencySet()) == NULL) {
					j--;
					continue;
				}
				adjset->vertex = graph->vertlist[k - DIFFERENCE];
				adjset->weight = w;
				if (IsVertexInAdjacencyList(graph->adjlist[i], adjset->vertex) == FALSE) {
					adjset->next = graph->adjlist[i];
					graph->adjlist[i] = adjset;
					if ((edge = malloc(sizeof(GraphEdge_t))) == NULL) {
						printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
						return FAILURE;
					}
					edge->vertex1 = graph->vertlist[i];
					edge->vertex2 = adjset->vertex;
					edge->weight = adjset->weight;
					if (y < graph->edgenum) {
						graph->edgelist[y++] = edge;
					}
					else {
						printf("\n\t| ERROR | The number of the edges exceeds the specified number |\n\n");
						free(edge);
					}
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
					if ((adjset2 = malloc(sizeof(AdjacencyList_t))) == NULL) {
						printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
						continue;
					}
					adjset2->vertex = graph->vertlist[i];
					adjset2->weight = adjset->weight;
					adjset2->next = graph->adjlist[k];
					graph->adjlist[k] = adjset2;
				}
				adjset = adjset->next;
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

AdjacencyList_t* CreateAdjacencySet()
{
	AdjacencyList_t* adjset;
	if ((adjset = malloc(sizeof(AdjacencyList_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	return adjset;
}

int IsVertexInAdjacencyList(AdjacencyList_t* adjset, GraphVertex_t* vertex)
{
	while (adjset != NULL) {
		if (adjset->vertex == vertex) {
			return TRUE;
		}
		adjset = adjset->next;
	}
	return FALSE;
}

void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination)
{
	if (destination == source) {
		PrintVertex(source);
		putchar('\n');
	}
	else if (destination->parent == NULL) {
		printf("\n\t| ERROR | No path from vertex #%d to vertex #%d exists |\n\n",
			source->number, destination->number);
	}
	else {
		PrintPath(graph, source, destination->parent);
		PrintVertex(destination);
		putchar('\n');
	}
	return;
}

void PrintGraph(Graph_t* graph)
{
	int i;
	for (i = 0; i < graph->vertexnum; i++) {
		PrintVertex(graph->vertlist[i]);
		PrintAdjacencyList(graph->adjlist[i]);
		putchar('\n');
	}
	return;
}

void PrintVertex(GraphVertex_t* vertex)
{
	char color[10];
	if (vertex != NULL) {
		switch (vertex->u2.color) {
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

void PrintAdjacencyList(AdjacencyList_t* adjset)
{
	if (adjset != NULL) {
		printf("  AdjList:");
		while (adjset != NULL) {
			printf(" %d(%d),", adjset->vertex->number, adjset->weight);
			adjset = adjset->next;
		}
		printf("\b ");
	}
	return;
}

void InitializeSingleSource(Graph_t* graph, GraphVertex_t* source)
{
	int i;
	for (i = 0; i < graph->vertexnum; i++) {
		graph->vertlist[i]->distance = INFINITY;
		graph->vertlist[i]->parent = NULL;
	}
	source->distance = 0;
	return;
}

void Relax(GraphVertex_t* source, GraphVertex_t* destination, int edgeweight)
{
	int sum;
	sum = WeightSummarization(source->distance, edgeweight);
	if (destination->distance > sum) {
		destination->distance = sum;
		destination->parent = source;
	}
	return;
}

int WeightSummarization(int weight1, int weight2)
{
	long long int sum;
	if (weight1 != INFINITY && weight1 != INFINITYMINUS) {
		if (weight2 != INFINITY && weight2 != INFINITYMINUS) {
			sum = (long long int)weight1 + weight2;
		}
		else if (weight2 == INFINITY) {
			return INFINITY;
		}
		else {								/* weight2 = INFINITYMINUS */
			return INFINITYMINUS;
		}
	}
	else if (weight1 == INFINITY) {
		if (weight2 == INFINITYMINUS) {
			return 0;
		}
		else {
			return INFINITY;
		}
	}
	else {									/* weight1 = INFINITYMINUS */
		if (weight2 == INFINITY) {
			return 0;
		}
		else {
			return INFINITYMINUS;
		}
	}
	if (sum > INFINITYMINUS && sum < INFINITY) {
		return (int)sum;
	}
	else if (sum >= INFINITY) {
		printf("\n\t| ERROR | The sum of edges is greater than %d |\n\n", INFINITY - 1);
		return INFINITY;
	}
	else {
		printf("\n\t| ERROR | The sum of edges is less than %d |\n\n", INFINITYMINUS + 1);
		return INFINITYMINUS;
	}
}

bool BellmanFord(Graph_t* graph, GraphVertex_t* source)
{
	int i, j;
	InitializeSingleSource(graph, source);
	for (i = 1; i < graph->vertexnum; i++) {
		for (j = 0; j < graph->edgenum; j++) {
			Relax(graph->edgelist[j]->vertex1, graph->edgelist[j]->vertex2, graph->edgelist[j]->weight);
		}
	}
	for (j = 0; j < graph->edgenum; j++) {
		if (graph->edgelist[j]->vertex2->distance > WeightSummarization(graph->edgelist[j]->vertex1->distance, graph->edgelist[j]->weight)) {
			return false;
		}
	}
	return true;
}

void DAGShortestPaths(Graph_t* graph, GraphVertex_t* source)
{
	TopologicalList_t tlist;
	tlist.head = NULL;
	AdjacencyList_t* adjset, * adjset2;
	TopologicalSort(graph, &tlist, NULL);
	InitializeSingleSource(graph, source);
	for (adjset = tlist.head; adjset != NULL; adjset = adjset->next) {
		for (adjset2 = graph->adjlist[adjset->vertex->number - DIFFERENCE]; adjset2 != NULL; adjset2 = adjset2->next) {
			Relax(adjset->vertex, adjset2->vertex, adjset2->weight);
		}
	}
	FreeAdjacencyList(tlist.head);
	return;
}

unsigned int time;

void DepthFirstSearch(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order)
{
	int i;
	for (i = 0; i < graph->vertexnum; i++) {
		graph->vertlist[i]->u2.color = WHITE;
		graph->vertlist[i]->parent = NULL;
	}
	time = 0;
	if (order != NULL) {
		AdjacencyList_t* adjset;
		adjset = order->head;
		while (adjset != NULL) {
			if (adjset->vertex->u2.color == WHITE) {
				DepthFirstSearchVisit(graph, adjset->vertex, tlist);
			}
			adjset = adjset->next;
		}
	}
	else {
		for (i = 0; i < graph->vertexnum; i++) {
			if (graph->vertlist[i]->u2.color == WHITE) {
				DepthFirstSearchVisit(graph, graph->vertlist[i], tlist);
			}
		}
	}
	return;
}

void DepthFirstSearchVisit(Graph_t* graph, GraphVertex_t* vertex, TopologicalList_t* tlist)
{
	AdjacencyList_t* adjset;
	vertex->discovered = ++time;
	vertex->u2.color = GRAY;
	adjset = graph->adjlist[vertex->number - DIFFERENCE];
	while (adjset != NULL) {
		if (adjset->vertex->u2.color == WHITE) {
			adjset->vertex->parent = vertex;
			DepthFirstSearchVisit(graph, adjset->vertex, tlist);
		}
		adjset = adjset->next;
	}
	vertex->u2.color = BLACK;
	vertex->finished = ++time;
	if (tlist != NULL) {
		AdjacencyList_t* adjset2;
		if ((adjset2 = CreateAdjacencySet()) == NULL) {
			return;
		}
		adjset2->vertex = vertex;
		adjset2->weight = INT_MIN;
		adjset2->next = tlist->head;
		tlist->head = adjset2;
	}
	return;
}

void TopologicalSort(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order)
{
	DepthFirstSearch(graph, tlist, order);
	return;
}
