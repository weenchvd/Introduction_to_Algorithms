/* Chapter 12.1 | Binary-Search-Tree */
/* Exercise 12.1-3 | Binary-Search-Tree */
/* Exercise 12.1-4 | Binary-Search-Tree */
/* Chapter 12.2 | Binary-Search-Tree */
/* Exercise 12.2-2 | Binary-Search-Tree */
/* Exercise 12.2-3 | Binary-Search-Tree */

#include "BinarySearchTree_common.h"
#include "BinarySearchTree_struct.h"
#include <stdio.h>
#include <stdlib.h>

void BinarySearchTreeInsert(BinarySearchTree_t** root, int key, int* number);
void BinarySearchTreePrintWithStack(BinarySearchTree_t* root, int number);
void BinarySearchTreePrintWithPointer(BinarySearchTree_t* root);
void BinarySearchTreePrintRecursiveInorder(BinarySearchTree_t* root);
void BinarySearchTreePrintRecursivePreorder(BinarySearchTree_t* root);
void BinarySearchTreePrintRecursivePostorder(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeSearchRecursive(BinarySearchTree_t* root, int key);
BinarySearchTree_t* BinarySearchTreeSearchIterative(BinarySearchTree_t* root, int key);
BinarySearchTree_t* BinarySearchTreeMinimumIterative(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeMinimumRecursive(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeMaximumIterative(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeMaximumRecursive(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreeSuccessor(BinarySearchTree_t* root);
BinarySearchTree_t* BinarySearchTreePredecessor(BinarySearchTree_t* root);

int main(void)
{
	int action, key, number;
	char* list = "\tList of action:\n 0 (List of action), "
		"1 (BinarySearchTreeInsert), 2 (BinarySearchTreePrintWithStack), 3 (BinarySearchTreePrintWithPointer), "
		"4 (BinarySearchTreePrintRecursiveInorder), 5 (BinarySearchTreePrintRecursivePreorder), 6 (BinarySearchTreePrintRecursivePostorder), "
		"7 (BinarySearchTreeSearchRecursive), 8 (BinarySearchTreeSearchIterative), 9 (BinarySearchTreeMinimumIterative), "
		"10 (BinarySearchTreeMinimumRecursive), 11 (BinarySearchTreeMaximumIterative), 12 (BinarySearchTreeMaximumRecursive), "
		"13 (BinarySearchTreeSuccessor), 14 (BinarySearchTreePredecessor)\n\n";
	BinarySearchTree_t* root, * node;
	root = NULL;
	number = 0;
	printf(list);
	while (TRUE) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		switch (action) {
		case 0:
			printf(list);
			break;
		case 1:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			BinarySearchTreeInsert(&root, key, &number);
			printf("Node inserted!\n");
			break;
		case 2:
			printf("\tBinarySearchTreePrintWithStack:\n");
			BinarySearchTreePrintWithStack(root, number);
			break;
		case 3:
			printf("\tBinarySearchTreePrintWithPointer:\n");
			BinarySearchTreePrintWithPointer(root);
			break;
		case 4:
			printf("\tBinarySearchTreePrintRecursiveInorder:\n");
			BinarySearchTreePrintRecursiveInorder(root);
			break;
		case 5:
			printf("\tBinarySearchTreePrintRecursivePreorder:\n");
			BinarySearchTreePrintRecursivePreorder(root);
			break;
		case 6:
			printf("\tBinarySearchTreePrintRecursivePostorder:\n");
			BinarySearchTreePrintRecursivePostorder(root);
			break;
		case 7:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			printf("BinarySearchTreeSearchRecursive. Adress: %p\n", BinarySearchTreeSearchRecursive(root, key));
			break;
		case 8:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			printf("BinarySearchTreeSearchIterative. Adress: %p\n", BinarySearchTreeSearchIterative(root, key));
			break;
		case 9:
			printf("BinarySearchTreeMinimumIterative. Key: %d\n", BinarySearchTreeMinimumIterative(root)->key);
			break;
		case 10:
			printf("BinarySearchTreeMinimumRecursive. Key: %d\n", BinarySearchTreeMinimumRecursive(root)->key);
			break;
		case 11:
			printf("BinarySearchTreeMaximumIterative. Key: %d\n", BinarySearchTreeMaximumIterative(root)->key);
			break;
		case 12:
			printf("BinarySearchTreeMaximumRecursive. Key: %d\n", BinarySearchTreeMaximumRecursive(root)->key);
			break;
		case 13:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = BinarySearchTreeSearchIterative(root, key)) && (node = BinarySearchTreeSuccessor(node))) {
				printf("BinarySearchTreeSuccessor. Key: %d\n", node->key);
			}
			break;
		case 14:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = BinarySearchTreeSearchIterative(root, key)) && (node = BinarySearchTreePredecessor(node))) {
				printf("BinarySearchTreePredecessor. Key: %d\n", node->key);
			}
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}