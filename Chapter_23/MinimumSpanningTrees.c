#include "MinimumSpanningTrees.h"

int CreateGraph(Graph_t* graph)
{
	int i, j, k, w, edgenum;
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
	graph->edgenum = 0;
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
				if (w < 1 || w > INT_MAX) {
					printf("\n\t| ERROR | The weight must from %d to %d |\n\n", 1, INT_MAX);
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
					graph->edgenum++;
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

int GenericMST(Graph_t* graph, Queue_t* mst)
{
	int i, j, tree1, tree2;
	int* forest;
	HeapQueueSet_t hset;
	HeapQueue_t* hqueue;
	AdjacencyList_t* adjset;
	GraphEdge_t* edge;
	if ((forest = malloc(sizeof(int) * (graph->vertexnum + DIFFERENCE))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	for (i = 0; i < DIFFERENCE; i++) {
		forest[i] = -1;
	}
	for (i = DIFFERENCE; i < graph->vertexnum + DIFFERENCE; i++) {
		forest[i] = i;
	}
	mst->size = graph->vertexnum;
	if ((mst->queue = malloc(sizeof(GraphEdge_t*) * mst->size)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	mst->head = mst->tail = 0;
	if ((hqueue = CreateHeapQueue(graph->edgenum)) == NULL) {
		return FAILURE;
	}
	for (i = 0; i < graph->vertexnum; i++) {
		adjset = graph->adjlist[i];
		while (adjset != NULL) {
			if (adjset->vertex->number >= i + DIFFERENCE) {
				if ((edge = malloc(sizeof(GraphEdge_t))) == NULL) {
					printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
					return FAILURE;
				}
				edge->vertex1 = graph->vertlist[i];
				edge->vertex2 = adjset->vertex;
				edge->weight = adjset->weight;
				MinHeapInsert(hqueue, edge);
			}
			adjset = adjset->next;
		}
	}
	for (i = 0; i < graph->vertexnum - 1; i++) {
		if (hqueue->heapsize > 0) {
			HeapExtractMin(hqueue, &hset);
			edge = hset.handle;
			tree1 = forest[edge->vertex1->number];
			tree2 = forest[edge->vertex2->number];
			if (tree1 != tree2) {
				Enqueue(mst, edge);
				for (j = DIFFERENCE; j < graph->vertexnum + DIFFERENCE; j++) {
					if (forest[j] == tree2) {
						forest[j] = tree1;
					}
				}
			}
			else {
				i--;
			}
		}
	}
	while (hqueue->heapsize > 0) {
		HeapExtractMin(hqueue, &hset);
		free(hset.handle);
	}
	PrintMST(mst);
	free(mst->queue);
	free(forest);
	return SUCCESS;
}

int MSTKruskal(Graph_t* graph, Queue_t* mst)
{
	int i;
	HeapQueueSet_t hset;
	HeapQueue_t* hqueue;
	AdjacencyList_t* adjset;
	GraphEdge_t* edge;
	mst->size = graph->vertexnum;
	if ((mst->queue = malloc(sizeof(GraphEdge_t*) * mst->size)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	mst->head = mst->tail = 0;
	for (i = 0; i < graph->vertexnum; i++) {
		MakeSet(graph->vertlist[i]);
	}
	if ((hqueue = CreateHeapQueue(graph->edgenum)) == NULL) {
		return FAILURE;
	}
	for (i = 0; i < graph->vertexnum; i++) {
		adjset = graph->adjlist[i];
		while (adjset != NULL) {
			if (adjset->vertex->number > i + DIFFERENCE) {
				if ((edge = malloc(sizeof(GraphEdge_t))) == NULL) {
					printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
					return FAILURE;
				}
				edge->vertex1 = graph->vertlist[i];
				edge->vertex2 = adjset->vertex;
				edge->weight = adjset->weight;
				MinHeapInsert(hqueue, edge);
			}
			adjset = adjset->next;
		}
	}
	while (hqueue->heapsize > 0) {
		HeapExtractMin(hqueue, &hset);
		edge = hset.handle;
		if (FindSet(edge->vertex1) != FindSet(edge->vertex2)) {
			Enqueue(mst, edge);
			UnionSet(edge->vertex1, edge->vertex2);
		}
		else {
			free(edge);
		}
	}
	PrintMST(mst);
	free(mst->queue);
	FreeHeapQueue(hqueue);
	return SUCCESS;
}

int MSTPrim(Graph_t* graph, GraphVertex_t* root, Queue_t* mst)
{
	int i;
	HeapQueueVSet_t hset;
	HeapQueueV_t* hqueue;
	AdjacencyList_t* adjset;
	GraphVertex_t* vertex;
	GraphEdge_t* edge;
	mst->size = graph->vertexnum;
	if ((mst->queue = malloc(sizeof(GraphEdge_t*) * mst->size)) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return FAILURE;
	}
	mst->head = mst->tail = 0;
	if ((hqueue = CreateHeapQueueV(graph->vertexnum)) == NULL) {
		return FAILURE;
	}
	for (i = 0; i < graph->vertexnum; i++) {
		graph->vertlist[i]->u1.key = INT_MAX;
		graph->vertlist[i]->parent = NULL;
		graph->vertlist[i]->u2.mark = TRUE;
	}
	root->u1.key = 0;
	for (i = 0; i < graph->vertexnum; i++) {
		MinHeapInsertV(hqueue, graph->vertlist[i]);
	}
	while (hqueue->heapsize > 0) {
		HeapExtractMinV(hqueue, &hset);
		vertex = hset.handle;
		vertex->u2.mark = FALSE;
		if (vertex->parent != NULL) {
			if ((edge = malloc(sizeof(GraphEdge_t))) == NULL) {
				printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
				return FAILURE;
			}
			edge->vertex1 = vertex->parent;
			edge->vertex2 = vertex;
			edge->weight = vertex->u1.key;
			Enqueue(mst, edge);
		}
		adjset = graph->adjlist[vertex->number - DIFFERENCE];
		while (adjset != NULL) {
			if (adjset->vertex->u2.mark == TRUE && adjset->weight < adjset->vertex->u1.key) {
				adjset->vertex->parent = vertex;
				for (i = 1; i <= hqueue->heapsize; i++) {
					if (adjset->vertex == hqueue->handle[i]) {
						break;
					}
				}
				adjset->vertex->u1.key = adjset->weight;
				HeapDecreaseKeyV(hqueue, i, adjset->weight);
			}
			adjset = adjset->next;
		}
	}
	PrintMST(mst);
	free(mst->queue);
	FreeHeapQueue(hqueue);
	return SUCCESS;
}

void Enqueue(Queue_t* q, GraphEdge_t* x)
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

GraphEdge_t* Dequeue(Queue_t* q)
{
	GraphEdge_t* x;
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

void PrintMST(Queue_t* mst)
{
	int i, w;
	GraphEdge_t* edge;
	printf("  MST:\n");
	i = w = 0;
	while (IsQueueEmpty(mst) != TRUE) {
		edge = Dequeue(mst);
		printf("  Edge between vertices #%4d (%p) - #%4d (%p) with a weight of %d\n",
			edge->vertex1->number, edge->vertex1, edge->vertex2->number, edge->vertex2, edge->weight);
		w += edge->weight;
		i++;
		free(edge);
	}
	printf("  Total weight: %6d  Number of the edges: %4d\n", w, i);
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
	if ((queue->handle = malloc(sizeof(GraphEdge_t*) * (queue->heapsizelimit + HEAPSTARTINDEX))) == NULL) {
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
	MinHeapify(queue, HEAPSTARTINDEX);
	return set;
}

void HeapDecreaseKey(HeapQueue_t* queue, int index, int newpriority)
{
	int parent;
	GraphEdge_t* handle;
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
		index = parent;
	}
	queue->priority[index] = newpriority;
	queue->handle[index] = handle;
	return;
}

void MinHeapInsert(HeapQueue_t* queue, GraphEdge_t* handle)
{
	if (queue->heapsize >= queue->heapsizelimit) {
		printf("\n\t| ERROR | Heap size limit reached |\n\n");
		return;
	}
	queue->priority[++queue->heapsize] = INT_MAX;
	queue->handle[queue->heapsize] = handle;
	HeapDecreaseKey(queue, queue->heapsize, handle->weight);
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
	free(queue->handle[index]);
	queue->handle[index] = queue->handle[queue->heapsize--];
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
			queue->priority[smallest] = tmp.priority;
			queue->handle[smallest] = tmp.handle;
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


HeapQueueV_t* CreateHeapQueueV(int heapsizelimit)
{
	HeapQueueV_t* queue;
	if ((queue = malloc(sizeof(HeapQueueV_t))) == NULL) {
		printf("\n\t| ERROR | Memory allocator error. No memory allocated |\n\n");
		return NULL;
	}
	if (InitializeHeapV(queue, heapsizelimit) == FAILURE) {
		free(queue);
		return NULL;
	}
	return queue;
}

int InitializeHeapV(HeapQueueV_t* queue, int heapsizelimit)
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

HeapQueueVSet_t* HeapMinV(HeapQueueV_t* queue, HeapQueueVSet_t* set)
{
	if (queue->heapsize < 1) {
		printf("\n\t| ERROR | Heap underflow |\n\n");
		return NULL;
	}
	set->priority = HEAPMINIMUM(queue->priority);
	set->handle = HEAPMINIMUM(queue->handle);
	return set;
}

HeapQueueVSet_t* HeapExtractMinV(HeapQueueV_t* queue, HeapQueueVSet_t* set)
{
	if (queue->heapsize < 1) {
		printf("\n\t| ERROR | Heap underflow |\n\n");
		return NULL;
	}
	set->priority = queue->priority[HEAPSTARTINDEX];
	set->handle = queue->handle[HEAPSTARTINDEX];
	queue->priority[HEAPSTARTINDEX] = queue->priority[queue->heapsize];
	queue->handle[HEAPSTARTINDEX] = queue->handle[queue->heapsize--];
	MinHeapifyV(queue, HEAPSTARTINDEX);
	return set;
}

void HeapDecreaseKeyV(HeapQueueV_t* queue, int index, int newpriority)
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
		index = parent;
	}
	queue->priority[index] = newpriority;
	queue->handle[index] = handle;
	return;
}

void MinHeapInsertV(HeapQueueV_t* queue, GraphVertex_t* handle)
{
	if (queue->heapsize >= queue->heapsizelimit) {
		printf("\n\t| ERROR | Heap size limit reached |\n\n");
		return;
	}
	queue->priority[++queue->heapsize] = INT_MAX;
	queue->handle[queue->heapsize] = handle;
	HeapDecreaseKeyV(queue, queue->heapsize, handle->u1.key);
	return;
}

void MinHeapDeleteV(HeapQueueV_t* queue, int index)
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
	free(queue->handle[index]);
	queue->handle[index] = queue->handle[queue->heapsize--];
	MinHeapifyV(queue, index);
	return;
}

void MinHeapifyV(HeapQueueV_t* queue, int index)
{
	int left, right, smallest;
	HeapQueueVSet_t tmp;
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
			queue->priority[smallest] = tmp.priority;
			queue->handle[smallest] = tmp.handle;
			index = smallest;
		}
		else {
			break;
		}
	}
	return;
}

void FreeHeapQueueV(HeapQueueV_t* queue)
{
	free(queue->handle);
	free(queue->priority);
	free(queue);
	return;
}

void MakeSet(GraphVertex_t* vertex)
{
	vertex->parent = vertex;
	vertex->u1.rank = 0;
	return;
}

void UnionSet(GraphVertex_t* vertex1, GraphVertex_t* vertex2)
{
	LinkSet(FindSet(vertex1), FindSet(vertex2));
	return;
}

void LinkSet(GraphVertex_t* vertex1, GraphVertex_t* vertex2)
{
	if (vertex1->u1.rank > vertex2->u1.rank) {
		vertex2->parent = vertex1;
	}
	else {
		vertex1->parent = vertex2;
		if (vertex1->u1.rank == vertex2->u1.rank) {
			vertex2->u1.rank++;
		}
	}
	return;
}

GraphVertex_t* FindSet(GraphVertex_t* vertex)
{
	if (vertex != vertex->parent) {
		vertex->parent = FindSet(vertex->parent);
	}
	return vertex->parent;
}