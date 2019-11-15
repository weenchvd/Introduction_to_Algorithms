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

BinarySearchTree_t* BinarySearchTreeSearchRecursive(BinarySearchTree_t* root, int key)
{
	if (root == NULL || key == root->key) {
		return root;
	}
	if (key < root->key) {
		return BinarySearchTreeSearchRecursive(root->left, key);
	}
	else {
		return BinarySearchTreeSearchRecursive(root->right, key);
	}
}

BinarySearchTree_t* BinarySearchTreeSearchIterative(BinarySearchTree_t* root, int key)
{
	while (root != NULL && key != root->key) {
		root = (key < root->key) ? root->left : root->right;
	}
	return root;
}

BinarySearchTree_t* BinarySearchTreeMinimumIterative(BinarySearchTree_t* root)
{
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

BinarySearchTree_t* BinarySearchTreeMinimumRecursive(BinarySearchTree_t* root)
{
	if (root->left == NULL) {
		return root;
	}
	return BinarySearchTreeMinimumRecursive(root->left);
}

BinarySearchTree_t* BinarySearchTreeMaximumIterative(BinarySearchTree_t* root)
{
	while (root->right != NULL) {
		root = root->right;
	}
	return root;
}

BinarySearchTree_t* BinarySearchTreeMaximumRecursive(BinarySearchTree_t* root)
{
	if (root->right == NULL) {
		return root;
	}
	return BinarySearchTreeMaximumRecursive(root->right);
}

BinarySearchTree_t* BinarySearchTreeSuccessor(BinarySearchTree_t* root)
{
	BinarySearchTree_t* prev;
	if (root->right != NULL) {
		return BinarySearchTreeMinimumIterative(root->right);
	}
	prev = (root->parent != NULL) ? root->parent : NULL;
	while (prev != NULL && root == prev->right) {
		root = prev;
		prev = prev->parent;
	}
	return prev;
}

BinarySearchTree_t* BinarySearchTreePredecessor(BinarySearchTree_t* root)
{
	BinarySearchTree_t* prev;
	if (root->left != NULL) {
		return BinarySearchTreeMaximumIterative(root->left);
	}
	prev = (root->parent != NULL) ? root->parent : NULL;
	while (prev != NULL && root == prev->left) {
		root = prev;
		prev = prev->parent;
	}
	return prev;
}