#include "RedBlackTreeInterval.h"

extern int minheight;
extern int maxheight;
extern int minblackheight;
extern int maxblackheight;
extern int numnode;

RBT_t* RBTCreateNode(Interval_t i)
{
	RBT_t* node;
	if ((node = malloc(sizeof(RBT_t))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return NULL;
	}
	node->invl.low = i.low;
	node->invl.high = i.high;
	return node;
}

void RBTInsert(RBTPointers_t* tree, RBT_t* newnode)
{
	RBT_t* node, * prev;
	prev = tree->nil;
	node = tree->root;
	while (node != tree->nil) {
		prev = node;
		node = (newnode->invl.low < node->invl.low) ? node->left : node->right;
	}
	newnode->parent = prev;
	if (prev == tree->nil) {
		tree->root = newnode;
	}
	else if (newnode->invl.low < prev->invl.low) {
		prev->left = newnode;
	}
	else {
		prev->right = newnode;
	}
	newnode->left = newnode->right = tree->nil;
	newnode->color = RED;
	newnode->max = newnode->invl.high;
	RBTIRecalculateMaxUpper(tree, newnode);
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
	node->max = RBTIIntervalMaximumOf(tree, node);
	rightchild->max = RBTIIntervalMaximumOf(tree, rightchild);
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
	node->max = RBTIIntervalMaximumOf(tree, node);
	leftchild->max = RBTIIntervalMaximumOf(tree, leftchild);
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
	}
	else if (delnode->right == tree->nil) {
		x = delnode->left;
		RBTTransplant(tree, delnode, delnode->left);
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
	}
	RBTIRecalculateMaxUpper(tree, x);
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

int RBTIIntervalMaximumOf(RBTPointers_t* tree, RBT_t* node)
{
	int max;
	max = node->invl.high;
	if (node->left != tree->nil && node->left->max > max) {
		max = node->left->max;
	}
	if (node->right != tree->nil && node->right->max > max) {
		max = node->right->max;
	}
	return max;
}

void RBTIRecalculateMaxUpper(RBTPointers_t* tree, RBT_t* node)
{
	for (node = node->parent; node != tree->nil; node = node->parent) {
		node->max = RBTIIntervalMaximumOf(tree, node);
	}
	return;
}

RBT_t* RBTMinimum(RBTPointers_t* tree, RBT_t* root)
{
	while (root->left != tree->nil) {
		root = root->left;
	}
	return root;
}

RBT_t* RBTMaximum(RBTPointers_t* tree, RBT_t* root)
{
	while (root->right != tree->nil) {
		root = root->right;
	}
	return root;
}

RBT_t* RBTSuccessor(RBTPointers_t* tree, RBT_t* root)
{
	RBT_t* prev;
	if (root->right != tree->nil) {
		return RBTMinimum(tree, root->right);
	}
	prev = root->parent;
	while (prev != tree->nil && root == prev->right) {
		root = prev;
		prev = prev->parent;
	}
	return prev;
}

RBT_t* RBTPredecessor(RBTPointers_t* tree, RBT_t* root)
{
	RBT_t* prev;
	if (root->left != tree->nil) {
		return RBTMaximum(tree, root->left);
	}
	prev = root->parent;
	while (prev != tree->nil && root == prev->left) {
		root = prev;
		prev = prev->parent;
	}
	return prev;
}

RBT_t* RBTISearch(RBTPointers_t* tree, Interval_t i)
{
	RBT_t* node;
	node = tree->root;
	while (node != tree->nil && (i.low > node->invl.high || node->invl.low > i.high)) {		/* node != tree->nil && !(i.low <= node->invl.high && node->invl.low <= i.high) */
		node = (node->left != tree->nil && node->left->max >= i.low) ? node->left : node->right;
	}
	return node;
}

RBT_t* RBTISearchWithMinLowEndpoint(RBTPointers_t* tree, Interval_t i)
{
	RBT_t* node;
	node = tree->root;
	while (node != tree->nil && (i.low > node->invl.high || node->invl.low > i.high)) {		/* node != tree->nil && !(i.low <= node->invl.high && node->invl.low <= i.high) */
		node = (node->left != tree->nil && node->left->max >= i.low) ? node->left : node->right;
	}
	if (node != tree->nil) {
		while (node->left != tree->nil && node->left->invl.high >= i.low) {
			node = node->left;
		}
	}
	return node;
}

RBT_t* RBTISearchOI(RBTPointers_t* tree, Interval_t oi)
{
	RBT_t* node;
	node = tree->root;
	while (node != tree->nil && (oi.low >= node->invl.high || node->invl.low >= oi.high)) {		/* node != tree->nil && !(oi.low < node->invl.high && node->invl.low < oi.high) */
		node = (node->left != tree->nil && node->left->max > oi.low) ? node->left : node->right;
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
		RBTPrintNode(tree, root);
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

void RBTPrintNode(RBTPointers_t* tree, RBT_t* node)
{
	RBT_t* pred, * succ;
	pred = RBTPredecessor(tree, node);
	succ = RBTSuccessor(tree, node);
	if (succ != tree->nil && pred != tree->nil) {
		printf("Addr: %p   Interval: %8d, %-8d   Max: %8d   Col: %-5s   PredKey: %8d, %-8d   SuccKey: %8d, %-8d\n",
			node, node->invl.low, node->invl.high, node->max, (node->color == BLACK) ? "BLACK" : "RED",
			pred->invl.low, pred->invl.high, succ->invl.low, succ->invl.high);
	}
	else if (succ != tree->nil) {
		printf("Addr: %p   Interval: %8d, %-8d   Max: %8d   Col: %-5s   PredKey: %8s, %-8s   SuccKey: %8d, %-8d\n",
			node, node->invl.low, node->invl.high, node->max, (node->color == BLACK) ? "BLACK" : "RED",
			"NIL", "NIL", succ->invl.low, succ->invl.high);
	}
	else {
		printf("Addr: %p   Interval: %8d, %-8d   Max: %8d   Col: %-5s   PredKey: %8d, %-8d   SuccKey: %8s, %-8s\n",
			node, node->invl.low, node->invl.high, node->max, (node->color == BLACK) ? "BLACK" : "RED",
			pred->invl.low, pred->invl.high, "NIL", "NIL");
	}
	return;
}