/* Chapter 11.4 | Hash-Table-Open-Addressing */
/* Exercise 11.4-2 | Hash-Table-Open-Addressing */

#include "HashTableOpenAddressing_common.h"
#include "HashTableOpenAddressing_struct.h"
#include <stdio.h>
#include <stdlib.h>

int HashInsert(int* ht, int key);
int HashSearch(int* ht, int key);
int HashDelete(int* ht, int key);
void HashPrint(int* ht, int size);

int main(void)
{
	int i, action, key;
	int hashtable[HASHTABLESIZE];
	for (i = 0; i < HASHTABLESIZE; i++) {
		hashtable[i] = NIL;
	}
	printf("List of action:\n\t1 (HashInsert), 2 (HashSearch), 3 (HashDelete), 4 (HashPrint)\n\n");
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
			if (key >= 0) {
				if (HashInsert(hashtable, key)) {
					printf("Key inserted!\n");
				}
			}
			else {
				printf("\n\n\t| ERROR | Incorrect input. The key must be greater than or equal to 0 |\n");
			}
			break;
		case 2:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (key >= 0) {
				if ((i = HashSearch(hashtable, key)) >= 0) {
					printf("HashSearch: #%d\n", i);
				}
				else {
					printf("The key is not found:\n");
				}
			}
			else {
				printf("\n\n\t| ERROR | Incorrect input. The key must be greater than or equal to 0 |\n");
			}
			break;
		case 3:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (key >= 0) {
				if ((i = HashDelete(hashtable, key)) >= 0) {
					printf("The key #%d is deleted\n", i);
				}
				else {
					printf("The key is not found:\n");
				}
			}
			else {
				printf("\n\n\t| ERROR | Incorrect input. The key must be greater than or equal to 0 |\n");
			}
			break;
		case 4:
			printf("\tHashPrint:\n");
			HashPrint(hashtable, HASHTABLESIZE);
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}