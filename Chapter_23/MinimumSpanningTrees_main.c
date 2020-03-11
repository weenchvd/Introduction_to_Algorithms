/* Chapter 23.1 | Minimum-Spanning-Trees */
/* Chapter 23.2 | Minimum-Spanning-Trees */

#include "MinimumSpanningTrees.h"
#include "MinimumSpanningTrees.h"
#include <stdio.h>
#include <stdlib.h>

void FreeGraph(Graph_t* graph);
void FreeAdjacencyList(AdjacencyList_t* adjset);

int CreateGraph(Graph_t* graph);
int GenericMST(Graph_t* graph, Queue_t* mst);
int MSTKruskal(Graph_t* graph, Queue_t* mst);
int MSTPrim(Graph_t* graph, GraphVertex_t* root, Queue_t* mst);
void PrintGraph(Graph_t* graph);

int main(void)
{
	int i, cond, action;
	char* list = "\tList of actions: -1 (EXIT), 0 (List of actions),\n"
		"1 (CreateGraph), 2 (GenericMST), 3 (MSTKruskal), 4 (MSTPrim)\n"
		"5 (PrintGraph)\n\n";
	Graph_t graph;
	Queue_t mst;
	GraphVertex_t* vertex;
	printf(list);
	graph.vertexnum = graph.type = 0;
	graph.adjlist = NULL;
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
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if (GenericMST(&graph, &mst) == FAILURE) {
				cond = FALSE;
			}
			break;
		case 3:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if (MSTKruskal(&graph, &mst) == FAILURE) {
				cond = FALSE;
			}
			break;
		case 4:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if (MSTPrim(&graph, graph.vertlist[0], &mst) == FAILURE) {
				cond = FALSE;
			}
			break;
		case 5:
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