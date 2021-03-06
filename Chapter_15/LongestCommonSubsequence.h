﻿#ifndef _LONGESTCOMMONSUBSEQUENCE_H
#define _LONGESTCOMMONSUBSEQUENCE_H

#include "LongestCommonSubsequence_common.h"
#include "LongestCommonSubsequence_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define ctitem(i, j, n) (n + 1) * i + j
#define btitem(i, j, n) n * (i - 1) + (j - 1)

enum DirectionType { UPLEFT = '1', UP = 'U', LEFT = 'L' };

void LCSFindAndPrint(Sequence_t* x, Sequence_t* y);
void LCSLength(Sequence_t* x, Sequence_t* y, int** ctable, char** btable);
void LCSPrint(Sequence_t* y, char* bt, int i, int j);
void PrintStrings(Sequence_t* x, Sequence_t* y);
void LCSFindAndPrintWithoutBtable(Sequence_t* x, Sequence_t* y);
void LCSLengthWithoutBtable(Sequence_t* x, Sequence_t* y, int** ctable);
void LCSPrintWithoutBtable(Sequence_t* x, Sequence_t* y, int* ct, int i, int j);
void LCSFindAndPrintWithoutBtableRecursive(Sequence_t* x, Sequence_t* y);
void LCSLengthWithoutBtableRecursive(Sequence_t* x, Sequence_t* y, int** ctable);
int LCSMemoizedLengthWithoutBtableRecursive(Sequence_t* x, Sequence_t* y, int* ct, int i, int j);
void LCSFindAndPrintLength(Sequence_t* x, Sequence_t* y);
int LCSLengthMinimal(Sequence_t* x, Sequence_t* y);

#endif