#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include "BinarySearchTree_common.h"
#include "BinarySearchTree_struct.h"
#include <stdio.h>
#include <stdlib.h>

void BinarySearchTreeInsert(BinarySearchTree_t** root, int key, int* number);
void BinarySearchTreePrintWithStack(BinarySearchTree_t* root, int number);
void BinarySearchTreePrintWithPointer(BinarySearchTree_t* root);
void BinarySearchTreePrintRecursiveInorder(BinarySearchTree_t* root);
void BinarySearchTreePrintRecursivePreorder(BinarySearchTree_t* root);
void BinarySearchTreePrintRecursivePostorder(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeSearchRecursive(BinarySearchTree_t* root, int key);
BinarySearchTree_t* BinarySearchTreeSearchIterative(BinarySearchTree_t* root, int key);
BinarySearchTree_t* BinarySearchTreeMinimumIterative(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeMinimumRecursive(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeMaximumIterative(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeMaximumRecursive(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeSuccessor(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreePredecessor(BinarySearchTree_t* root);

#endif