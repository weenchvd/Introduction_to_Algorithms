/* Exercise 16.2-2 | Greedy-Strategy-Elements */

#include "GreedyStrategyElements_common.h"
#include "GreedyStrategyElements_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 4
#define RANDOM(a,b) rand() % (b - a + 1) + a

void ZeroOneKnapsackConstruct(KI_t* items);

int main(void)
{
	int i, j, cond, action;
	KI_t items;
	char* list = "\tList of action: -1 (EXIT), 0 (List of action),\n"
		"1 (CreateSetOfItems), 2 (ZeroOneKnapsackConstruct)\n\n";
	printf(list);
	items.v = items.w = NULL;
	items.n = items.maxw = 0;
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
			if (items.v != NULL || items.w != NULL) {
				break;
			}
			printf("Please enter the number of items: ");
			if (scanf("%d", &items.n) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (items.n < 1) {
				printf("\n\n\t| ERROR | Incorrect input. Number must be greater than 0 |\n");
				return FAILURE;
			}
			printf("Please enter the maximum weight of the knapsack: ");
			if (scanf("%d", &items.maxw) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (items.maxw < 1) {
				printf("\n\n\t| ERROR | Incorrect input. Number must be greater than 0 |\n");
				return FAILURE;
			}
			if ((items.v = malloc(sizeof(int) * items.n)) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			if ((items.w = malloc(sizeof(int) * items.n)) == NULL) {
				printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
				return FAILURE;
			}
			for (i = 0; i < items.n; i++) {
				printf("Please enter the value of the item #%d: ", i + 1);
				if (scanf("%d", &items.v[i]) <= 0) {
					printf("\n\n\t| ERROR | Incorrect input |\n");
					return FAILURE;
				}
				printf("Please enter the weight of the item #%d: ", i + 1);
				if (scanf("%d", &items.w[i]) <= 0) {
					printf("\n\n\t| ERROR | Incorrect input |\n");
					return FAILURE;
				}
			}
			break;
		case 2:
			if (items.n > 0 && items.maxw > 0) {
				printf("ZeroOneKnapsackConstruct:\n");
				ZeroOneKnapsackConstruct(&items);
			}
			else {
				printf("Number or weight of items lower than 1\n");
			}
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	free(items.v);
	free(items.w);
	return SUCCESS;
}