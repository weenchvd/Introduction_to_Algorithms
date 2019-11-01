#ifndef _STACKQUEUE_H
#define _STACKQUEUE_H

#include "StackQueue_common.h"
#include "StackQueue_struct.h"
#include <stdio.h>
#include <stdlib.h>

enum ReturnTypeStackQueue { ERROR = INT_MIN };

void Push(StackSet_t* s, int x);
int Pop(StackSet_t* s);
void Enqueue(QueueSet_t* q, int x);
int Dequeue(QueueSet_t* q);

inline int StackEmpty(StackSet_t* s)
{
	return (s->top == ARRAYSTARTINDEX - 1) ? TRUE : FALSE;
}

inline int StackFull(StackSet_t* s)
{
	return (s->top == STACKSIZE - 1) ? TRUE : FALSE;
}

inline int QueueEmpty(QueueSet_t* q)
{
	return (q->head == q->tail) ? TRUE : FALSE;
}

inline int QueueFull(QueueSet_t* q)
{
	return (q->head == ((q->tail + 1 == QUEUESIZE) ? ARRAYSTARTINDEX : q->tail + 1)) ? TRUE : FALSE;
}

#endif