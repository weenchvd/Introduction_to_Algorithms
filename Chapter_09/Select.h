#ifndef _SELECT_H
#define _SELECT_H

#include "Select_common.h"
#include <stdio.h>
#include <stdlib.h>

#define GROUPSIZE 5

enum ReturnTypeSelect { ERROR = INT_MIN };

int Select(int* a, int first, int last, int i);
int FindMedian(int* a, int first, int last);
int PartitionM(int* a, int first, int last, int target);

#endif