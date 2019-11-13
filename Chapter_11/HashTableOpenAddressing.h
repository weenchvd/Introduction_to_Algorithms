#ifndef _HASHTABLEOPENADDRESSING_H
#define _HASHTABLEOPENADDRESSING_H

#include "HashTableOpenAddressing_common.h"
#include "HashTableOpenAddressing_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define M2 700
#define HASH(k,i) ((k % HASHTABLESIZE) + i * (1 + (k % M2))) % HASHTABLESIZE

int HashInsert(int* ht, int key);
int HashSearch(int* ht, int key);
int HashDelete(int* ht, int key);
void HashPrint(int* ht, int size);

#endif