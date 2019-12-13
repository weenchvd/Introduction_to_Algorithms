/* Chapter 15.5 | Optimal-Binary-Search-Trees */
/* Exercise 15.5-1 | Optimal-Binary-Search-Trees */

#include "OptimalBinarySearchTrees_common.h"
#include "OptimalBinarySearchTrees_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 4
#define RANDOM(a,b) rand() % (b - a + 1) + a

void BSTOptimalConstruct(BSTPr_t* pr);

int main(void)
{
	int i, j, cond, action;
	BSTPr_t pr;
	char* list = "\tList of action: -1 (EXIT), 0 (List of action),\n"
		"1 (CreateSequenceOfProbabilities), 2 (BSTOptimalConstruct)\n\n";
	printf(list);
	pr.p = pr.q = NULL;
	pr.n = 0;
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
			printf("Please enter the number of keys: ");
			if (scanf("%d", &pr.n) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (pr.n < 1) {
				printf("\n\n\t| ERROR | Incorrect input. Number must be greater than 0 |\n");
				return FAILURE;
			}
			if ((pr.p = malloc(sizeof(int) * (pr.n + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			if ((pr.q = malloc(sizeof(int) * (pr.n + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			pr.p[0] = 0;
			for (i = 1; i <= pr.n; i++) {
				printf("Please enter the probability #%d for the p-sequence as a percentage: ", i);
				if (scanf("%d", &pr.p[i]) <= 0) {
					printf("\n\n\t| ERROR | Incorrect input |\n");
					return FAILURE;
				}
			}
			for (i = 0; i <= pr.n; i++) {
				printf("Please enter the probability #%d for the q-sequence as a percentage: ", i);
				if (scanf("%d", &pr.q[i]) <= 0) {
					printf("\n\n\t| ERROR | Incorrect input |\n");
					return FAILURE;
				}
			}
			break;
		case 2:
			if (pr.n > 0) {
				j = 0;
				for (i = 1; i <= pr.n; i++) {
					j += pr.p[i];
				}
				for (i = 0; i <= pr.n; i++) {
					j += pr.q[i];
				}
				if (j == 100) {
					printf("BSTOptimalConstruct:\n");
					BSTOptimalConstruct(&pr);
				}
				else {
					printf("The sum of probabilities is not equal to 100\n");
				}
			}
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	free(pr.p);
	free(pr.q);
	return SUCCESS;
}