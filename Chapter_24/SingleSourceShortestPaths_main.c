/* Chapter 24.1 | Single-Source-Shortest-Paths */

#include "SingleSourceShortestPaths_common.h"
#include "SingleSourceShortestPaths_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void FreeGraph(Graph_t* graph);
void FreeAdjacencyList(AdjacencyList_t* adjset);

int CreateGraph(Graph_t* graph);
void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void PrintGraph(Graph_t* graph);
bool BellmanFord(Graph_t* graph, GraphVertex_t* source);

int main(void)
{
	int i, cond, action;
	char* list = "\tList of actions: -1 (EXIT), 0 (List of actions),\n"
		"1 (CreateGraph), 2 (BellmanFord), 3 (), 4 ()\n"
		"5 (PrintGraph)\n\n";
	Graph_t graph;
	GraphVertex_t* vertex;
	printf(list);
	graph.vertexnum = graph.edgenum = graph.type = 0;
	graph.adjlist = graph.vertlist = graph.edgelist = NULL;
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
				graph.vertexnum = graph.edgenum = graph.type = 0;
				graph.adjlist = graph.vertlist = graph.edgelist = NULL;
			}
			break;
		case 2:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
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
			if (BellmanFord(&graph, vertex) == true) {
				printf("The graph does not contain a negative-weight cycle that is reachable from the source\n");
				for (i = 0; i < graph.vertexnum; i++) {
					printf("The path from vertex #%d to vertex #%d with the weight %d:\n",
						vertex->number, graph.vertlist[i]->number, graph.vertlist[i]->distance);
					PrintPath(&graph, vertex, graph.vertlist[i]);
				}
			}
			else {
				printf("The graph contains a negative-weight cycle that is reachable from the source\n");
			}
			break;
		case 3:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			break;
		case 4:
			if (graph.vertexnum == 0) {
				printf("\n\t| ERROR | Graph does not exist |\n\n");
				break;
			}
			/*if (MSTPrim(&graph, graph.vertlist[0], &mst) == FAILURE) {
				cond = false;
			}*/
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