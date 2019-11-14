#include "BinarySearchTree.h"

void BinarySearchTreeInsert(BinarySearchTree_t** root, int key, int* number)
{
	BinarySearchTree_t* node, * newnode;
	if ((newnode = malloc(sizeof(BinarySearchTree_t))) == NULL) {
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
		newnode->parent = NULL;
	}
	return;
}

void BinarySearchTreePrintWithStack(BinarySearchTree_t* root, int number)
{
	BinarySearchTree_t* node;
	BSTStackSet_t s;
	s.ptr = 0;
	if ((s.stack = malloc(sizeof(BinarySearchTree_t*) * ((size_t)number + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	s.stack[s.ptr++] = root;
	while (s.ptr > 0) {
		node = s.stack[s.ptr - 1];
		while (node != NULL) {
			s.stack[s.ptr++] = node = node->left;
		}
		s.ptr--;
		if (s.ptr > 0) {
			node = s.stack[--s.ptr];
			printf("\t\tKey: %8d\n", node->key);
			s.stack[s.ptr++] = node->right;
		}
	}
	free(s.stack);
	return;
}

void BinarySearchTreePrintWithPointer(BinarySearchTree_t* root)
{
	BinarySearchTree_t* node, * prev;
	if (root == NULL) {
		return;
	}
	if (root->left != NULL) {
		node = root->left;
		prev = root;
		while (node != root) {
			if (prev == node->left) {
				printf("\t\tKey: %8d\n", node->key);
				prev = node;
				node = (node->right != NULL) ? node->right : node->parent;
			}
			else if (prev == node->right) {
				prev = node;
				node = node->parent;
			}
			else if (prev == node->parent) {
				if (node->left != NULL) {
					prev = node;
					node = node->left;
				}
				else {
					prev = NULL;
				}
			}
		}
	}
	printf("\t\tKey: %8d\n", root->key);
	if (root->right != NULL) {
		node = root->right;
		prev = root;
		while (node != root) {
			if (prev == node->left) {
				printf("\t\tKey: %8d\n", node->key);
				prev = node;
				node = (node->right != NULL) ? node->right : node->parent;
			}
			else if (prev == node->right) {
				prev = node;
				node = node->parent;
			}
			else if (prev == node->parent) {
				if (node->left != NULL) {
					prev = node;
					node = node->left;
				}
				else {
					prev = NULL;
				}
			}
		}
	}
	return;
}

void BinarySearchTreePrintRecursiveInorder(BinarySearchTree_t* root)
{
	if (root != NULL) {
		BinarySearchTreePrintRecursiveInorder(root->left);
		printf("\t\tKey: %8d\n", root->key);
		BinarySearchTreePrintRecursiveInorder(root->right);
	}
	return;
}

void BinarySearchTreePrintRecursivePreorder(BinarySearchTree_t* root)
{
	if (root != NULL) {
		printf("\t\tKey: %8d\n", root->key);
		BinarySearchTreePrintRecursivePreorder(root->left);
		BinarySearchTreePrintRecursivePreorder(root->right);
	}
	return;
}

void BinarySearchTreePrintRecursivePostorder(BinarySearchTree_t* root)
{
	if (root != NULL) {
		BinarySearchTreePrintRecursivePostorder(root->left);
		BinarySearchTreePrintRecursivePostorder(root->right);
		printf("\t\tKey: %8d\n", root->key);
	}
	return;
}