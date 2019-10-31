#ifndef _STACKQUEUE_H
#define _STACKQUEUE_H

#include "StackQueue_common.h"
#include "StackQueue_struct.h"
#include <stdio.h>
#include <stdlib.h>

int StackEmpty(StackSet_t* s);
void Push(StackSet_t* s, int x);
int Pop(StackSet_t* s);
void Enqueue(QueueSet_t* q, int x);
int Dequeue(QueueSet_t* q);

#endif