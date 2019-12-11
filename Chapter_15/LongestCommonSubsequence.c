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