/* Chapter 16.1 | Activity-Selection-Problem */

#include "ActivitySelectionProblem_common.h"
#include "ActivitySelectionProblem_struct.h"
#include <stdio.h>
#include <stdlib.h>

void RecursiveActivitySelector(AS_t* as, int k);
void GreedyActivitySelector(AS_t* as);

int main(void)
{
	int i, j, cond, action;
	AS_t as;
	char* list = "\tList of action: -1 (EXIT), 0 (List of action),\n"
		"1 (RecursiveActivitySelector), 2 (GreedyActivitySelector)\n\n";
	printf(list);
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
			printf("Please enter the number of activities: ");
			if (scanf("%d", &as.n) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (as.n < 1) {
				printf("\n\n\t| ERROR | Incorrect input. Number must be greater than 0 |\n");
				return FAILURE;
			}
			if ((as.s = malloc(sizeof(int) * (as.n + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			if ((as.f = malloc(sizeof(int) * (as.n + 1))) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			printf("Please enter the activities in monotonically increasing order of finish time\n");
			as.s[0] = as.f[0] = 0;
			for (i = 1; i <= as.n; i++) {
				printf("Please enter the beginning and end of activity #%d, \"START, FINISH\": ", i);
				if (scanf("%d, %d", &as.s[i], &as.f[i]) <= 0) {
					printf("\n\n\t| ERROR | Incorrect input |\n");
					return FAILURE;
				}
			}
			j = TRUE;
			for (i = 1; i <= as.n; i++) {
				if (as.f[i - 1] > as.f[i]) {
					j = FALSE;
					break;
				}
			}
			if (j == TRUE) {
				printf("The resulting set of selected activities is: ");
				RecursiveActivitySelector(&as, 0);
				printf("\b\b \n");
			}
			else {
				printf("\n\n\t| ERROR | Incorrect input. The finish time must be in monotonically increasing order |\n");
			}
			as.n = 0;
			free(as.s);
			free(as.f);
			break;
		case 2:
			printf("Please enter the number of activities: ");
			if (scanf("%d", &as.n) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (as.n < 1) {
				printf("\n\n\t| ERROR | Incorrect input. Number must be greater than 0 |\n");
				return FAILURE;
			}
			if ((as.s = malloc(sizeof(int) * as.n)) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			if ((as.f = malloc(sizeof(int) * as.n)) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			printf("Please enter the activities in monotonically increasing order of finish time\n");
			for (i = 0; i < as.n; i++) {
				printf("Please enter the beginning and end of activity #%d, \"START, FINISH\": ", i + 1);
				if (scanf("%d, %d", &as.s[i], &as.f[i]) <= 0) {
					printf("\n\n\t| ERROR | Incorrect input |\n");
					return FAILURE;
				}
			}
			j = TRUE;
			for (i = 1; i < as.n; i++) {
				if (as.f[i - 1] > as.f[i]) {
					j = FALSE;
					break;
				}
			}
			if (j == TRUE) {
				printf("The resulting set of selected activities is: ");
				GreedyActivitySelector(&as);
				printf("\b\b \n");
			}
			else {
				printf("\n\n\t| ERROR | Incorrect input. The finish time must be in monotonically increasing order |\n");
			}
			as.n = 0;
			free(as.s);
			free(as.f);
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}