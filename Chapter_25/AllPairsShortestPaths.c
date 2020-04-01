#include "AllPairsShortestPaths.h"

int CreateGraph(Graph_t* graph)
{
	int i, j, y, k, w, rows;
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
	if ((graph->adjmatrix = CreateAdjacencyMatrix(graph->vertexnum)) == NULL) {
		return FAILURE;
	}
	rows = graph->adjmatrix->rows;
	for (i = 0, j = rows * rows; i < j; i++) {
		graph->adjmatrix->weight[i] = INFINITY;
	}
	for (i = 1; i <= rows; i++) {
		graph->adjmatrix->weight[item(i, i, rows)] = 0;
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
						graph->adjmatrix->weight[item(edge->vertex1->number, edge->vertex2->number, rows)] = edge->weight;
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
					graph->adjmatrix->weight[item(k + DIFFERENCE, i + DIFFERENCE, rows)] = adjset2->weight;
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

void PrintAllPairsShortestPath(AdjacencyMatrix_t* predSubgraph, int i, int j)
{
	if (i == j) {
		printf("%d ", i);
	}
	else if (predSubgraph->weight[item(i, j, predSubgraph->rows)] == NIL) {
		printf("  No path from vertex #%d to vertex #%d exists", i, j);
	}
	else {
		PrintAllPairsShortestPath(predSubgraph, i, predSubgraph->weight[item(i, j, predSubgraph->rows)]);
		printf("%d ", j);
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

int WeightSummarization(int weight1, int weight2)
{
	long long int sum;
	if (weight1 != INFINITY && weight1 != INFINITYMINUS) {
		if (weight2 != INFINITY && weight2 != INFINITYMINUS) {
			sum = (long long int)weight1 + (long long int)weight2;
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

AdjacencyMatrix_t* CreateAdjacencyMatrix(const int rows)
{
	AdjacencyMatrix_t* adjmatrix;
	if ((adjmatrix = malloc(sizeof(AdjacencyMatrix_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	if ((adjmatrix->weight = malloc(sizeof(int) * rows * rows)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		free(adjmatrix);
		return NULL;
	}
	adjmatrix->rows = rows;
	return adjmatrix;
}

AdjacencyMatrix_t* MakeCopyAdjacencyMatrix(const AdjacencyMatrix_t* source)
{
	int i, n;
	AdjacencyMatrix_t* destination;
	n = source->rows;
	if ((destination = CreateAdjacencyMatrix(n)) == NULL) {
		return NULL;
	}
	for (i = 0; i < n * n; i++) {
		destination->weight[i] = source->weight[i];
	}
	return destination;
}

void FreeAdjacencyMatrix(AdjacencyMatrix_t* adjmatrix)
{
	free(adjmatrix->weight);
	free(adjmatrix);
	return;
}

AdjacencyMatrix_t* ExtendShortestPaths(AdjacencyMatrix_t* shortestPath, AdjacencyMatrix_t* edgeWeight)
{
	int i, j, k, n;
	AdjacencyMatrix_t* newShortestPath;
	n = shortestPath->rows;
	if ((newShortestPath = CreateAdjacencyMatrix(n)) == NULL) {
		return NULL;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			newShortestPath->weight[item(i, j, n)] = INFINITY;
			for (k = 1; k <= n; k++) {
				newShortestPath->weight[item(i, j, n)] = min(newShortestPath->weight[item(i, j, n)],
					WeightSummarization(shortestPath->weight[item(i, k, n)], edgeWeight->weight[item(k, j, n)]));
			}
		}
	}
	return newShortestPath;
}

AdjPredSet_t* ExtendShortestPathsAndPredecessorSubgraph(AdjPredSet_t* adjpred, AdjacencyMatrix_t* edgeWeight)
{
	int i, j, k, n, currentWeight, newWeight;
	AdjacencyMatrix_t* shortestPath, * newShortestPath, * predSubgraph;
	shortestPath = adjpred->shortestPath;
	predSubgraph = adjpred->predSubgraph;
	n = shortestPath->rows;
	if ((newShortestPath = CreateAdjacencyMatrix(n)) == NULL) {
		return NULL;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			newShortestPath->weight[item(i, j, n)] = INFINITY;
			predSubgraph->weight[item(i, j, n)] = NIL;
			for (k = 1; k <= n; k++) {
				currentWeight = newShortestPath->weight[item(i, j, n)];
				newWeight = WeightSummarization(shortestPath->weight[item(i, k, n)], edgeWeight->weight[item(k, j, n)]);
				if (newWeight < currentWeight) {
					newShortestPath->weight[item(i, j, n)] = newWeight;
				}
				if (newWeight <= currentWeight && k != j) {
					predSubgraph->weight[item(i, j, n)] = k;
				}
			}
		}
	}
	adjpred->shortestPath = newShortestPath;
	return adjpred;
}

AdjPredSet_t* SlowAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight)
{
	int i, j, k, n;
	AdjacencyMatrix_t* shortestPath, * predSubgraph;
	AdjPredSet_t* adjpred;
	if ((adjpred = malloc(sizeof(AdjPredSet_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	n = edgeWeight->rows;
	if ((shortestPath = MakeCopyAdjacencyMatrix(edgeWeight)) == NULL) {
		return NULL;
	}
	if ((predSubgraph = CreateAdjacencyMatrix(n)) == NULL) {
		return NULL;
	}
	adjpred->shortestPath = shortestPath;
	adjpred->predSubgraph = predSubgraph;
	for (i = 2; i < n; i++) {
		shortestPath = adjpred->shortestPath;
		if ((adjpred = ExtendShortestPathsAndPredecessorSubgraph(adjpred, edgeWeight)) == NULL) {
			return NULL;
		}
		FreeAdjacencyMatrix(shortestPath);
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			for (k = 1; k <= n; k++) {
				if (adjpred->shortestPath->weight[item(i, j, n)] == INFINITY) {
					adjpred->predSubgraph->weight[item(i, j, n)] = NIL;
				}
			}
		}
	}
	return adjpred;
}

AdjacencyMatrix_t* FasterAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight)
{
	int i, n;
	AdjacencyMatrix_t* shortestPath, * shortestPath2, * shortestPath3;
	n = edgeWeight->rows;
	if ((shortestPath = MakeCopyAdjacencyMatrix(edgeWeight)) == NULL) {
		return NULL;
	}
	i = 1;
	while (i < n - 1) {
		shortestPath2 = shortestPath;
		if ((shortestPath3 = MakeCopyAdjacencyMatrix(shortestPath2)) == NULL) {
			return NULL;
		}
		if ((shortestPath = ExtendShortestPaths(shortestPath2, shortestPath3)) == NULL) {
			return NULL;
		}
		FreeAdjacencyMatrix(shortestPath2);
		FreeAdjacencyMatrix(shortestPath3);
		i *= 2;
	}
	return shortestPath;
}

AdjPredSet_t* FloydWarshall(const AdjacencyMatrix_t* edgeWeight)
{
	int i, j, k, n, currentWeight, newWeight;
	AdjacencyMatrix_t* shortestPath, * predSubgraph;
	AdjPredSet_t* adjPred;
	if ((adjPred = malloc(sizeof(AdjPredSet_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	n = edgeWeight->rows;
	if ((shortestPath = MakeCopyAdjacencyMatrix(edgeWeight)) == NULL) {
		return NULL;
	}
	if ((predSubgraph = CreateAdjacencyMatrix(n)) == NULL) {
		return NULL;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			predSubgraph->weight[item(i, j, n)] = (i == j || edgeWeight->weight[item(i, j, n)] == INFINITY) ? NIL : i;
		}
	}
	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				currentWeight = shortestPath->weight[item(i, j, n)];
				newWeight = WeightSummarization(shortestPath->weight[item(i, k, n)], shortestPath->weight[item(k, j, n)]);
				if (newWeight < currentWeight) {
					shortestPath->weight[item(i, j, n)] = newWeight;
					predSubgraph->weight[item(i, j, n)] = predSubgraph->weight[item(k, j, n)];
				}
				else {
					shortestPath->weight[item(i, j, n)] = currentWeight;
					predSubgraph->weight[item(i, j, n)] = predSubgraph->weight[item(i, j, n)];
				}
			}
		}
	}
	adjPred->shortestPath = shortestPath;
	adjPred->predSubgraph = predSubgraph;
	adjPred->isNegativeWeightCycle = false;
	for (i = 1; i <= n; i++) {
		if (shortestPath->weight[item(i, i, n)] < 0) {
			adjPred->isNegativeWeightCycle = true;
			break;
		}
	}
	return adjPred;
}

void SetBitValueInTransitiveClosureMatrix(TClosure_t* clos, int i, int j, int value)
{
	int itemNumber, byteNumber, leftShift;
	itemNumber = item(i, j, clos->rows) + 1;
	byteNumber = ((itemNumber % CHAR_BIT > 0) ? itemNumber / CHAR_BIT + 1 : itemNumber / CHAR_BIT) - 1;
	leftShift = (itemNumber - 1) % CHAR_BIT;
	clos->key[byteNumber] = (value == true) ? (clos->key[byteNumber] | 1 << leftShift) : (clos->key[byteNumber] & ~(1 << leftShift));
	return;
}

bool GetBitValueInTransitiveClosureMatrix(TClosure_t* clos, int i, int j)
{
	int itemNumber, byteNumber, leftShift;
	itemNumber = item(i, j, clos->rows) + 1;
	byteNumber = ((itemNumber % CHAR_BIT > 0) ? itemNumber / CHAR_BIT + 1 : itemNumber / CHAR_BIT) - 1;
	leftShift = (itemNumber - 1) % CHAR_BIT;
	return clos->key[byteNumber] & 1 << leftShift;
}

TClosure_t* TransitiveClosure(AdjacencyMatrix_t* edgeWeight)
{
	char currentValue, newValue;
	int i, j, k, n;
	TClosure_t* clos, * newClos;
	n = edgeWeight->rows;
	if ((clos = CreateTransitiveClosureMatrix(n)) == NULL) {
		return NULL;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (i == j || edgeWeight->weight[item(i, j, n)] < INFINITY) {
				SetBitValueInTransitiveClosureMatrix(clos, i, j, true);
			}
			else {
				SetBitValueInTransitiveClosureMatrix(clos, i, j, false);
			}
		}
	}
	for (k = 1; k <= n; k++) {
		if ((newClos = CreateTransitiveClosureMatrix(n)) == NULL) {
			return NULL;
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				currentValue = GetBitValueInTransitiveClosureMatrix(clos, i, j);
				newValue = GetBitValueInTransitiveClosureMatrix(clos, i, k) & GetBitValueInTransitiveClosureMatrix(clos, k, j);
				SetBitValueInTransitiveClosureMatrix(newClos, i, j, currentValue | newValue);
			}
		}
		FreeTransitiveClosureMatrix(clos);
		clos = newClos;
	}
	return clos;
}

TClosure_t* CreateTransitiveClosureMatrix(const int rows)
{
	TClosure_t* clos;
	if ((clos = malloc(sizeof(TClosure_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	if ((clos->key = malloc(sizeof(char) * GetClosureSizeInBytes(rows))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		free(clos);
		return NULL;
	}
	clos->rows = rows;
	return clos;
}

void FreeTransitiveClosureMatrix(TClosure_t* clos)
{
	free(clos->key);
	free(clos);
	return;
}

AdjacencyMatrix_t* Johnson(Graph_t* graph)
{
	int i, j, n;
	int* h;
	GraphVertex_t* vertex;
	AdjacencyList_t* adjSet;
	AdjacencyMatrix_t* shortestPath, * edgeWeight, * newEdgeWeight;
	shortestPath = NULL;
	n = graph->vertexnum;
	if ((vertex = CreateVertex()) == NULL) {
		return NULL;
	}
	graph->auxVertex = vertex;
	for (i = 0; i < n; i++) {
		if ((adjSet = CreateAdjacencySet()) == NULL) {
			return NULL;
		}
		adjSet->vertex = graph->vertlist[i];
		adjSet->next = graph->auxAdjList;
		adjSet->weight = 0;
		graph->auxAdjList = adjSet;
	}
	if (BellmanFord(graph, vertex) == false) {
		printf("\n\t| ERROR | The graph contain a negative-weight cycle |\n\n");
	}
	else {
		if ((h = malloc(sizeof(int) * n)) == NULL) {
			printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
			return NULL;
		}
		for (i = 0; i < n; i++) {
			h[i] = graph->vertlist[i]->distance;
		}
		edgeWeight = graph->adjmatrix;
		if ((newEdgeWeight = CreateAdjacencyMatrix(n)) == NULL) {
			return NULL;
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				newEdgeWeight->weight[item(i, j, n)] =
					WeightSummarization(edgeWeight->weight[item(i, j, n)], (h[i - DIFFERENCE] - h[j - DIFFERENCE]));
			}
		}
		if ((shortestPath = CreateAdjacencyMatrix(n)) == NULL) {
			return NULL;
		}
		graph->adjmatrix = newEdgeWeight;
		for (i = 1; i <= n; i++) {
			vertex = graph->vertlist[i - DIFFERENCE];
			Dijkstra(graph, vertex);
			for (j = 1; j <= n; j++) {
				shortestPath->weight[item(i, j, n)] =
					WeightSummarization(graph->vertlist[j - DIFFERENCE]->distance, (h[j - DIFFERENCE] - h[i - DIFFERENCE]));
			}
		}
		graph->adjmatrix = edgeWeight;
		FreeAdjacencyMatrix(newEdgeWeight);
		free(h);
	}
	FreeAuxDataFromGraph(graph);
	return shortestPath;
}

void FreeAuxDataFromGraph(Graph_t* graph)
{
	AdjacencyList_t* adjSet, * adjSetNext;
	free(graph->auxVertex);
	adjSet = graph->auxAdjList;
	while (adjSet != NULL) {
		adjSetNext = adjSet->next;
		free(adjSet);
		adjSet = adjSetNext;
	}
	graph->auxVertex = NULL;
	graph->auxAdjList = NULL;
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

bool BellmanFord(Graph_t* graph, GraphVertex_t* source)
{
	int i, j, numberOfVertices;
	GraphVertex_t* vertex;
	AdjacencyList_t* adjSet;
	if (graph->auxVertex != NULL) {
		vertex = graph->auxVertex;
		numberOfVertices = graph->vertexnum + 1;
	}
	else {
		numberOfVertices = graph->vertexnum;
	}
	InitializeSingleSource(graph, source);
	for (i = 1; i < numberOfVertices; i++) {
		for (j = 0; j < graph->edgenum; j++) {
			Relax(graph->edgelist[j]->vertex1, graph->edgelist[j]->vertex2, graph->edgelist[j]->weight);
		}
		adjSet = graph->auxAdjList;
		while (adjSet != NULL) {
			Relax(vertex, adjSet->vertex, adjSet->weight);
			adjSet = adjSet->next;
		}
	}
	for (j = 0; j < graph->edgenum; j++) {
		if (graph->edgelist[j]->vertex2->distance > WeightSummarization(graph->edgelist[j]->vertex1->distance, graph->edgelist[j]->weight)) {
			return false;
		}
	}
	return true;
}

void Dijkstra(Graph_t* graph, GraphVertex_t* source)
{
	int i, j, n, distance, weight;
	GraphVertex_t* vertex1, * vertex2;
	HeapQueue_t* vertices;
	HeapQueueSet_t set;
	n = graph->vertexnum;
	if ((vertices = CreateHeapQueue(n)) == NULL) {
		return;
	}
	InitializeSingleSource(graph, source);
	for (i = 0; i < n; i++) {
		graph->vertlist[i]->u2.mark = true;
		MinHeapInsert(vertices, graph->vertlist[i]);
	}
	while (vertices->heapsize > 1) {
		HeapExtractMin(vertices, &set);
		vertex1 = set.handle;
		vertex1->u2.mark = false;
		i = vertex1->number;
		for (j = 1; j <= n; j++) {
			if ((weight = graph->adjmatrix->weight[item(i, j, n)]) != INFINITY) {
				vertex2 = graph->vertlist[j - DIFFERENCE];
				distance = vertex2->distance;
				Relax(vertex1, vertex2, weight);
				if (vertex2->u2.mark == true && distance != vertex2->distance) {
					HeapDecreaseKey(vertices, vertex2->u1.index, vertex2->distance);
				}
			}
		}
	}
	HeapExtractMin(vertices, &set);
	FreeHeapQueue(vertices);
	return;
}

HeapQueue_t* CreateHeapQueue(int heapsizelimit)
{
	HeapQueue_t* queue;
	if ((queue = malloc(sizeof(HeapQueue_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	if (InitializeHeap(queue, heapsizelimit) == FAILURE) {
		free(queue);
		return NULL;
	}
	return queue;
}

int InitializeHeap(HeapQueue_t* queue, int heapsizelimit)
{
	queue->heapsize = 0;
	queue->heapsizelimit = heapsizelimit;
	if ((queue->handle = malloc(sizeof(GraphVertex_t*) * (queue->heapsizelimit + HEAPSTARTINDEX))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	if ((queue->priority = malloc(sizeof(int) * (queue->heapsizelimit + HEAPSTARTINDEX))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	return SUCCESS;
}

HeapQueueSet_t* HeapMin(HeapQueue_t* queue, HeapQueueSet_t* set)
{
	if (queue->heapsize < 1) {
		printf("\n\t| ERROR | Heap underflow |\n\n");
		return NULL;
	}
	set->priority = HEAPMINIMUM(queue->priority);
	set->handle = HEAPMINIMUM(queue->handle);
	return set;
}

HeapQueueSet_t* HeapExtractMin(HeapQueue_t* queue, HeapQueueSet_t* set)
{
	if (queue->heapsize < 1) {
		printf("\n\t| ERROR | Heap underflow |\n\n");
		return NULL;
	}
	set->priority = queue->priority[HEAPSTARTINDEX];
	set->handle = queue->handle[HEAPSTARTINDEX];
	queue->priority[HEAPSTARTINDEX] = queue->priority[queue->heapsize];
	queue->handle[HEAPSTARTINDEX] = queue->handle[queue->heapsize--];
	queue->handle[HEAPSTARTINDEX]->u1.index = HEAPSTARTINDEX;
	MinHeapify(queue, HEAPSTARTINDEX);
	return set;
}

void HeapDecreaseKey(HeapQueue_t* queue, int index, int newpriority)
{
	int parent;
	GraphVertex_t* handle;
	if (index > queue->heapsize) {
		printf("\n\t| ERROR | Index is greater than heap size |\n\n");
		return;
	}
	if (index < HEAPSTARTINDEX) {
		printf("\n\t| ERROR | Index is less than %d |\n\n", HEAPSTARTINDEX);
		return;
	}
	if (newpriority > queue->priority[index]) {
		printf("\n\t| ERROR | New priority is bigger than current priority |\n\n");
		return;
	}
	handle = queue->handle[index];
	while (index > 1 && queue->priority[parent = PARENT(index)] > newpriority) {
		queue->priority[index] = queue->priority[parent];
		queue->handle[index] = queue->handle[parent];
		queue->handle[index]->u1.index = index;
		index = parent;
	}
	queue->priority[index] = newpriority;
	queue->handle[index] = handle;
	queue->handle[index]->u1.index = index;
	return;
}

void MinHeapInsert(HeapQueue_t* queue, GraphVertex_t* handle)
{
	if (queue->heapsize >= queue->heapsizelimit) {
		printf("\n\t| ERROR | Heap size limit reached |\n\n");
		return;
	}
	queue->priority[++queue->heapsize] = INT_MAX;
	queue->handle[queue->heapsize] = handle;
	HeapDecreaseKey(queue, queue->heapsize, handle->distance);
	return;
}

void MinHeapDelete(HeapQueue_t* queue, int index)
{
	if (index > queue->heapsize) {
		printf("\n\t| ERROR | Index is greater than heap size |\n\n");
		return;
	}
	if (index < HEAPSTARTINDEX) {
		printf("\n\t| ERROR | Index is less than %d |\n\n", HEAPSTARTINDEX);
		return;
	}
	queue->priority[index] = queue->priority[queue->heapsize];
	queue->handle[index] = queue->handle[queue->heapsize--];
	queue->handle[index]->u1.index = index;
	MinHeapify(queue, index);
	return;
}

void MinHeapify(HeapQueue_t* queue, int index)
{
	int left, right, smallest;
	HeapQueueSet_t tmp;
	while (TRUE)
	{
		left = LEFT(index);
		right = RIGHT(index);
		if (left <= queue->heapsize && queue->priority[left] < queue->priority[index]) {
			smallest = left;
		}
		else {
			smallest = index;
		}
		if (right <= queue->heapsize && queue->priority[right] < queue->priority[smallest]) {
			smallest = right;
		}
		if (smallest != index) {
			tmp.priority = queue->priority[index];
			tmp.handle = queue->handle[index];
			queue->priority[index] = queue->priority[smallest];
			queue->handle[index] = queue->handle[smallest];
			queue->handle[index]->u1.index = index;
			queue->priority[smallest] = tmp.priority;
			queue->handle[smallest] = tmp.handle;
			queue->handle[smallest]->u1.index = smallest;
			index = smallest;
		}
		else {
			break;
		}
	}
	return;
}

void FreeHeapQueue(HeapQueue_t* queue)
{
	free(queue->handle);
	free(queue->priority);
	free(queue);
	return;
}
