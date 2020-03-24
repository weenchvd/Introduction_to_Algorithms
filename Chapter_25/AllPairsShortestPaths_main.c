/* Chapter 25.1 | All-Pairs-Shortest-Paths */

#include "AllPairsShortestPaths_common.h"
#include "AllPairsShortestPaths_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void FreeGraph(Graph_t* graph);
void FreeAdjacencyList(AdjacencyList_t* adjset);

int CreateGraph(Graph_t* graph);
void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void PrintAllPairsShortestPath(AdjacencyMatrix_t* predSubgraph, int i, int j);
void PrintGraph(Graph_t* graph);
AdjacencyMatrix_t* SlowAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight);
AdjacencyMatrix_t* FasterAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight);


int main(void)
{
	int i, j, cond, action;
	char* list = "\tList of actions: -1 (EXIT), 0 (List of actions),\n"
		"1 (CreateGraph), 2 (SlowAllPairsShortestPaths), 3 (FasterAllPairsShortestPaths), 4 ()\n"
		"5 (PrintGraph)\n\n";
	Graph_t graph;
	GraphVertex_t* vertex;
	AdjacencyMatrix_t* shortestPath;
	printf(list);
	graph.vertexnum = graph.edgenum = graph.type = 0;
	graph.adjlist = graph.vertlist = graph.edgelist = graph.adjmatrix = NULL;
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
			if (graph.vertexnum != 0) {
				printf("\n\t| ERROR | Graph already exists |\n\n");
				break;
			}
			if (CreateGraph(&graph) == FAILURE) {
				free(graph.adjlist);
				free(graph.vertlist);
				free(graph.edgelist);
				if (graph.adjmatrix != NULL) {
					free(graph.adjmatrix->weight);
				}
				free(graph.adjmatrix);
				graph.vertexnum = graph.edgenum = graph.type = 0;
				graph.adjlist = graph.vertlist = graph.edgelist = graph.adjmatrix = NULL;
			}
			break;
		case 2:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if ((shortestPath = SlowAllPairsShortestPaths(graph.adjmatrix)) == NULL) {
				break;
			}
			for (i = 1; i <= graph.vertexnum; i++) {
				for (j = 1; j <= graph.vertexnum; j++) {
					printf("  The path from vertex #%d to vertex #%d with the weight %d\n",
						i, j, shortestPath->weight[item(i, j, shortestPath->rows)]);
				}
			}
			break;
		case 3:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if ((shortestPath = FasterAllPairsShortestPaths(graph.adjmatrix)) == NULL) {
				break;
			}
			for (i = 1; i <= graph.vertexnum; i++) {
				for (j = 1; j <= graph.vertexnum; j++) {
					printf("  The path from vertex #%d to vertex #%d with the weight %d\n",
						i, j, shortestPath->weight[item(i, j, shortestPath->rows)]);
				}
			}
			break;
		case 4:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
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
	for (i = 0; i < graph->edgenum; i++) {
		free(graph->edgelist[i]);
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