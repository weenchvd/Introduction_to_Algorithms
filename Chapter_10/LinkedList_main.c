/* Chapter 10.2 | Linked-List */
/* Exercise 10.2-4 | Linked-List */

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

int main(void)
{
	int action, key;
	DoublyLinkedList_t* head;
	DoublyLinkedList_t* nil;
	DoublyLinkedList_t* node;
	DoublyLinkedList_t nilnode;
	head = NULL;
	nil = &nilnode;
	nil->next = nil;
	nil->prev = nil;
	printf("List of action:\n\t1 (ListSearch), 2 (ListInsert), 3 (ListDelete), 4 (PrintList), "
		"5 (ListSearchSentinel), 6 (ListInsertSentinel), 7 (ListDeleteSentinel), 8 (PrintListSentinel)\n\n");
	while (TRUE) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		switch (action) {
		case 1:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			printf("Node address: %p\n", ListSearch(&head, key));
			break;
		case 2:
			if ((node = malloc(sizeof(DoublyLinkedList_t))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			node->key = key;
			ListInsert(&head, node);
			printf("Node inserted!\n");
			break;
		case 3:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			node = ListSearch(&head, key);
			if (node != NULL) {
				ListDelete(&head, node);
				printf("Node deleted!\n");
			}
			else {
				printf("The node is not listed!\n");
			}
			break;
		case 4:
			PrintList(head);
			break;
		case 5:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			printf("Node address: %p\n", ListSearchSentinel(nil, key));
			break;
		case 6:
			if ((node = malloc(sizeof(DoublyLinkedList_t))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			node->key = key;
			ListInsertSentinel(nil, node);
			printf("Node inserted!\n");
			break;
		case 7:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			node = ListSearchSentinel(nil, key);
			if (node != NULL) {
				ListDeleteSentinel(node);
				printf("Node deleted!\n");
			}
			else {
				printf("The node is not listed!\n");
			}
			break;
		case 8:
			PrintListSentinel(nil);
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}