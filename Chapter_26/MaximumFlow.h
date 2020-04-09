#ifndef _MAXIMUMFLOW_H
#define _MAXIMUMFLOW_H

int CreateGraph(Graph_t* graph);
GraphVertex_t* CreateVertex();
GraphEdge_t* CreateEdge();
AdjLLSet_t* CreateAdjacencyLLSet();
int IsVertexInAdjacencyList(AdjLLSet_t* adjSet, GraphVertex_t* vertex);
AdjacencyMatrix_t* CreateAdjacencyMatrix(const int nRows);
AdjacencyMatrix_t* MakeCopyAdjacencyMatrix(const AdjacencyMatrix_t* source);
void FreeAdjacencyMatrix(AdjacencyMatrix_t* adjMatrix);
void PrintGraph(Graph_t* graph);
void PrintVertex(GraphVertex_t* vertex);
void PrintAdjacencyList(AdjLLSet_t* adjSet);
int WeightSummarization(int weight1, int weight2);
int EdmondsKarp(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
Graph_t* MakeResidualGraph(Graph_t* sourceGraph);
void FreeResidualGraph(Graph_t* residualGraph);
void BreadthFirstSearch(Graph_t* graph, GraphVertex_t* sourceVertex);
void Enqueue(Queue_t* q, void* x);
void* Dequeue(Queue_t* q);
inline int IsQueueEmpty(Queue_t* q);
inline int IsQueueFull(Queue_t* q);

#endif