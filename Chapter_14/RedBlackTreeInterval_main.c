/* Chapter 14.3 | Interval-Tree */
/* Exercise 14.3-1 | Interval-Tree */

#include "RedBlackTreeInterval_common.h"
#include "RedBlackTreeInterval_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN -9999
#define MAX 9999
#define RANDOM(a,b) rand() % (b - a + 1) + a

RBT_t* RBTCreateNode(Interval_t i);
void RBTInsert(RBTPointers_t* tree, RBT_t* newnode);
void RBTDelete(RBTPointers_t* tree, RBT_t* delnode);
RBT_t* RBTISearch(RBTPointers_t* tree, Interval_t i);
void RBTPrintInorder(RBTPointers_t* tree, RBT_t* root, int hcounter, int bhcounter);
void RBTPrintNode(RBTPointers_t* tree, RBT_t* node);

int minheight;
int maxheight;
int minblackheight;
int maxblackheight;
int numnode;

int main(void)
{
	int i, j, r1, r2, way, action;
	char* list = "\tList of action:\n 0 (List of action), "
		"1 (RBTInsert), 2 (RBTDelete), 3 (RBTSearch), "
		"4 (RBTPrintInorder), 5 (RBTRandomInsert), 6 (RBTRandomDelete)\n\n";
	RBT_t* node;
	RBTPointers_t tree;
	RBT_t nil;
	Interval_t invl;
	nil.invl.low = nil.invl.high = nil.max = 0;
	nil.color = BLACK;
	nil.parent = nil.left = nil.right = NULL;
	tree.nil = tree.root = &nil;
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
			printf("Please enter a range of keys \"A, B\": ");
			if (scanf("%d, %d", &invl.low, &invl.high) <= 0) {
				printf("\n\n\t| ERROR | Unacceptable \"A, B\" range |\n");
				break;
			}
			if (invl.low <= invl.high && (node = RBTCreateNode(invl)) != NULL) {
				RBTInsert(&tree, node);
				printf("Node inserted!\n");
			}
			else {
				printf("Insert failed!\n");
			}
			break;
		case 2:
			printf("Please enter a range of keys \"A, B\": ");
			if (scanf("%d, %d", &invl.low, &invl.high) <= 0) {
				printf("\n\n\t| ERROR | Unacceptable \"A, B\" range |\n");
				break;
			}
			if (invl.low <= invl.high && (node = RBTISearch(&tree, invl)) != tree.nil) {
				RBTDelete(&tree, node);
				printf("Node deleted!\n");
			}
			else {
				printf("Removal failed!\n");
			}
			break;
		case 3:
			printf("Please enter a range of keys \"A, B\": ");
			if (scanf("%d, %d", &invl.low, &invl.high) <= 0) {
				printf("\n\n\t| ERROR | Unacceptable \"A, B\" range |\n");
				break;
			}
			if (invl.low <= invl.high && (node = RBTISearch(&tree, invl)) != tree.nil) {
				printf("RBTSearch. Adress: %p\n", node);
			}
			else {
				printf("Interval is not in the tree!\n");
			}
			break;
		case 4:
			maxheight = maxblackheight = numnode = 0;
			minheight = minblackheight = INT_MAX;
			printf("\tRBTPrintInorder:\n");
			RBTPrintInorder(&tree, tree.root, 0, 0);
			printf("\tHeight: min %d, max %d. Black height: min %d, max %d. Number of nodes: %d.\n",
				minheight, maxheight, minblackheight, maxblackheight, numnode);
			if (tree.root != tree.nil) {
				printf("\tRoot:\n");
				RBTPrintNode(&tree, tree.root);
				printf("\n\n");
			}
			else {
				printf("\tRoot: NIL\n\n");
			}
			break;
		case 5:
			j = 0;
			printf("Please enter the number of random keys to insert: ");
			if (scanf("%d", &j) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			for (i = 0; i < j; i++) {
				invl.low = RANDOM(MIN, MAX);
				invl.high = invl.low + RANDOM(0, 20);
				if ((node = RBTCreateNode(invl)) != NULL) {
					RBTInsert(&tree, node);
				}
			}
			printf("Nodes inserted!\n");
			break;
		case 6:
			j = 0;
			printf("Please enter the number of random keys to delete: ");
			if (scanf("%d", &j) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			for (i = 0; i < j; i++) {
				if (tree.root == tree.nil) {
					break;
				}
				else {
					node = tree.root;
				}
				r1 = RANDOM(1, 31000);
				r2 = RANDOM(2, 10);
				while ((r1 /= r2) > 1) {
					way = r1 % 2;
					if (way == 0) {
						if (node->left != tree.nil) {
							node = node->left;
						}
						else {
							break;
						}
					}
					else {
						if (node->right != tree.nil) {
							node = node->right;
						}
						else {
							break;
						}
					}
				}
				if (node != tree.nil) {
					RBTDelete(&tree, node);
				}
			}
			if (i > 0) {
				printf("Nodes deleted!\n");
			}
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}