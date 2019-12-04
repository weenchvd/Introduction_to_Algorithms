/* Chapter 15.1 | Rod-Cutting */
/* Exercise 15.1-3 | Rod-Cutting */
/* Exercise 15.1-4 | Rod-Cutting */
/* Exercise 15.1-5 | Rod-Cutting */

#include "RodCutting_common.h"
#include "RodCutting_struct.h"
#include <stdio.h>
#include <stdlib.h>

int MemoizedCutRod(int* price, int n);
int BottomUpCutRod(int* price, int n);
void PrintCutRodSolution(int* price, int n);
void PrintCutRodSolutionNonFreeCut(int* price, int n, int cutcost);
void PrintExtendedMemoizedCutRodSolution(int* price, int n);
void PrintFibonacciNumber(int n);

int main(void)
{
	int i, j, n, tmp, action;
	int* price;
	char* list = "\tList of action:\n 0 (List of action), "
		"1 (MemoizedCutRod), 2 (BottomUpCutRod), 3 (PrintCutRodSolution), 4 (PrintCutRodSolutionNonFreeCut), "
		"5 (PrintExtendedMemoizedCutRodSolution), 6 (PrintFibonacciNumber)\n\n";
	n = 0;
	printf("Please enter the length of a rod: ");
	if (scanf("%d", &n) <= 0) {
		printf("\n\n\t| ERROR | Incorrect input |\n");
		return FAILURE;
	}
	if (n < 0) {
		return FAILURE;
	}
	else if ((price = malloc(sizeof(int) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	price[0] = 0;
	for (i = 1; i <= n; i++) {
		printf("Please enter the price of a rod with a length of %d: ", i);
		if (scanf("%d", &price[i]) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
	}
	printf(list);
	while (TRUE) {
		printf("Please enter an action: ");
		if (scanf("%d", &action) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		switch (action) {
		case 0:
			printf(list);
			break;
		case 1:
			printf("\tMemoizedCutRod: %d\n", MemoizedCutRod(price, n));
			break;
		case 2:
			printf("\tBottomUpCutRod: %d\n", BottomUpCutRod(price, n));
			break;
		case 3:
			printf("\tPrintCutRodSolution:\n");
			PrintCutRodSolution(price, n);
			break;
		case 4:
			tmp = 0;
			printf("Please enter the cost of making a cut of a rod: ");
			if (scanf("%d", &tmp) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (tmp < 0) {
				printf("\n\n\t| ERROR | Incorrect input. Cost must be equal to or greater than 0 |\n");
				break;
			}
			printf("\tPrintCutRodSolutionNonFreeCut:\n");
			PrintCutRodSolutionNonFreeCut(price, n, tmp);
			break;
		case 5:
			printf("\tPrintExtendedMemoizedCutRodSolution:\n");
			PrintExtendedMemoizedCutRodSolution(price, n);
			break;
		case 6:
			tmp = 0;
			printf("Please enter the number of Fibonacci numbers: ");
			if (scanf("%d", &tmp) <= 0) {
				printf("\n\n\t| ERROR | Incorrect input |\n");
				return FAILURE;
			}
			if (tmp < 1 || tmp > 47) {
				printf("\n\n\t| ERROR | Incorrect input. Number of Fibonacci numbers must be from 1 to 47 |\n");
				break;
			}
			printf("\tPrintFibonacciNumber:\n");
			PrintFibonacciNumber(tmp);
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	return SUCCESS;
}