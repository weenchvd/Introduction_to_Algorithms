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
int GenericPushRelabel(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void InitializePreflow(Graph_t* graph, GraphVertex_t* source);
void PushAll(Graph_t* graph, int* condition);
void PushFlowAlongOriginalEdge(GraphEdge_t* originalEdge, int residualCapacity);
void PushFlowAlongResidualEdge(GraphEdge_t* originalEdge, int residualCapacity);
void RelabelAll(Graph_t* graph, GraphVertex_t* destination, int* condition);
void RelabelVertex(GraphVertex_t* vertex, int minHeight);
int RelabelToFront(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void Discharge(GraphVertex_t* vertex, SinglyLLSetPtr_t** neighborList);
SinglyLLSetPtr_t** CreateNeighborList(Graph_t* graph);
void FreeNeighborList(Graph_t* graph, SinglyLLSetPtr_t** neighborList);
SinglyLLSetPtr_t* CreateVertexList(Graph_t* graph, GraphVertex_t* source, GraphVertex_t* destination);
void FreeVertexList(SinglyLLSetPtr_t* vertexList);
SinglyLLSetPtr_t* SinglyLinkedListCreateSet();
SinglyLLSetPtr_t* SinglyLinkedListSearchSet(SinglyLLSetPtr_t** head, void* ptr);
SinglyLLSetPtr_t** SinglyLinkedListGetPointerToNextPointerOfPreviousSet(SinglyLLSetPtr_t** head, SinglyLLSetPtr_t* set);
void SinglyLinkedListInsertSet(SinglyLLSetPtr_t** head, SinglyLLSetPtr_t* set);
void SinglyLinkedListExtractSet(SinglyLLSetPtr_t** head, SinglyLLSetPtr_t* set);

#endif