#ifndef _REDBLACKTREEDOS_H
#define _REDBLACKTREEDOS_H

#include "RedBlackTreeDOS_common.h"
#include "RedBlackTreeDOS_struct.h"
#include <stdio.h>
#include <stdlib.h>

RBT_t* RBTCreateNode(int key);
void RBTInsert(RBTPointers_t* tree, RBT_t* newnode);
void RBTInsertFixup(RBTPointers_t* tree, RBT_t* node);
void RBTLeftRotate(RBTPointers_t* tree, RBT_t* node);
void RBTRightRotate(RBTPointers_t* tree, RBT_t* node);
void RBTDelete(RBTPointers_t* tree, RBT_t* delnode);
void RBTTransplant(RBTPointers_t* tree, RBT_t* receiver, RBT_t* source);
void RBTOSDecreaseSize(RBTPointers_t* tree, RBT_t* node);
void RBTDeleteFixup(RBTPointers_t* tree, RBT_t* node);
RBT_t* RBTMinimum(RBTPointers_t* tree, RBT_t* root);
RBT_t* RBTOSSelectRecursive(RBT_t* root, int rank);
RBT_t* RBTOSSelectIterative(RBT_t* root, int rank);
int RBTOSRank(RBTPointers_t* tree, RBT_t* node);
int RBTOSKeyRank(RBTPointers_t* tree, int key);
RBT_t* RBTSearch(RBTPointers_t* tree, int key);
void RBTPrintInorder(RBTPointers_t* tree, RBT_t* root, int hcounter, int bhcounter);
void RBTPrintPreorder(RBTPointers_t* tree, RBT_t* root);
void RBTPrintPostorder(RBTPointers_t* tree, RBT_t* root);

#endif