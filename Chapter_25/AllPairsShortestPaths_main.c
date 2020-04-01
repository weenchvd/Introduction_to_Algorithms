/* Chapter 25.1 | All-Pairs-Shortest-Paths */
/* Exercise 25.1-7 | All-Pairs-Shortest-Paths */
/* Chapter 25.2 | All-Pairs-Shortest-Paths */
/* Exercise 25.2-3 | All-Pairs-Shortest-Paths */
/* Exercise 25.2-4 | All-Pairs-Shortest-Paths */
/* Exercise 25.2-6 | All-Pairs-Shortest-Paths */
/* Chapter 25.3 | All-Pairs-Shortest-Paths */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AllPairsShortestPaths_common.h"
#include "AllPairsShortestPaths_struct.h"


void FreeGraph(Graph_t* graph);
void FreeAdjacencyList(AdjacencyList_t* adjset);

int CreateGraph(Graph_t* graph);
void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void PrintAllPairsShortestPath(AdjacencyMatrix_t* predSubgraph, int i, int j);
void PrintGraph(Graph_t* graph);
void FreeAdjacencyMatrix(AdjacencyMatrix_t* adjmatrix);
AdjPredSet_t* SlowAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight);
AdjacencyMatrix_t* FasterAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight);
AdjPredSet_t* FloydWarshall(const AdjacencyMatrix_t* edgeWeight);
bool GetBitValueInTransitiveClosureMatrix(TClosure_t* clos, int i, int j);
TClosure_t* TransitiveClosure(AdjacencyMatrix_t* edgeWeight);
void FreeTransitiveClosureMatrix(TClosure_t* clos);
AdjacencyMatrix_t* Johnson(Graph_t* graph);


int main(void)
{
	int i, j, n, cond, action;
	char* list = "\tList of actions: -1 (EXIT), 0 (List of actions),\n"
		"1 (CreateGraph), 2 (SlowAllPairsShortestPaths), 3 (FasterAllPairsShortestPaths), 4 (FloydWarshall)\n"
		"5 (TransitiveClosure), 6 (Johnson), 7 (PrintGraph)\n\n";
	Graph_t graph;
	GraphVertex_t* vertex;
	AdjacencyMatrix_t* shortestPath;
	AdjPredSet_t* adjpred;
	TClosure_t* clos;
	printf(list);
	graph.vertexnum = graph.edgenum = graph.type = 0;
	graph.adjlist = graph.vertlist = graph.edgelist = graph.adjmatrix = graph.auxVertex = graph.auxAdjList = NULL;
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
			if ((adjpred = SlowAllPairsShortestPaths(graph.adjmatrix)) == NULL) {
				break;
			}
			n = adjpred->shortestPath->rows;
			for (i = 1; i <= graph.vertexnum; i++) {
				for (j = 1; j <= graph.vertexnum; j++) {
					if (adjpred->shortestPath->weight[item(i, j, n)] != INFINITY) {
						printf("  The path from vertex #%d to vertex #%d with the weight %d: ",
							i, j, adjpred->shortestPath->weight[item(i, j, n)]);
					}
					else {
						printf("  The path from vertex #%d to vertex #%d with the weight \'INFINITY\': ", i, j);
					}
					PrintAllPairsShortestPath(adjpred->predSubgraph, i, j);
					putchar('\n');
				}
			}
			FreeAdjacencyMatrix(adjpred->shortestPath);
			FreeAdjacencyMatrix(adjpred->predSubgraph);
			free(adjpred);
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
			FreeAdjacencyMatrix(shortestPath);
			break;
		case 4:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if ((adjpred = FloydWarshall(graph.adjmatrix)) == NULL) {
				break;
			}
			n = adjpred->shortestPath->rows;
			if (adjpred->isNegativeWeightCycle == false) {
				printf("  The graph does not contain a negative-weight cycle\n");
				for (i = 1; i <= graph.vertexnum; i++) {
					for (j = 1; j <= graph.vertexnum; j++) {
						if (adjpred->shortestPath->weight[item(i, j, n)] != INFINITY) {
							printf("  The path from vertex #%d to vertex #%d with the weight %d: ",
								i, j, adjpred->shortestPath->weight[item(i, j, n)]);
						}
						else {
							printf("  The path from vertex #%d to vertex #%d with the weight \'INFINITY\': ", i, j);
						}
						PrintAllPairsShortestPath(adjpred->predSubgraph, i, j);
						putchar('\n');
					}
				}
			}
			else {
				printf("  The graph contain a negative-weight cycle\n");
			}
			FreeAdjacencyMatrix(adjpred->shortestPath);
			FreeAdjacencyMatrix(adjpred->predSubgraph);
			free(adjpred);
			break;
		case 5:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if ((clos = TransitiveClosure(graph.adjmatrix)) == NULL) {
				break;
			}
			for (i = 1; i <= graph.vertexnum; i++) {
				for (j = 1; j <= graph.vertexnum; j++) {
					printf("  The path from vertex #%d to vertex #%d: %s\n",
						i, j, (GetBitValueInTransitiveClosureMatrix(clos, i, j) == true) ? "TRUE" : "    FALSE");
				}
			}
			FreeTransitiveClosureMatrix(clos);
			break;
		case 6:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			if ((shortestPath = Johnson(&graph)) == NULL) {
				break;
			}
			for (i = 1; i <= graph.vertexnum; i++) {
				for (j = 1; j <= graph.vertexnum; j++) {
					printf("  The path from vertex #%d to vertex #%d with the weight %d\n",
						i, j, shortestPath->weight[item(i, j, shortestPath->rows)]);
				}
			}
			FreeAdjacencyMatrix(shortestPath);
			break;
		case 7:
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