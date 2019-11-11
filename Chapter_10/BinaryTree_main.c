/* Exercise 10.4-3 | Binary-Tree */

#include "BinaryTree_common.h"
#include "BinaryTree_struct.h"
#include <stdio.h>
#include <stdlib.h>

void BinaryTreeInsert(BinaryTree_t** root, int key, int* number);
void BinaryTreePrint(BinaryTree_t* root, int number);
void BinaryTreePrintRecursive(BinaryTree_t* root);

int main(void)
{
	int action, key, number;
	BinaryTree_t* root;
	root = NULL;
	number = 0;
	printf("List of action:\n\t1 (BinaryTreeInsert), 2 (BinaryTreePrint), 3 (BinaryTreePrintRecursive)\n\n");
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
			BinaryTreeInsert(&root, key, &number);
			printf("Node inserted!\n");
			break;
		case 2:
			printf("\tBinaryTreePrint:\n");
			BinaryTreePrint(root, number);
			break;
		case 3:
			printf("\tBinaryTreePrintRecursive:\n");
			BinaryTreePrintRecursive(root);
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}