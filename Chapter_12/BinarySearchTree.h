#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include "BinarySearchTree_common.h"
#include "BinarySearchTree_struct.h"
#include <stdio.h>
#include <stdlib.h>

BST_t* BSTCreateNode(int key, int* number);
void BSTInsertIterative(BST_t** root, BST_t* newnode);
void BSTInsertRecursive(BST_t** root, BST_t* newnode);
void BSTPrintWithStack(BST_t* root, int number);
void BSTPrintWithPointer(BST_t* root);
void BSTPrintRecursiveInorder(BST_t* root);
void BSTPrintRecursivePreorder(BST_t* root);
void BSTPrintRecursivePostorder(BST_t* root);
BST_t* BSTSearchRecursive(BST_t* root, int key);
BST_t* BSTSearchIterative(BST_t* root, int key);
BST_t* BSTMinimumIterative(BST_t* root);
BST_t* BSTMinimumRecursive(BST_t* root);
BST_t* BSTMaximumIterative(BST_t* root);
BST_t* BSTMaximumRecursive(BST_t* root);
BST_t* BSTSuccessor(BST_t* root);
BST_t* BSTPredecessor(BST_t* root);
void BSTTransplant(BST_t** root, BST_t* receiver, BST_t* source);
void BSTDelete(BST_t** root, BST_t* node);

#endif