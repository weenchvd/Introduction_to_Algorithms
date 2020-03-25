#ifndef _ALLPAIRSSHORTESTPATHS_H
#define _ALLPAIRSSHORTESTPATHS_H

#include "AllPairsShortestPaths_common.h"
#include "AllPairsShortestPaths_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define INFINITY INT_MAX
#define INFINITYMINUS INT_MIN
#define NIL 0


int CreateGraph(Graph_t* graph);
GraphVertex_t* CreateVertex();
AdjacencyList_t* CreateAdjacencySet();
int IsVertexInAdjacencyList(AdjacencyList_t* adjset, GraphVertex_t* vertex);
void PrintPath(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void PrintAllPairsShortestPath(AdjacencyMatrix_t* predSubgraph, int i, int j);
void PrintGraph(Graph_t* graph);
void PrintVertex(GraphVertex_t* vertex);
void PrintAdjacencyList(AdjacencyList_t* adjset);
int WeightSummarization(int weight1, int weight2);
AdjacencyMatrix_t* CreateAdjacencyMatrix(const int rows);
AdjacencyMatrix_t* MakeCopyAdjacencyMatrix(const AdjacencyMatrix_t* source);
void FreeAdjacencyMatrix(AdjacencyMatrix_t* adjmatrix);
AdjacencyMatrix_t* ExtendShortestPaths(AdjacencyMatrix_t* shortestPath, AdjacencyMatrix_t* edgeWeight);
AdjPredSet_t* ExtendShortestPathsAndPredecessorSubgraph(AdjPredSet_t* adjpred, AdjacencyMatrix_t* edgeWeight);
AdjPredSet_t* SlowAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight);
AdjacencyMatrix_t* FasterAllPairsShortestPaths(const AdjacencyMatrix_t* edgeWeight);


void FreeAdjacencyList(AdjacencyList_t* adjset);

#endif