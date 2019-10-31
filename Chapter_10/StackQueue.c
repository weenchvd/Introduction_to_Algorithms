#include "StackQueue.h"

int StackEmpty(StackSet_t* s)
{
	return (s->top == 0) ? TRUE : FALSE;
}

void Push(StackSet_t* s, int x)
{
	s->stack[++s->top] = x;
	return;
}

int Pop(StackSet_t* s)
{
	if (StackEmpty(s)) {
		printf("\n\n\t| ERROR | Stack underflow |\n");
		return INT_MIN;
	}
	else {
		return s->stack[s->top--];
	}
}

void Enqueue(QueueSet_t* q, int x)
{
	q->queue[q->tail] = x;
	q->tail = (q->tail == QUEUESIZE - 1) ? ARRAYSTARTINDEX : q->tail + 1;
	return;
}

int Dequeue(QueueSet_t* q)
{
	int x;
	x = q->queue[q->head];
	q->head = (q->head == QUEUESIZE - 1) ? ARRAYSTARTINDEX : q->head + 1;
	return x;
}