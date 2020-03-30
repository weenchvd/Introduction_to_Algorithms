#ifndef _ALLPAIRSSHORTESTPATHS_H
#define _ALLPAIRSSHORTESTPATHS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "AllPairsShortestPaths_common.h"
#include "AllPairsShortestPaths_struct.h"


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
AdjPredSet_t* FloydWarshall(const AdjacencyMatrix_t* edgeWeight);
void SetBitValueInTransitiveClosureMatrix(TClosure_t* clos, int i, int j, int value);
bool GetBitValueInTransitiveClosureMatrix(TClosure_t* clos, int i, int j);
TClosure_t* TransitiveClosure(AdjacencyMatrix_t* edgeWeight);
TClosure_t* CreateTransitiveClosureMatrix(const int rows);
void FreeTransitiveClosureMatrix(TClosure_t* clos);


void FreeAdjacencyList(AdjacencyList_t* adjset);

#endif