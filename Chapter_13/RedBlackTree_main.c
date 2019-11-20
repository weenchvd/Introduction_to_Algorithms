/* Chapter 13.1 | Red-Black-Tree */
/* Chapter 13.2 | Red-Black-Tree */
/* Chapter 13.3 | Red-Black-Tree */

#include "RedBlackTree_common.h"
#include "RedBlackTree_struct.h"
#include <stdio.h>
#include <stdlib.h>

RBT_t* RBTCreateNode(int key);
void RBTInsert(RBTPointers_t* tree, RBT_t* newnode);
RBT_t* RBTSearch(RBTPointers_t* tree, int key);
void RBTPrintInorder(RBTPointers_t* tree, RBT_t* root, int hcounter, int bhcounter);
void RBTPrintPreorder(RBTPointers_t* tree, RBT_t* root);
void RBTPrintPostorder(RBTPointers_t* tree, RBT_t* root);

int minheight;
int maxheight;
int blackheight;
int numnode;

int main(void)
{
	int action, key;
	char* list = "\tList of action:\n 0 (List of action), "
		"1 (RBTInsert), 2 (RBTSearch), "
		"3 (RBTPrintInorder), 4 (RBTPrintPreorder), 5 (RBTPrintPostorder)\n\n";
	RBT_t* node;
	RBTPointers_t tree;
	RBT_t nil;
	nil.key = 0;
	nil.color = BLACK;
	nil.parent = nil.left = nil.right = NULL;
	tree.nil = tree.root = &nil;
	minheight = INT_MAX;
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
			if ((node = RBTCreateNode(key)) != NULL) {
				RBTInsert(&tree, node);
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
			if ((node = RBTSearch(&tree, key)) != tree.nil) {
				printf("RBTSearch. Adress: %p\n", node);
			}
			else {
				printf("Node is not in the tree!\n");
			}
			break;
		case 3:
			printf("\tRBTPrintInorder:\n");
			RBTPrintInorder(&tree, tree.root, 0, 0);
			printf("\tMinimal height: %d. Maximum height: %d. Black height: %d. Number of nodes: %d.\n", minheight, maxheight, blackheight, numnode);
			maxheight = blackheight = numnode = 0;
			minheight = INT_MAX;
			break;
		case 4:
			printf("\tRBTPrintPreorder:\n");
			RBTPrintPreorder(&tree, tree.root);
			break;
		case 5:
			printf("\tRBTPrintPostorder:\n");
			RBTPrintPostorder(&tree, tree.root);
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}