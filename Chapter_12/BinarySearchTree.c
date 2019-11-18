#include "BinarySearchTree.h"

BST_t* BSTCreateNode(int key, int* number)
{
	BST_t* node;
	if ((node = malloc(sizeof(BST_t))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return NULL;
	}
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	(*number)++;
	return node;
}

void BSTInsertIterative(BST_t** root, BST_t* newnode)
{
	BST_t* node, * prev;
	prev = NULL;
	node = *root;
	while (node != NULL) {
		prev = node;
		node = (newnode->key < node->key) ? node->left : node->right;
	}
	newnode->parent = prev;
	if (prev == NULL) {
		*root = newnode;
	}
	else if (newnode->key < prev->key) {
		prev->left = newnode;
	}
	else {
		prev->right = newnode;
	}
	return;
}

void BSTInsertRecursive(BST_t** root, BST_t* newnode)
{
	if (*root == NULL) {
		*root = newnode;
	}
	else if (newnode->key < (*root)->key) {
		if ((*root)->left == NULL) {
			(*root)->left = newnode;
			newnode->parent = *root;
		}
		else {
			BSTInsertRecursive(&(*root)->left, newnode);
		}
	}
	else {
		if ((*root)->right == NULL) {
			(*root)->right = newnode;
			newnode->parent = *root;
		}
		else {
			BSTInsertRecursive(&(*root)->right, newnode);
		}
	}
	return;
}

void BSTPrintWithStack(BST_t* root, int number)
{
	BST_t* node;
	BSTStackSet_t s;
	s.ptr = 0;
	if ((s.stack = malloc(sizeof(BST_t*) * ((size_t)number + 1))) == NULL) {
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

void BSTPrintWithPointer(BST_t* root)
{
	BST_t* node, * prev;
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

void BSTPrintRecursiveInorder(BST_t* root)
{
	if (root != NULL) {
		BSTPrintRecursiveInorder(root->left);
		printf("\t\tKey: %8d\n", root->key);
		BSTPrintRecursiveInorder(root->right);
	}
	return;
}

void BSTPrintRecursivePreorder(BST_t* root)
{
	if (root != NULL) {
		printf("\t\tKey: %8d\n", root->key);
		BSTPrintRecursivePreorder(root->left);
		BSTPrintRecursivePreorder(root->right);
	}
	return;
}

void BSTPrintRecursivePostorder(BST_t* root)
{
	if (root != NULL) {
		BSTPrintRecursivePostorder(root->left);
		BSTPrintRecursivePostorder(root->right);
		printf("\t\tKey: %8d\n", root->key);
	}
	return;
}

BST_t* BSTSearchRecursive(BST_t* root, int key)
{
	if (root == NULL || key == root->key) {
		return root;
	}
	if (key < root->key) {
		return BSTSearchRecursive(root->left, key);
	}
	else {
		return BSTSearchRecursive(root->right, key);
	}
}

BST_t* BSTSearchIterative(BST_t* root, int key)
{
	while (root != NULL && key != root->key) {
		root = (key < root->key) ? root->left : root->right;
	}
	return root;
}

BST_t* BSTMinimumIterative(BST_t* root)
{
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

BST_t* BSTMinimumRecursive(BST_t* root)
{
	if (root->left == NULL) {
		return root;
	}
	return BSTMinimumRecursive(root->left);
}

BST_t* BSTMaximumIterative(BST_t* root)
{
	while (root->right != NULL) {
		root = root->right;
	}
	return root;
}

BST_t* BSTMaximumRecursive(BST_t* root)
{
	if (root->right == NULL) {
		return root;
	}
	return BSTMaximumRecursive(root->right);
}

BST_t* BSTSuccessor(BST_t* root)
{
	BST_t* prev;
	if (root->right != NULL) {
		return BSTMinimumIterative(root->right);
	}
	prev = (root->parent != NULL) ? root->parent : NULL;
	while (prev != NULL && root == prev->right) {
		root = prev;
		prev = prev->parent;
	}
	return prev;
}

BST_t* BSTPredecessor(BST_t* root)
{
	BST_t* prev;
	if (root->left != NULL) {
		return BSTMaximumIterative(root->left);
	}
	prev = (root->parent != NULL) ? root->parent : NULL;
	while (prev != NULL && root == prev->left) {
		root = prev;
		prev = prev->parent;
	}
	return prev;
}

void BSTTransplant(BST_t** root, BST_t* receiver, BST_t* source)
{
	if (receiver->parent == NULL) {
		*root = source;
	}
	else if (receiver == receiver->parent->left) {
		receiver->parent->left = source;
	}
	else {
		receiver->parent->right = source;
	}
	if (source != NULL) {
		source->parent = receiver->parent;
	}
	return;
}

void BSTDelete(BST_t** root, BST_t* node)
{
	BST_t* min;
	if (node->left == NULL) {
		BSTTransplant(root, node, node->right);
	}
	else if (node->right == NULL) {
		BSTTransplant(root, node, node->left);
	}
	else {
		min = BSTMinimumIterative(node->right);
		if (min->parent != node) {
			BSTTransplant(root, min, min->right);
			min->right = node->right;
			min->right->parent = min;
		}
		BSTTransplant(root, node, min);
		min->left = node->left;
		min->left->parent = min;
	}
	free(node);
	return;
}