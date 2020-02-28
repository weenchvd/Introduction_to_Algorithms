/* Chapter 22.1 | Elementary-Graph-Algorithms */
/* Chapter 22.2 | Elementary-Graph-Algorithms */
/* Chapter 22.3 | Elementary-Graph-Algorithms */
/* Chapter 22.4 | Elementary-Graph-Algorithms */
/* Chapter 22.5 | Elementary-Graph-Algorithms */

#include "ElementaryGraphAlgorithms_common.h"
#include "ElementaryGraphAlgorithms_struct.h"
#include <stdio.h>
#include <stdlib.h>

void FreeGraph(Graph_t* graph);
void FreeAdjacencyList(AdjacencyList_t* adjset);

int CreateGraph(Graph_t* graph);
void BreadthFirstSearch(Graph_t* graph, GraphVertex_t* vertex);
void DepthFirstSearch(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order);
void TopologicalSort(Graph_t* graph, TopologicalList_t* tlist, TopologicalList_t* order);
void StronglyConnectedComponents(Graph_t* graph);
void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void PrintGraph(Graph_t* graph);
void PrintBreadthFirstTree(Graph_t* graph);
void PrintDepthFirstTree(Graph_t* graph);
void PrintAdjacencyList(AdjacencyList_t* adjset);

int main(void)
{
	int i, cond, action;
	char* list = "\tList of actions: -1 (EXIT), 0 (List of actions),\n"
		"1 (CreateGraph), 2 (BreadthFirstSearch), 3 (DepthFirstSearch),\n"
		"4 (TopologicalSort), 5 (StronglyConnectedComponents), 6 (PrintGraph)\n\n";
	Graph_t graph;
	TopologicalList_t tlist;
	GraphVertex_t* vertex;
	printf(list);
	graph.vertexnum = graph.type = 0;
	graph.adjlist = NULL;
	tlist.head = NULL;
	cond = TRUE;
	while (cond) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\t| ERROR | Incorrect input |\n\n");
			continue;
		}
		switch (action) {
		case -1:
			cond = FALSE;
			break;
		case 0:
			printf(list);
			break;
		case 1:
			if (graph.vertexnum != 0) {
				printf("\n\t| ERROR | Graph already exists |\n\n");
				break;
			}
			if (CreateGraph(&graph) == FAILURE) {
				free(graph.adjlist);
				free(graph.vertlist);
				graph.vertexnum = graph.type = 0;
				graph.adjlist = graph.vertlist = NULL;
			}
			break;
		case 2:
			printf("Please enter the vertex number: ");
			if (scanf("%d", &i) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				break;
			}
			if (i < 1 || i > graph.vertexnum) {
				printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", graph.vertexnum);
				break;
			}
			vertex = graph.vertlist[i - DIFFERENCE];
			BreadthFirstSearch(&graph, vertex);
			PrintBreadthFirstTree(&graph);
			printf("Please enter the vertex number to display the path from vertex #%d to this vertex: ", vertex->number);
			if (scanf("%d", &i) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				break;
			}
			if (i < 1 || i > graph.vertexnum) {
				printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", graph.vertexnum);
				break;
			}
			printf("The path from vertex #%d to vertex #%d:\n", vertex->number, i);
			PrintPath(&graph, vertex, graph.vertlist[i - DIFFERENCE]);
			break;
		case 3:
			DepthFirstSearch(&graph, NULL, NULL);
			PrintDepthFirstTree(&graph);
			break;
		case 4:
			TopologicalSort(&graph, &tlist, NULL);
			PrintAdjacencyList(tlist.head);
			putchar('\n');
			FreeAdjacencyList(tlist.head);
			tlist.head = NULL;
			break;
		case 5:
			StronglyConnectedComponents(&graph);
			break;
		case 6:
			PrintGraph(&graph);
			break;
		default:
			printf("\n\t| ERROR | Incorrect input |\n\n");
			break;
		}
	}
	FreeGraph(&graph);
	return SUCCESS;
}

void FreeGraph(Graph_t* graph)
{
	int i;
	for (i = 0; i < graph->vertexnum; i++) {
		FreeAdjacencyList(graph->adjlist[i]);
		free(graph->vertlist[i]);
	}
	return;
}

void FreeAdjacencyList(AdjacencyList_t* adjset)
{
	AdjacencyList_t* adjsetnext;
	while (adjset != NULL) {
		adjsetnext = adjset->next;
		free(adjset);
		adjset = adjsetnext;
	}
	return;
}