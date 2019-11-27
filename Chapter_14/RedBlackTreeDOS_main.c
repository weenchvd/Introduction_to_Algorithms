/* Chapter 14.1 | Dynamic-Order-Statistics */
/* Exercise 14.1-3 | Dynamic-Order-Statistics */
/* Exercise 14.1-4 | Dynamic-Order-Statistics */
/* Exercise 14.1-6 | Dynamic-Order-Statistics */
/* Exercise 14.2-1 | Augmenting-Data-Structure */
/* Exercise 14.2-4 | Augmenting-Data-Structure */

#include "RedBlackTreeDOS_common.h"
#include "RedBlackTreeDOS_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN -9999
#define MAX 9999
#define RANDOM(a,b) rand() % (b - a + 1) + a

RBT_t* RBTCreateNode(int key);
void RBTInsert(RBTPointers_t* tree, RBT_t* newnode);
void RBTDelete(RBTPointers_t* tree, RBT_t* delnode);
RBT_t* RBTOSSelectRecursive(RBT_t* root, int rank);
RBT_t* RBTOSSelectIterative(RBT_t* root, int rank);
int RBTOSRank(RBTPointers_t* tree, RBT_t* node);
int RBTOSKeyRank(RBTPointers_t* tree, int key);
void RBTADSEnumerate(RBTPointers_t* tree, int a, int b);
RBT_t* RBTSearch(RBTPointers_t* tree, int key);
void RBTPrintInorder(RBTPointers_t* tree, RBT_t* root, int hcounter, int bhcounter);
void RBTPrintPreorder(RBTPointers_t* tree, RBT_t* root);
void RBTPrintPostorder(RBTPointers_t* tree, RBT_t* root);

int minheight;
int maxheight;
int minblackheight;
int maxblackheight;
int numnode;

int main(void)
{
	int i, j, r1, r2, way, action, key, rank;
	char* list = "\tList of action:\n 0 (List of action), "
		"1 (RBTInsert), 2 (RBTDelete), 3 (RBTSearch), "
		"4 (RBTOSSelectRecursive), 5 (RBTOSSelectIterative), 6 (RBTOSRank), 7 (RBTOSKeyRank), 8 (RBTADSEnumerate), "
		"9 (RBTPrintInorder), 10 (RBTPrintPreorder), 11 (RBTPrintPostorder), "
		"12 (RBTRandomInsert), 13 (RBTRandomDelete)\n\n";
	RBT_t* node;
	RBTPointers_t tree;
	RBT_t nil;
	nil.key = nil.size = 0;
	nil.color = BLACK;
	nil.parent = nil.left = nil.right = nil.suc = nil.pred = NULL;
	tree.nil = tree.root = tree.min = tree.max = &nil;
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
				RBTDelete(&tree, node);
				printf("Node deleted!\n");
			}
			else {
				printf("Removal failed!\n");
			}
			break;
		case 3:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = RBTSearch(&tree, key)) != tree.nil) {
				printf("RBTSearch. Address: %p\n", node);
			}
			else {
				printf("Node is not in the tree!\n");
			}
			break;
		case 4:
			printf("Please enter a rank: ");
			if (scanf("%d", &rank) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (rank > 0) {
				node = RBTOSSelectRecursive(tree.root, rank);
				printf("\tRBTOSSelectRecursive: address %p, key %d, rank %d\n", node, node->key, rank);
			}
			else {
				printf("\n\n\t| ERROR | Incorrect input. The rank must be greater than 0 |\n");
			}
			break;
		case 5:
			printf("Please enter a rank: ");
			if (scanf("%d", &rank) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (rank > 0) {
				node = RBTOSSelectIterative(tree.root, rank);
				printf("\tRBTOSSelectIterative: address %p, key %d, rank %d\n", node, node->key, rank);
			}
			else {
				printf("\n\n\t| ERROR | Incorrect input. The rank must be greater than 0 |\n");
			}
			break;
		case 6:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((node = RBTSearch(&tree, key)) != tree.nil) {
				printf("\tRBTOSRank: address %p, key %d, rank %d\n", node, node->key, RBTOSRank(&tree, node));
			}
			else {
				printf("Node is not in the tree!\n");
			}
			break;
		case 7:
			printf("Please enter a key: ");
			if (scanf("%d", &key) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if ((rank = RBTOSKeyRank(&tree, key)) != FAILURE) {
				printf("\tRBTOSKeyRank: address %p, key %d, rank %d\n", RBTSearch(&tree, key), key, rank);
			}
			else {
				printf("Node is not in the tree!\n");
			}
			break;
		case 8:
			printf("Please enter a range of keys \"A, B\": ");
			if (scanf("%d, %d", &r1, &r2) <= 0) {
				printf("\n\n\t| ERROR | Unacceptable \"A, B\" range |\n");
				break;
			}
			if (r1 < r2) {
				printf("\tRBTADSEnumerate(keys from %d to %d):\n", r1, r2);
				RBTADSEnumerate(&tree, r1, r2);
			}
			break;
		case 9:
			maxheight = maxblackheight = numnode = 0;
			minheight = minblackheight = INT_MAX;
			printf("\tRBTPrintInorder:\n\n");
			RBTPrintInorder(&tree, tree.root, 0, 0);
			printf("\tHeight: min %d, max %d. Black height: min %d, max %d. Number of nodes: %d.\n"
				"\tMinimum: %d. Maximum: %d.\n\n",
				minheight, maxheight, minblackheight, maxblackheight, numnode,
				tree.min->key, tree.max->key);
			break;
		case 10:
			printf("\tRBTPrintPreorder:\n");
			RBTPrintPreorder(&tree, tree.root);
			break;
		case 11:
			printf("\tRBTPrintPostorder:\n");
			RBTPrintPostorder(&tree, tree.root);
			break;
		case 12:
			j = 0;
			printf("Please enter the number of random keys to insert: ");
			if (scanf("%d", &j) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			for (i = 0; i < j; i++) {
				if ((node = RBTCreateNode(RANDOM(MIN, MAX))) != NULL) {
					RBTInsert(&tree, node);
				}
			}
			printf("Nodes inserted!\n");
			break;
		case 13:
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