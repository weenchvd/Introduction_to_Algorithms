#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct DFloatLinkedList {
	double num;
	struct DFloatLinkedList* next;
} DFloatLinkedList_t;

#endif