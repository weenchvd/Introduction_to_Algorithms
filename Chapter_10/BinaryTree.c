#include "BinaryTree.h"

void BinaryTreeInsert(BinaryTree_t** root, int key, int* number)
{
	BinaryTree_t* node, * newnode;
	if ((newnode = malloc(sizeof(BinaryTree_t))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->key = key;
	(*number)++;
	if (*root != NULL) {
		node = *root;
		while (TRUE) {
			if (key < node->key) {
				if (node->left != NULL) {
					node = node->left;
				}
				else {
					node->left = newnode;
					newnode->parent = node;
					break;
				}
			}
			else {
				if (node->right != NULL) {
					node = node->right;
				}
				else {
					node->right = newnode;
					newnode->parent = node;
					break;
				}
			}
		}
	}
	else {
		*root = newnode;
		newnode->parent = *root;
	}
	return;
}

void BinaryTreePrint(BinaryTree_t* root, int number)
{
	int path;
	BinaryTree_t* node;
	StackSet_t s;
	s.ptr = 0;
	if ((s.stack = malloc(sizeof(int) * ((size_t)number * 2 + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	if (root != NULL) {
		s.stack[s.ptr++] = ENDOFTREE;
		s.stack[s.ptr++] = DOWN;
		node = root;
		while (path = s.stack[--s.ptr]) {		/* while (path != ENDOFTREE) */
			if (path == LEFT) {
				printf("\tKey: %8d\n", node->key);
				if (node->right != NULL) {
					s.stack[s.ptr++] = RIGHT;
					s.stack[s.ptr++] = DOWN;
					node = node->right;
					continue;
				}
				s.stack[s.ptr++] = UP;
			}
			else if (path == RIGHT) {
				s.stack[s.ptr++] = UP;
			}
			else if (path == DOWN) {
				if (node->left != NULL) {
					s.stack[s.ptr++] = LEFT;
					s.stack[s.ptr++] = DOWN;
					node = node->left;
					continue;
				}
				printf("\tKey: %8d\n", node->key);
				if (node->right != NULL) {
					s.stack[s.ptr++] = RIGHT;
					s.stack[s.ptr++] = DOWN;
					node = node->right;
					continue;
				}
				s.stack[s.ptr++] = UP;
			}
			else if (path == UP) {
				node = node->parent;
			}
		}
	}
	free(s.stack);
	return;
}

void BinaryTreePrintRecursive(BinaryTree_t* root)
{
	if (root != NULL) {
		BinaryTreePrintRecursive(root->left);
		printf("\tKey: %8d\n", root->key);
		BinaryTreePrintRecursive(root->right);
	}
	return;
}