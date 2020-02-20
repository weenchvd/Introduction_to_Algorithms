/* Chapter 22.1 | Elementary-Graph-Algorithms */
/* Chapter 22.2 | Elementary-Graph-Algorithms */

#include "ElementaryGraphAlgorithms_common.h"
#include "ElementaryGraphAlgorithms_struct.h"
#include <stdio.h>
#include <stdlib.h>

int CreateGraph(GraphSet_t* graph);
void BreadthFirstSearch(GraphSet_t* graph, GraphVertex_t* vertex);
void PrintGraph(GraphSet_t* graph);
void PrintBreadthFirstTree(GraphSet_t* graph);
void FreeGraph(GraphSet_t* graph);

int main(void)
{
	int i, cond, action;
	char* list = "\tList of action: -1 (EXIT), 0 (List of action),\n"
		"1 (CreateGraph), 2 (BreadthFirstSearch), 3 (---------),\n"
		"4 (PrintGraph), 5 (----------), 6 (-----------)\n"
		"7 (------------)\n\n";
	GraphSet_t graph;
	GraphVertex_t* vertex;
	//AdjacencyListSet_t* adjset;
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
			break;
		case 3:

			break;
		case 4:
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

void FreeGraph(GraphSet_t* graph)
{
	int i;
	AdjacencyListSet_t* adjset, * adjsetnext;
	for (i = 0; i < graph->vertexnum; i++) {
		for (adjset = graph->adjlist[i]; adjset != NULL; adjset = adjsetnext) {
			adjsetnext = adjset->next;
			free(adjset);
		}
		free(graph->vertlist[i]);
	}
	return;
}