#include "RedBlackTreeDOS.h"

extern int minheight;
extern int maxheight;
extern int minblackheight;
extern int maxblackheight;
extern int numnode;

RBT_t* RBTCreateNode(int key)
{
	RBT_t* node;
	if ((node = malloc(sizeof(RBT_t))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return NULL;
	}
	node->key = key;
	return node;
}

void RBTInsert(RBTPointers_t* tree, RBT_t* newnode)
{
	RBT_t* node, * prev;
	prev = tree->nil;
	node = tree->root;
	while (node != tree->nil) {
		prev = node;
		node = (newnode->key < node->key) ? node->left : node->right;
	}
	newnode->parent = prev;
	if (prev == tree->nil) {
		tree->root = newnode;
	}
	else if (newnode->key < prev->key) {
		prev->left = newnode;
	}
	else {
		prev->right = newnode;
	}
	newnode->left = newnode->right = tree->nil;
	newnode->color = RED;
	newnode->size = 1;
	for (node = newnode->parent; node != tree->nil; node = node->parent) {
		node->size++;
	}
	RBTInsertFixup(tree, newnode);
	return;
}

void RBTInsertFixup(RBTPointers_t* tree, RBT_t* node)
{
	RBT_t* uncle;
	while (node->parent->color == RED) {
		if (node->parent == node->parent->parent->left) {
			uncle = node->parent->parent->right;
			if (uncle->color == RED) {
				node->parent->color = uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->right) {
					node = node->parent;
					RBTLeftRotate(tree, node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RBTRightRotate(tree, node->parent->parent);
			}
		}
		else {
			uncle = node->parent->parent->left;
			if (uncle->color == RED) {
				node->parent->color = uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					RBTRightRotate(tree, node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RBTLeftRotate(tree, node->parent->parent);
			}
		}
	}
	tree->root->color = BLACK;
	return;
}

void RBTLeftRotate(RBTPointers_t* tree, RBT_t* node)
{
	RBT_t* rightchild;
	rightchild = node->right;
	node->right = rightchild->left;
	if (rightchild->left != tree->nil) {
		rightchild->left->parent = node;
	}
	rightchild->parent = node->parent;
	if (node->parent == tree->nil) {
		tree->root = rightchild;
	}
	else if (node == node->parent->left) {
		node->parent->left = rightchild;
	}
	else {
		node->parent->right = rightchild;
	}
	rightchild->left = node;
	node->parent = rightchild;
	rightchild->size = node->size;
	node->size = node->left->size + node->right->size + 1;
	return;
}

void RBTRightRotate(RBTPointers_t* tree, RBT_t* node)
{
	RBT_t* leftchild;
	leftchild = node->left;
	node->left = leftchild->right;
	if (leftchild->right != tree->nil) {
		leftchild->right->parent = node;
	}
	leftchild->parent = node->parent;
	if (node->parent == tree->nil) {
		tree->root = leftchild;
	}
	else if (node == node->parent->left) {
		node->parent->left = leftchild;
	}
	else {
		node->parent->right = leftchild;
	}
	leftchild->right = node;
	node->parent = leftchild;
	leftchild->size = node->size;
	node->size = node->left->size + node->right->size + 1;
	return;
}

void RBTDelete(RBTPointers_t* tree, RBT_t* delnode)
{
	int ycolor;
	RBT_t* y, * x;
	y = delnode;
	ycolor = y->color;
	if (delnode->left == tree->nil) {
		x = delnode->right;
		RBTTransplant(tree, delnode, delnode->right);
		RBTOSDecreaseSize(tree, x);
	}
	else if (delnode->right == tree->nil) {
		x = delnode->left;
		RBTTransplant(tree, delnode, delnode->left);
		RBTOSDecreaseSize(tree, x);
	}
	else {
		y = RBTMinimum(tree, delnode->right);
		ycolor = y->color;
		x = y->right;
		if (y->parent == delnode) {
			x->parent = y;
		}
		else {
			RBTTransplant(tree, y, y->right);
			y->right = delnode->right;
			y->right->parent = y;
		}
		RBTTransplant(tree, delnode, y);
		y->left = delnode->left;
		y->left->parent = y;
		y->color = delnode->color;
		y->size = y->left->size + y->right->size + 1;
		if (x->parent != y) {
			RBTOSDecreaseSize(tree, x);
		}
		else if (x->parent != tree->root) {
			RBTOSDecreaseSize(tree, x->parent);
		}
	}
	if (ycolor == BLACK) {
		RBTDeleteFixup(tree, x);
	}
	free(delnode);
	return;
}

void RBTTransplant(RBTPointers_t* tree, RBT_t* receiver, RBT_t* source)
{
	if (receiver->parent == tree->nil) {
		tree->root = source;
	}
	else if (receiver == receiver->parent->left) {
		receiver->parent->left = source;
	}
	else {
		receiver->parent->right = source;
	}
	source->parent = receiver->parent;
	return;
}

void RBTOSDecreaseSize(RBTPointers_t* tree, RBT_t* node)
{
	for (node = node->parent; node != tree->nil; node = node->parent) {
		node->size--;
	}
	return;
}

void RBTDeleteFixup(RBTPointers_t* tree, RBT_t* node)
{
	RBT_t* sibling;
	while (node != tree->root && node->color == BLACK) {
		if (node == node->parent->left) {
			sibling = node->parent->right;
			if (sibling->color == RED) {
				sibling->color = BLACK;
				node->parent->color = RED;
				RBTLeftRotate(tree, node->parent);
				sibling = node->parent->right;
			}
			if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
				sibling->color = RED;
				node = node->parent;
			}
			else {
				if (sibling->right->color == BLACK) {
					sibling->left->color = BLACK;
					sibling->color = RED;
					RBTRightRotate(tree, sibling);
					sibling = node->parent->right;
				}
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->right->color = BLACK;
				RBTLeftRotate(tree, node->parent);
				node = tree->root;
			}
		}
		else {
			sibling = node->parent->left;
			if (sibling->color == RED) {
				sibling->color = BLACK;
				node->parent->color = RED;
				RBTRightRotate(tree, node->parent);
				sibling = node->parent->left;
			}
			if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
				sibling->color = RED;
				node = node->parent;
			}
			else {
				if (sibling->left->color == BLACK) {
					sibling->right->color = BLACK;
					sibling->color = RED;
					RBTLeftRotate(tree, sibling);
					sibling = node->parent->left;
				}
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->left->color = BLACK;
				RBTRightRotate(tree, node->parent);
				node = tree->root;
			}
		}
	}
	node->color = BLACK;
	return;
}

RBT_t* RBTMinimum(RBTPointers_t* tree, RBT_t* root)
{
	while (root->left != tree->nil) {
		root = root->left;
	}
	return root;
}

RBT_t* RBTOSSelectRecursive(RBT_t* root, int rank)
{
	int noderank;
	noderank = root->left->size + 1;
	if (rank == noderank) {
		return root;
	}
	else if (rank < noderank) {
		return RBTOSSelectRecursive(root->left, rank);
	}
	else {
		return RBTOSSelectRecursive(root->right, rank - noderank);
	}
}

RBT_t* RBTOSSelectIterative(RBT_t* root, int rank)
{
	int noderank;
	for (noderank = root->left->size + 1; rank != noderank; noderank = root->left->size + 1) {
		if (rank < noderank) {
			root = root->left;
		}
		else {
			root = root->right;
			rank = rank - noderank;
		}
	}
	return root;
}

int RBTOSRank(RBTPointers_t* tree, RBT_t* node)
{
	int rank;
	for (rank = node->left->size + 1; node != tree->root; node = node->parent) {
		if (node == node->parent->right) {
			rank = rank + node->parent->left->size + 1;
		}
	}
	return rank;
}

int RBTOSKeyRank(RBTPointers_t* tree, int key)
{
	int rank;
	RBT_t* node;
	node = tree->root;
	rank = node->left->size + 1;
	while (node != tree->nil && key != node->key) {
		if (key < node->key) {
			node = node->left;
			rank = rank - node->right->size - 1;
		}
		else {
			node = node->right;
			rank = rank + node->left->size + 1;
		}
	}
	if (node == tree->nil) {
		rank = FAILURE;
	}
	return rank;
}

RBT_t* RBTSearch(RBTPointers_t* tree, int key)
{
	RBT_t* node;
	node = tree->root;
	while (node != tree->nil && key != node->key) {
		node = (key < node->key) ? node->left : node->right;
	}
	return node;
}

void RBTPrintInorder(RBTPointers_t* tree, RBT_t* root, int hcounter, int bhcounter)
{
	if (root != tree->nil) {
		hcounter++;
		if (root->color == BLACK) {
			bhcounter++;
		}
		RBTPrintInorder(tree, root->left, hcounter, bhcounter);
		numnode++;
		printf("\t\tAddress: %p    Key: %8d    Color: %-5s    Size: %-5d\n",
			root, root->key, (root->color == BLACK) ? "BLACK" : "RED", root->size);
		RBTPrintInorder(tree, root->right, hcounter, bhcounter);
	}
	else {
		if (hcounter > maxheight) {
			maxheight = hcounter;
		}
		if (hcounter < minheight) {
			minheight = hcounter;
		}
		if (bhcounter > maxblackheight) {
			maxblackheight = bhcounter;
		}
		if (bhcounter < minblackheight) {
			minblackheight = bhcounter;
		}
	}
	return;
}

void RBTPrintPreorder(RBTPointers_t* tree, RBT_t* root)
{
	if (root != tree->nil) {
		printf("\t\tKey: %8d\n", root->key);
		RBTPrintPreorder(tree, root->left);
		RBTPrintPreorder(tree, root->right);
	}
	return;
}

void RBTPrintPostorder(RBTPointers_t* tree, RBT_t* root)
{
	if (root != tree->nil) {
		RBTPrintPostorder(tree, root->left);
		RBTPrintPostorder(tree, root->right);
		printf("\t\tKey: %8d\n", root->key);
	}
	return;
}