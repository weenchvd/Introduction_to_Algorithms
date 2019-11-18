/* Chapter 12.1 | Binary-Search-Tree */
/* Exercise 12.1-3 | Binary-Search-Tree */
/* Exercise 12.1-4 | Binary-Search-Tree */
/* Chapter 12.2 | Binary-Search-Tree */
/* Exercise 12.2-2 | Binary-Search-Tree */
/* Exercise 12.2-3 | Binary-Search-Tree */
/* Chapter 12.3 | Binary-Search-Tree */
/* Exercise 12.3-1 | Binary-Search-Tree */

#include "BinarySearchTree_common.h"
#include "BinarySearchTree_struct.h"
#include <stdio.h>
#include <stdlib.h>

BST_t* BSTCreateNode(int key, int* number);
void BSTInsertIterative(BST_t** root, BST_t* newnode);
void BSTInsertRecursive(BST_t** root, BST_t* newnode);
void BSTPrintWithStack(BST_t* root, int number);
void BSTPrintWithPointer(BST_t* root);
void BSTPrintRecursiveInorder(BST_t* root);
void BSTPrintRecursivePreorder(BST_t* root);
void BSTPrintRecursivePostorder(BST_t* root);
BST_t* BSTSearchRecursive(BST_t* root, int key);
BST_t* BSTSearchIterative(BST_t* root, int key);
BST_t* BSTMinimumIterative(BST_t* root);
BST_t* BSTMinimumRecursive(BST_t* root);
BST_t* BSTMaximumIterative(BST_t* root);
BST_t* BSTMaximumRecursive(BST_t* root);
BST_t* BSTSuccessor(BST_t* root);
BST_t* BSTPredecessor(BST_t* root);
void BSTDelete(BST_t** root, BST_t* node);

int main(void)
{
	int action, key, number;
	char* list = "\tList of action:\n 0 (List of action), "
		"1 (BSTInsertIterative), 2 (BSTInsertRecursive), 3 (BSTPrintWithStack), 4 (BSTPrintWithPointer), "
		"5 (BSTPrintRecursiveInorder), 6 (BSTPrintRecursivePreorder), 7 (BSTPrintRecursivePostorder), "
		"8 (BSTSearchRecursive), 9 (BSTSearchIterative), 10 (BSTMinimumIterative), "
		"11 (BSTMinimumRecursive), 12 (BSTMaximumIterative), 13 (BSTMaximumRecursive), "
		"14 (BSTSuccessor), 15 (BSTPredecessor), 16 (BSTDelete)\n\n";
	BST_t* root, * node;
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
			if ((node = BSTCreateNode(key, &number)) != NULL) {
				BSTInsertIterative(&root, node);
				printf("Node inserted!\n");
			}
			else {
				printf("Insert failed!\n");
			}
			break;
		case 2:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = BSTCreateNode(key, &number)) != NULL) {
				BSTInsertRecursive(&root, node);
				printf("Node inserted!\n");
			}
			else {
				printf("Insert failed!\n");
			}
			break;
		case 3:
			printf("\tBinarySearchTreePrintWithStack:\n");
			BSTPrintWithStack(root, number);
			break;
		case 4:
			printf("\tBinarySearchTreePrintWithPointer:\n");
			BSTPrintWithPointer(root);
			break;
		case 5:
			printf("\tBinarySearchTreePrintRecursiveInorder:\n");
			BSTPrintRecursiveInorder(root);
			break;
		case 6:
			printf("\tBinarySearchTreePrintRecursivePreorder:\n");
			BSTPrintRecursivePreorder(root);
			break;
		case 7:
			printf("\tBinarySearchTreePrintRecursivePostorder:\n");
			BSTPrintRecursivePostorder(root);
			break;
		case 8:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			printf("BSTSearchRecursive. Adress: %p\n", BSTSearchRecursive(root, key));
			break;
		case 9:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			printf("BSTSearchIterative. Adress: %p\n", BSTSearchIterative(root, key));
			break;
		case 10:
			printf("BSTMinimumIterative. Key: %d\n", BSTMinimumIterative(root)->key);
			break;
		case 11:
			printf("BSTMinimumRecursive. Key: %d\n", BSTMinimumRecursive(root)->key);
			break;
		case 12:
			printf("BSTMaximumIterative. Key: %d\n", BSTMaximumIterative(root)->key);
			break;
		case 13:
			printf("BSTMaximumRecursive. Key: %d\n", BSTMaximumRecursive(root)->key);
			break;
		case 14:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = BSTSearchIterative(root, key)) && (node = BSTSuccessor(node))) {
				printf("BSTSuccessor. Key: %d\n", node->key);
			}
			break;
		case 15:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = BSTSearchIterative(root, key)) && (node = BSTPredecessor(node))) {
				printf("BSTPredecessor. Key: %d\n", node->key);
			}
			break;
		case 16:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = BSTSearchIterative(root, key)) != NULL) {
				BSTDelete(&root, node);
				printf("Node deleted!\n");
			}
			else {
				printf("Removal failed!\n");
			}
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}