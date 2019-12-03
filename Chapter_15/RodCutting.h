#ifndef _RODCUTTING_H
#define _RODCUTTING_H

#include "RodCutting_common.h"
#include "RodCutting_struct.h"
#include <stdio.h>
#include <stdlib.h>

int MemoizedCutRod(int* price, int n);
int MemoizedCutRodAux(int* price, int* rev, int n);
int BottomUpCutRod(int* price, int n);
void PrintCutRodSolution(int* price, int n);
void ExtendedBottomUpCutRod(int* price, int* rev, int* cutsize, int n);
void PrintCutRodSolutionNonFreeCut(int* price, int n, int cutcost);
void ExtendedBottomUpCutRodNonFreeCut(int* price, int* rev, int* cutsize, int n, int cutcost);

#endif