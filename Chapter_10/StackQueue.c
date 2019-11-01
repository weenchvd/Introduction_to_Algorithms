#include "StackQueue.h"

void Push(StackSet_t* s, int x)
{
	if (StackFull(s)) {
		printf("\n\n\t| ERROR | Stack overflow |\n");
	}
	else {
		s->stack[++s->top] = x;
	}
	return;
}

int Pop(StackSet_t* s)
{
	if (StackEmpty(s)) {
		printf("\n\n\t| ERROR | Stack underflow |\n");
		return ERROR;
	}
	return s->stack[s->top--];
}

void Enqueue(QueueSet_t* q, int x)
{
	if (QueueFull(q)) {
		printf("\n\n\t| ERROR | Queue overflow |\n");
	}
	else {
		q->queue[q->tail] = x;
		q->tail = (q->tail == QUEUESIZE - 1) ? ARRAYSTARTINDEX : q->tail + 1;
	}
	return;
}

int Dequeue(QueueSet_t* q)
{
	int x;
	if (QueueEmpty(q)) {
		printf("\n\n\t| ERROR | Queue underflow |\n");
		return ERROR;
	}
	x = q->queue[q->head];
	q->head = (q->head == QUEUESIZE - 1) ? ARRAYSTARTINDEX : q->head + 1;
	return x;
}