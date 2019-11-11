#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include "BinaryTree_common.h"
#include "BinaryTree_struct.h"
#include <stdio.h>
#include <stdlib.h>

enum PathType { ENDOFTREE, LEFT, RIGHT, DOWN, UP};

void BinaryTreeInsert(BinaryTree_t** root, int key, int* number);
void BinaryTreePrint(BinaryTree_t* root, int number);
void BinaryTreePrintRecursive(BinaryTree_t* root);

#endif