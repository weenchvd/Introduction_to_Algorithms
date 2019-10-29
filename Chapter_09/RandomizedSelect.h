#ifndef _COUNTINGSORT_H
#define _COUNTINGSORT_H

#include "RandomizedSelect_common.h"
#include <stdlib.h>

#define RANDOM(a, b) rand() % (b - a + 1) + a

int RandomizedSelect(int* a, int first, int last, int i);
int RandomizedSelectI(int* a, int first, int last, int i);
int RandomizedPartition(int* a, int first, int last);
int Partition(int* a, int first, int last);

#endif