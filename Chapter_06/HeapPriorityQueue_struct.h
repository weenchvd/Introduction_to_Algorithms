#ifndef _STRUCT_H
#define _STRUCT_H

#define PRIORITYQUEUESIZE 1024

typedef struct PriorityQueue {
	int priority[PRIORITYQUEUESIZE];
	int handle[PRIORITYQUEUESIZE];
} PriorityQueue_t;

typedef struct Handle {
	int priority;
	int handle;
} Handle_t;

#endif