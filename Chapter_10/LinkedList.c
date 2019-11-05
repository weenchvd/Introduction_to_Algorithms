#include "LinkedList.h"

DoublyLinkedList_t* ListSearch(DoublyLinkedList_t** head, int k)
{
	DoublyLinkedList_t* node;
	node = *head;
	while (node != NULL && node->key != k) {
		node = node->next;
	}
	return node;
}

void ListInsert(DoublyLinkedList_t** head, DoublyLinkedList_t* node)
{
	node->next = *head;
	if (*head != NULL) {
		(*head)->prev = node;
	}
	*head = node;
	node->prev = NULL;
	return;
}

void ListDelete(DoublyLinkedList_t** head, DoublyLinkedList_t* node)
{
	if (node->prev != NULL) {
		node->prev->next = node->next;
	}
	else {
		*head = node->next;
	}
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	return;
}

DoublyLinkedList_t* ListSearchSentinel(DoublyLinkedList_t* nil, int k)
{
	DoublyLinkedList_t* node;
	nil->key = k;
	node = nil->next;
	while (node->key != k) {
		node = node->next;
	}
	if (node == nil) {
		node = NULL;
	}
	return node;
}

void ListInsertSentinel(DoublyLinkedList_t* nil, DoublyLinkedList_t* node)
{
	node->next = nil->next;
	nil->next->prev = node;
	nil->next = node;
	node->prev = nil;
	return;
}

void ListDeleteSentinel(DoublyLinkedList_t* node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return;
}

void PrintList(DoublyLinkedList_t* head)
{
	int number;
	DoublyLinkedList_t* node;
	number = 0;
	node = head;
	while (node != NULL) {
		printf("Node number: %3d    Node address: %p    Node key: %8d\n", ++number, node, node->key);
		node = node->next;
	}
	if (number == 0) {
		printf("List is empty\n");
	}
	return;
}

void PrintListSentinel(DoublyLinkedList_t* nil)
{
	int number;
	DoublyLinkedList_t* node;
	number = 0;
	node = nil->next;
	while (node != nil) {
		printf("Node number: %3d    Node address: %p    Node key: %8d\n", ++number, node, node->key);
		node = node->next;
	}
	if (number == 0) {
		printf("List is empty\n");
	}
	return;
}