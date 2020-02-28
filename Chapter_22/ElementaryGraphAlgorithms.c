#include "ElementaryGraphAlgorithms.h"

int CreateGraph(Graph_t* graph)
{
	int i, j, k;
	GraphVertex_t* vertex;
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
	for (i = j = 0; i < graph->vertexnum; i++) {
		if ((vertex = CreateVertex()) == NULL) {
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
				if ((adjset = CreateAdjacencySet()) == NULL) {
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
					if ((adjset2 = malloc(sizeof(AdjacencyList_t))) == NULL) {
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

void BreadthFirstSearch(Graph_t* graph, GraphVertex_t* vertex)
{
	int i;
	Queue_t q;
	GraphVertex_t* current, * descendant;
	AdjacencyList_t* adjset;
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

unsigned int time;

void DepthFirstSearch(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order)
{
	int i;
	for (i = 0; i < graph->vertexnum; i++) {
		graph->vertlist[i]->color = WHITE;
		graph->vertlist[i]->parent = NULL;
	}
	time = 0;
	if (order != NULL) {
		AdjacencyList_t* adjset;
		adjset = order->head;
		while (adjset != NULL) {
			if (adjset->vertex->color == WHITE) {
				DepthFirstSearchVisit(graph, adjset->vertex, tlist);
			}
			adjset = adjset->next;
		}
	}
	else {
		for (i = 0; i < graph->vertexnum; i++) {
			if (graph->vertlist[i]->color == WHITE) {
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
	vertex->color = GRAY;
	adjset = graph->adjlist[vertex->number - DIFFERENCE];
	while (adjset != NULL) {
		if (adjset->vertex->color == WHITE) {
			adjset->vertex->parent = vertex;
			DepthFirstSearchVisit(graph, adjset->vertex, tlist);
		}
		adjset = adjset->next;
	}
	vertex->color = BLACK;
	vertex->finished = ++time;
	if (tlist != NULL) {
		AdjacencyList_t* adjset2;
		if ((adjset2 = CreateAdjacencySet()) == NULL) {
			return;
		}
		adjset2->vertex = vertex;
		adjset2->next = tlist->head;
		tlist->head = adjset2;
	}
	return;
}

void Enqueue(Queue_t* q, GraphVertex_t* x)
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

GraphVertex_t* Dequeue(Queue_t* q)
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

inline int IsQueueEmpty(Queue_t* q)
{
	return (q->head == q->tail) ? TRUE : FALSE;
}

inline int IsQueueFull(Queue_t* q)
{
	return (q->head == ((q->tail + 1 == q->size) ? ARRAYSTARTINDEX : q->tail + 1)) ? TRUE : FALSE;
}

void TopologicalSort(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order)
{
	DepthFirstSearch(graph, tlist, order);
	return;
}

void StronglyConnectedComponents(Graph_t* graph)
{
	int i;
	TopologicalList_t tlist, order;
	tlist.head = NULL;
#if PRINTGRAPHSTATE
	printf("The initial graph\n");
	PrintGraph(graph);
#endif // PRINTGRAPHSTATE
	TopologicalSort(graph, &tlist, NULL);
#if PRINTGRAPHSTATE
	printf("The graph after TopologicalSort()\n");
	PrintGraph(graph);
#endif // PRINTGRAPHSTATE
	TransposeGraph(graph);
#if PRINTGRAPHSTATE
	printf("The graph after TransposeGraph()\n");
	PrintGraph(graph);
#endif // PRINTGRAPHSTATE
	order.head = tlist.head;
	tlist.head = NULL;
	TopologicalSort(graph, &tlist, &order);
#if PRINTGRAPHSTATE
	printf("The graph after TopologicalSort()\n");
	PrintGraph(graph);
	putchar('\n');
#endif // PRINTGRAPHSTATE
	PrintSCCVertices(&tlist);
	TransposeGraph(graph);
#if PRINTGRAPHSTATE
	putchar('\n');
	printf("The graph after TransposeGraph()\n");
	PrintGraph(graph);
#endif // PRINTGRAPHSTATE
	FreeAdjacencyList(tlist.head);
	FreeAdjacencyList(order.head);
	return;
}

void TransposeGraph(Graph_t* graph)
{
	int i, j;
	AdjacencyList_t* adjset, * adjsetnext, ** adjlisttransposed;
	if ((adjlisttransposed = malloc(sizeof(AdjacencyList_t*) * graph->vertexnum)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return;
	}
	for (i = 0; i < graph->vertexnum; i++) {
		adjlisttransposed[i] = NULL;
	}
	for (i = 0; i < graph->vertexnum; i++) {
		adjset = graph->adjlist[i];
		while (adjset != NULL) {
			adjsetnext = adjset->next;
			j = adjset->vertex->number - DIFFERENCE;
			adjset->vertex = graph->vertlist[i];
			adjset->next = adjlisttransposed[j];
			adjlisttransposed[j] = adjset;
			adjset = adjsetnext;
		}
	}
	free(graph->adjlist);
	graph->adjlist = adjlisttransposed;
	return;
}

/* the function prints vertices of strongly connected components */
void PrintSCCVertices(TopologicalList_t* tlist)
{
	int i;
	const char* message = "  Vertices of a strongly connected component #";
	AdjacencyList_t* adjset;
	i = 0;
	adjset = tlist->head;
	while (adjset != NULL) {
		if (adjset->vertex->parent == NULL) {
			if (i > 0) {
				printf("\b \n");
			}
			printf("%s%d:", message, ++i);
		}
		printf(" %d,", adjset->vertex->number);
		adjset = adjset->next;
	}
	if (i > 0) {
		printf("\b \n");
	}
	return;
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

void PrintBreadthFirstTree(Graph_t* graph)
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

void PrintDepthFirstTree(Graph_t* graph)
{
	int i, j;
	char* printed;
	if ((printed = malloc(sizeof(char) * graph->vertexnum)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return;
	}
	for (i = 0; i < graph->vertexnum; i++) {
		printed[i] = FALSE;
	}
	printf("Depth-first tree:\n");
	for (i = 1; i <= 2 * graph->vertexnum; i++) {
		for (j = 0; j < graph->vertexnum; j++) {
			if (printed[j] == FALSE && graph->vertlist[j]->discovered == i) {
				PrintVertex(graph->vertlist[j]);
				putchar('\n');
				printed[graph->vertlist[j]->number - DIFFERENCE] = TRUE;
				break;
			}
		}
	}
	free(printed);
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

void PrintAdjacencyList(AdjacencyList_t* adjset)
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