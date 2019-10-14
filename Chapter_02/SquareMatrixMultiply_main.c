/* Chapter 4.2 | Square-Matrix-Multiply */

#include <stdio.h>
#include <stdlib.h>
#include "SquareMatrixMultiply_struct.h"

enum returntype { ERROR = -1, SUCCESS };

int* SquareMatrixMultiply(int* matrixA, int* matrixB, int* matrixC, int n);

int main(int argc, char* argv[])
{
	int* matrixA, * matrixB, * matrixC;
	int i, j, n, tmp;
	if (argc < 2) {
		printf("\n\n\t| ERROR | Please enter the number of rows/columns as program arguments |\n");
		return ERROR;
	}
	if ((n = atoi(argv[1])) < 1) {
		printf("\n\n\t| ERROR | The number of rows/columns must be a positive integer |\n");
		return ERROR;
	}
	if ((matrixA = malloc(sizeof(int) * n * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	if ((matrixB = malloc(sizeof(int) * n * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	if ((matrixC = malloc(sizeof(int) * n * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return ERROR;
	}
	putchar('\n');
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("Please enter an item MatrixA[%d][%d]: ", i + 1, j + 1);
			scanf("%d", &tmp);
			matrixA[i * n + j] = tmp;
		}
	}
	putchar('\n');
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("Please enter an item MatrixB[%d][%d]: ", i + 1, j + 1);
			scanf("%d", &tmp);
			matrixB[i * n + j] = tmp;
		}
	}
	putchar('\n');
	SquareMatrixMultiply(matrixA, matrixB, matrixC, n);
	printf("\nThe result of multiplying MatrixA[%d][%d] by MatrixB[%d][%d] is MatrixC[%d][%d]:\n", n, n, n, n, n, n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf(" %6d", matrixC[i * n + j]);
		}
		putchar('\n');
	}
	free(matrixA);
	free(matrixB);
	free(matrixC);
	return SUCCESS;
}