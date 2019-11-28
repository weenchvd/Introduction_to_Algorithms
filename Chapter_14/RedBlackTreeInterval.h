#ifndef _REDBLACKTREEINTERVAL_H
#define _REDBLACKTREEINTERVAL_H

#include "RedBlackTreeInterval_common.h"
#include "RedBlackTreeInterval_struct.h"
#include <stdio.h>
#include <stdlib.h>

RBT_t* RBTCreateNode(Interval_t i);
void RBTInsert(RBTPointers_t* tree, RBT_t* newnode);
void RBTInsertFixup(RBTPointers_t* tree, RBT_t* node);
void RBTLeftRotate(RBTPointers_t* tree, RBT_t* node);
void RBTRightRotate(RBTPointers_t* tree, RBT_t* node);
void RBTDelete(RBTPointers_t* tree, RBT_t* delnode);
void RBTTransplant(RBTPointers_t* tree, RBT_t* receiver, RBT_t* source);
void RBTDeleteFixup(RBTPointers_t* tree, RBT_t* node);
int RBTIIntervalMaximumOf(RBTPointers_t* tree, RBT_t* node);
void RBTIRecalculateMaxUpper(RBTPointers_t* tree, RBT_t* node);
RBT_t* RBTMinimum(RBTPointers_t* tree, RBT_t* root);
RBT_t* RBTMaximum(RBTPointers_t* tree, RBT_t* root);
RBT_t* RBTSuccessor(RBTPointers_t* tree, RBT_t* root);
RBT_t* RBTPredecessor(RBTPointers_t* tree, RBT_t* root);
RBT_t* RBTISearch(RBTPointers_t* tree, Interval_t i);
void RBTPrintInorder(RBTPointers_t* tree, RBT_t* root, int hcounter, int bhcounter);
void RBTPrintNode(RBTPointers_t* tree, RBT_t* node);

#endif