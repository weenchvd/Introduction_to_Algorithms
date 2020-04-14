/* Chapter 26.2 | Maximum-Flow */
/* Chapter 26.4 | Maximum-Flow */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MaximumFlow_common.h"
#include "MaximumFlow_struct.h"
#include "MaximumFlow_main.h"
#include "MaximumFlow.h"


int main(void)
{
	int i, j, n, cond, action;
	char* list = "\tList of actions: -1 (EXIT), 0 (List of actions),\n"
		"1 (CreateGraph), 2 (EdmondsKarp), 3 (GenericPushRelabel), 4 ()\n"
		"5 (PrintGraph)\n\n";
	Graph_t graph;
	printf(list);
	graph.nVertices = graph.nEdges = graph.graphType = 0;
	graph.adjList = graph.vertList = graph.edgeList = graph.adjMatrix = graph.auxVertex = graph.auxAdjList = NULL;
	cond = true;
	while (cond) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\t| ERROR | Incorrect input |\n\n");
			continue;
		}
		switch (action) {
		case -1:
			cond = false;
			break;
		case 0:
			printf(list);
			break;
		case 1:
			if (graph.nVertices != 0) {
				printf("\n\t| ERROR | Graph already exists |\n\n");
				break;
			}
			if (CreateGraph(&graph) == FAILURE) {
				free(graph.adjList);
				free(graph.vertList);
				free(graph.edgeList);
				if (graph.adjMatrix != NULL) {
					free(graph.adjMatrix->value);
				}
				free(graph.adjMatrix);
				graph.nVertices = graph.nEdges = graph.graphType = 0;
				graph.adjList = graph.vertList = graph.edgeList = graph.adjMatrix = graph.auxVertex = graph.auxAdjList = NULL;
			}
			break;
		case 2:
			if (graph.nVertices == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			printf("  Please enter the source vertex number: ");
			if (scanf("%d", &i) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				break;
			}
			if (i < 1 || i > graph.nVertices) {
				printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", graph.nVertices);
				break;
			}
			printf("  Please enter the sink vertex number: ");
			if (scanf("%d", &j) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				break;
			}
			if (j < 1 || j > graph.nVertices) {
				printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", graph.nVertices);
				break;
			}
			if ((n = EdmondsKarp(&graph, graph.vertList[i], graph.vertList[j])) == FAILURE) {
				break;
			}
			printf("    The flow from source vertex #%d to sink vertex #%d: %d\n", i, j, n);
			break;
		case 3:
			if (graph.nVertices == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			printf("  Please enter the source vertex number: ");
			if (scanf("%d", &i) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				break;
			}
			if (i < 1 || i > graph.nVertices) {
				printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", graph.nVertices);
				break;
			}
			printf("  Please enter the sink vertex number: ");
			if (scanf("%d", &j) <= 0) {
				printf("\n\t| ERROR | Incorrect input |\n\n");
				break;
			}
			if (j < 1 || j > graph.nVertices) {
				printf("\n\t| ERROR | The number must be from 1 to %d |\n\n", graph.nVertices);
				break;
			}
			n = GenericPushRelabel(&graph, graph.vertList[i], graph.vertList[j]);
			printf("    The flow from source vertex #%d to sink vertex #%d: %d\n", i, j, n);
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
	for (i = FIRSTVERTEXNUMBER; i < graph->nVertices + FIRSTVERTEXNUMBER; i++) {
		FreeAdjacencyList(graph->adjList[i]);
		free(graph->vertList[i]);
	}
	for (i = 0; i < graph->nEdges; i++) {
		free(graph->edgeList[i]);
	}
	FreeAdjacencyMatrix(graph->adjMatrix);
	return;
}

void FreeAdjacencyList(AdjLLSet_t* adjSet)
{
	AdjLLSet_t* adjsetnext;
	while (adjSet != NULL) {
		adjsetnext = adjSet->next;
		free(adjSet);
		adjSet = adjsetnext;
	}
	return;
}