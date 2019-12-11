#include "LongestCommonSubsequence.h"

void LCSFindAndPrint(Sequence_t* x, Sequence_t* y)
{
	int* ctable;
	char* btable;
	LCSLength(x, y, &ctable, &btable);
	printf("Longest common subsequence:\n                ");
	LCSPrint(y, btable, x->size, y->size);
	putchar('\n');
	free(ctable);
	free(btable);
	return;
}

void LCSLength(Sequence_t* x, Sequence_t* y, int** ctable, char** btable)
{
	int i, j, m, n;
	int* ct;
	char* bt;
	m = x->size;
	n = y->size;
	if ((*ctable = ct = malloc(sizeof(int) * (m + 1) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	if ((*btable = bt = malloc(sizeof(char) * m * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 1; i <= m; i++) {
		ct[ctitem(i, 0, n)] = 0;
	}
	for (j = 0; j <= n; j++) {
		ct[ctitem(0, j, n)] = 0;
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (x->s[i - 1] == y->s[j - 1]) {
				ct[ctitem(i, j, n)] = ct[ctitem((i - 1), (j - 1), n)] + 1;
				bt[btitem(i, j, n)] = UPLEFT;
			}
			else if (ct[ctitem((i - 1), j, n)] >= ct[ctitem(i, (j - 1), n)]) {
				ct[ctitem(i, j, n)] = ct[ctitem((i - 1), j, n)];
				bt[btitem(i, j, n)] = UP;
			}
			else {
				ct[ctitem(i, j, n)] = ct[ctitem(i, (j - 1), n)];
				bt[btitem(i, j, n)] = LEFT;
			}
		}
	}
	return;
}

void LCSPrint(Sequence_t* y, char* bt, int i, int j)
{
	if (i == 0 || j == 0) {
		return;
	}
	if (bt[btitem(i, j, y->size)] == UPLEFT) {
		LCSPrint(y, bt, i - 1, j - 1);
		putchar(y->s[j - 1]);
	}
	else if (bt[btitem(i, j, y->size)] == UP) {
		LCSPrint(y, bt, i - 1, j);
	}
	else {
		LCSPrint(y, bt, i, j - 1);
	}
	return;
}

void PrintStrings(Sequence_t* x, Sequence_t* y)
{
	printf("Sequence #1:    %s (%d)\n", x->s, x->size);
	printf("Sequence #2:    %s (%d)\n", y->s, y->size);
	return;
}

void LCSFindAndPrintWithoutBtable(Sequence_t* x, Sequence_t* y)
{
	int* ctable;
	LCSLengthWithoutBtable(x, y, &ctable);
	printf("Longest common subsequence:\n                ");
	LCSPrintWithoutBtable(x, y, ctable, x->size, y->size);
	putchar('\n');
	free(ctable);
	return;
}

void LCSLengthWithoutBtable(Sequence_t* x, Sequence_t* y, int** ctable)
{
	int i, j, m, n;
	int* ct;
	m = x->size;
	n = y->size;
	if ((*ctable = ct = malloc(sizeof(int) * (m + 1) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 1; i <= m; i++) {
		ct[ctitem(i, 0, n)] = 0;
	}
	for (j = 0; j <= n; j++) {
		ct[ctitem(0, j, n)] = 0;
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (x->s[i - 1] == y->s[j - 1]) {
				ct[ctitem(i, j, n)] = ct[ctitem((i - 1), (j - 1), n)] + 1;
			}
			else if (ct[ctitem((i - 1), j, n)] >= ct[ctitem(i, (j - 1), n)]) {
				ct[ctitem(i, j, n)] = ct[ctitem((i - 1), j, n)];
			}
			else {
				ct[ctitem(i, j, n)] = ct[ctitem(i, (j - 1), n)];
			}
		}
	}
	return;
}

void LCSPrintWithoutBtable(Sequence_t* x, Sequence_t* y, int* ct, int i, int j)
{
	if (i == 0 || j == 0) {
		return;
	}
	if (x->s[i - 1] == y->s[j - 1]) {
		LCSPrintWithoutBtable(x, y, ct, i - 1, j - 1);
		putchar(y->s[j - 1]);
	}
	else if (ct[ctitem((i - 1), j, y->size)] >= ct[ctitem(i, (j - 1), y->size)]) {
		LCSPrintWithoutBtable(x, y, ct, i - 1, j);
	}
	else {
		LCSPrintWithoutBtable(x, y, ct, i, j - 1);
	}
	return;
}

void LCSFindAndPrintWithoutBtableRecursive(Sequence_t* x, Sequence_t* y)
{
	int* ctable;
	LCSLengthWithoutBtableRecursive(x, y, &ctable);
	printf("Longest common subsequence:\n                ");
	LCSPrintWithoutBtable(x, y, ctable, x->size, y->size);
	putchar('\n');
	free(ctable);
	return;
}

void LCSLengthWithoutBtableRecursive(Sequence_t* x, Sequence_t* y, int** ctable)
{
	int i, j, m, n;
	int* ct;
	m = x->size;
	n = y->size;
	if ((*ctable = ct = malloc(sizeof(int) * (m + 1) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 1; i <= m; i++) {
		ct[ctitem(i, 0, n)] = 0;
		for (j = 1; j <= n; j++) {
			ct[ctitem(i, j, n)] = INT_MIN;
		}
	}
	for (j = 0; j <= n; j++) {
		ct[ctitem(0, j, n)] = 0;
	}
	ct[ctitem(m, n, n)] = LCSMemoizedLengthWithoutBtableRecursive(x, y, ct, m, n);
	return;
}

int LCSMemoizedLengthWithoutBtableRecursive(Sequence_t* x, Sequence_t* y, int* ct, int i, int j)
{
	int top, left;
	if (ct[ctitem(i, j, y->size)] == INT_MIN) {
		if (x->s[i - 1] == y->s[j - 1]) {
			ct[ctitem(i, j, y->size)] = LCSMemoizedLengthWithoutBtableRecursive(x, y, ct, i - 1, j - 1) + 1;
		}
		else if ((top = LCSMemoizedLengthWithoutBtableRecursive(x, y, ct, i - 1, j)) >=
			(left = LCSMemoizedLengthWithoutBtableRecursive(x, y, ct, i, j - 1))) {
			ct[ctitem(i, j, y->size)] = top;
		}
		else {
			ct[ctitem(i, j, y->size)] = left;
		}
	}
	return ct[ctitem(i, j, y->size)];
}

void LCSFindAndPrintLength(Sequence_t* x, Sequence_t* y)
{
	printf("Longest common subsequence: %d\n", LCSLengthMinimal(x, y));
	return;
}

int LCSLengthMinimal(Sequence_t* x, Sequence_t* y)
{
	int i, j, m, n, top, topleft;
	char* ms, * ns;
	int* ct;
	if (x->size >= y->size) {
		m = x->size;
		n = y->size;
		ms = x->s;
		ns = y->s;
	}
	else {
		m = y->size;
		n = x->size;
		ms = y->s;
		ns = x->s;
	}
	if ((ct = malloc(sizeof(int) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (j = 0; j <= n; j++) {
		ct[j] = 0;
	}
	for (i = 1; i <= m; i++) {
		top = 0;
		for (j = 1; j <= n; j++) {
			topleft = top;
			top = (i > 1) ? ct[j] : 0;
			if (ms[i - 1] == ns[j - 1]) {
				ct[j] = topleft + 1;
			}
			else if (top >= ct[j - 1]) {
				ct[j] = top;
			}
			else {
				ct[j] = ct[j - 1];
			}
		}
	}
	i = ct[n];
	free(ct);
	return i;
}