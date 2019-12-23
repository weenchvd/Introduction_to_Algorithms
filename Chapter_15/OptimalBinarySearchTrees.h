#ifndef _OPTIMALBINARYSEARCHTREES_H
#define _OPTIMALBINARYSEARCHTREES_H

#include "OptimalBinarySearchTrees_common.h"
#include "OptimalBinarySearchTrees_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define etitem(i, j, n) (n + 1) * (i - 1) + j
#define rtitem(i, j, n) (n + 1) * (n - i + 1) + (n - j)
#define wtitem(i, j, n) (n + 1) * (i - 1) + j

enum DirectionType { LEFT, RIGHT };

void BSTOptimalConstruct(BSTPr_t* pr);
void BSTOptimal(BSTPr_t* pr, BSTATables_t* t);
void BSTOptimalPrint(BSTPr_t* pr, BSTATables_t* t, int i, int j);
void BSTOptimalPrint2(BSTPr_t* pr, BSTATables_t* t, int i, int j, int direction, int last);

#endif