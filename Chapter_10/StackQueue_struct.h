#ifndef _STRUCT_H
#define _STRUCT_H

#define STACKSIZE 10
#define QUEUESIZE 10

typedef struct StackSet {
	int stack[STACKSIZE];
	int top;
} StackSet_t;

typedef struct QueueSet {
	int queue[QUEUESIZE];
	int head;
	int tail;
} QueueSet_t;

#endif