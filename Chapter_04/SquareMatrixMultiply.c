#include "SquareMatrixMultiply.h"
#include "SquareMatrixMultiply_struct.h"

/* iterative algorithm */
int* SquareMatrixMultiply(int* matrixA, int* matrixB, int* matrixC, int n) // n - number of rows/columns
{
	int i, j, k, sum;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sum = 0;
			for (k = 0; k < n; k++) {
				sum = sum + matrixA[i * n + k] * matrixB[k * n + j];
			}
			matrixC[i * n + j] = sum;
		}
	}
	return matrixC;
}

/* recursive algorithm */
int* SquareMatrixMultiply(int* matrixA, int* matrixB, int* matrixC, int n) // n - number of rows/columns
{

	return;
}

/* Strassen's algorithm */