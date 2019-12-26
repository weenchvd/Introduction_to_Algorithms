#ifndef _GREEDYSTRATEGYELEMENTS_H
#define _GREEDYSTRATEGYELEMENTS_H

#include "GreedyStrategyElements_common.h"
#include "GreedyStrategyElements_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define vtitem(i, j, n) ((n) * ((i) - 1) + ((j) - 1))
#define stitem(i, j, n) ((n) * ((n) - (i)) + ((n) - (j)))
#define wtitem(i, j, n) ((n) * ((i) - 1) + ((j) - 1))

enum DirectionType { JMINUS1 = -1, IPLUS1 = -2 };

void ZeroOneKnapsackConstruct(KI_t* items);
void ZeroOneKnapsackSolution(KI_t* items, KATables_t* t);
void ZeroOneKnapsackSolutionPrint(KATables_t* t, int i, int j, int n);

#endif