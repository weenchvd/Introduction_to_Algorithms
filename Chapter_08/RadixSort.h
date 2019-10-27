#ifndef _RADIXSORT_H
#define _RADIXSORT_H

#include "RadixSort_common.h"

#define NUMBERSYSTEM 2
#define NUMBEROFBITININTEGER sizeof(int) * 8

void RadixSort(int* a, int* b, int size);

#endif