/* Chapter 12.1 | Binary-Search-Tree */
/* Exercise 12.1-3 | Binary-Search-Tree */
/* Exercise 12.1-4 | Binary-Search-Tree */

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

int main(void)
{
	int action, key, number;
	BinarySearchTree_t* root;
	root = NULL;
	number = 0;
	printf("List of action:\n\t1 (BinarySearchTreeInsert), 2 (BinarySearchTreePrintWithStack), 3 (BinarySearchTreePrintWithPointer), "
		"4 (BinarySearchTreePrintRecursiveInorder), 5 (BinarySearchTreePrintRecursivePreorder), 6 (BinarySearchTreePrintRecursivePostorder)\n\n");
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
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}