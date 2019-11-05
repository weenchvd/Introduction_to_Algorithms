#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct DoublyLinkedList {
	struct DoublyLinkedList* prev;
	struct DoublyLinkedList* next;
	int key;
} DoublyLinkedList_t;

#endif