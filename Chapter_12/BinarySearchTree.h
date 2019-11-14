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

#endif