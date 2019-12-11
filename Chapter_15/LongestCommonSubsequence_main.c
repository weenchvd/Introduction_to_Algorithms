/* Chapter 15.4 | Longest-Common-Subsequence */

#include "LongestCommonSubsequence_common.h"
#include "LongestCommonSubsequence_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 4
#define RANDOM(a,b) rand() % (b - a + 1) + a

void LCSFindAndPrint(Sequence_t* x, Sequence_t* y);
void PrintStrings(Sequence_t* x, Sequence_t* y);

int main(void)
{
	int i, j, cond, action;
	Sequence_t seq1, seq2;
	SSet_t set;
	char* list = "\tList of action: -1 (EXIT), 0 (List of action),\n"
		"1 (CreateStrings), 2 (CreateRandomStrings), 3 (PrintStrings), 4 (LCSFindAndPrint)\n\n";
	printf(list);
	seq1.s = seq2.s = NULL;
	set.sp = 0;
	cond = TRUE;
	while (cond) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		switch (action) {
		case -1:
			cond = FALSE;
			break;
		case 0:
			printf(list);
			break;
		case 1:
			if (set.sp >= SSTACKSIZE - 2) {
				while (set.sp > 0) {
					free(set.sstack[--set.sp]);
				}
			}
			printf("Please enter the number of characters for the sequence #1: ");
			if (scanf("%d", &seq1.size) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (seq1.size < 1) {
				printf("\n\n\t| ERROR | Incorrect input. Number must be greater than 0 |\n");
				return FAILURE;
			}
			printf("Please enter the number of characters for the sequence #2: ");
			if (scanf("%d", &seq2.size) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (seq2.size < 1) {
				printf("\n\n\t| ERROR | Incorrect input. Number must be greater than 0 |\n");
				return FAILURE;
			}
			if ((seq1.s = malloc(sizeof(char) * (seq1.size + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			if ((seq2.s = malloc(sizeof(char) * (seq2.size + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			set.sstack[set.sp++] = seq1.s;
			set.sstack[set.sp++] = seq2.s;
			printf("Please enter the characters for the sequence #1: ");
			if (scanf("%s", seq1.s) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			seq1.s[seq1.size] = '\0';
			printf("Please enter the characters for the sequence #2: ");
			if (scanf("%s", seq2.s) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			seq2.s[seq2.size] = '\0';
			break;
		case 2:
			if (set.sp >= SSTACKSIZE - 2) {
				while (set.sp > 0) {
					free(set.sstack[--set.sp]);
				}
			}
			seq1.size = RANDOM(10, 100);
			if ((seq1.s = malloc(sizeof(char) * (seq1.size + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			seq2.size = RANDOM(10, 100);
			if ((seq2.s = malloc(sizeof(char) * (seq2.size + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			set.sstack[set.sp++] = seq1.s;
			set.sstack[set.sp++] = seq2.s;
			for (i = 0; i < seq1.size; i++) {
				seq1.s[i] = RANDOM('A', 'Z');
			}
			seq1.s[i] = '\0';
			for (i = 0; i < seq2.size; i++) {
				seq2.s[i] = RANDOM('A', 'Z');
			}
			seq2.s[i] = '\0';
			break;
		case 3:
			if (seq1.s != NULL && seq2.s != NULL) {
				PrintStrings(&seq1, &seq2);
			}
			break;
		case 4:
			if (seq1.s != NULL && seq2.s != NULL) {
				LCSFindAndPrint(&seq1, &seq2);
			}
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	while (set.sp > 0) {
		free(set.sstack[--set.sp]);
	}
	return SUCCESS;
}