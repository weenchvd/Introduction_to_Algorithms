#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "LinkedList_common.h"
#include "LinkedList_struct.h"
#include <stdio.h>
#include <stdlib.h>

DoublyLinkedList_t* ListSearch(DoublyLinkedList_t** head, int k);
void ListInsert(DoublyLinkedList_t** head, DoublyLinkedList_t* node);
void ListDelete(DoublyLinkedList_t** head, DoublyLinkedList_t* node);
DoublyLinkedList_t* ListSearchSentinel(DoublyLinkedList_t* nil, int k);
void ListInsertSentinel(DoublyLinkedList_t* nil, DoublyLinkedList_t* node);
void ListDeleteSentinel(DoublyLinkedList_t* node);
void PrintList(DoublyLinkedList_t* head);
void PrintListSentinel(DoublyLinkedList_t* nil);

#endif