/* Chapter 15.2 | Matrix-Chain-Multiplication */
/* Exercise 15.2-2 | Matrix-Chain-Multiplication */

#include "MatrixChainMultiplication_common.h"
#include "MatrixChainMultiplication_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 4
#define RANDOM(a,b) rand() % (b - a + 1) + a

Matrix_t* MatrixSequenceMultiply(MSequence_t* seq);
Matrix_t* CreateMatrix(int row, int col);
void PrintMatrix(Matrix_t* m);
Matrix_t* MatrixSequenceMultiplyGeneral(MSequence_t* seq);

#if PRINTMATRIXNAME
extern int name;
#endif // PRINTMATRIXNAME

MSequence_t* allm;

int main(void)
{
	int i, j, n, row, col, tmp, cond, action;
	MSequence_t seq, allmatrices;
	Matrix_t* matrix, * matrix2;
	char* list = "\tList of action:\n-1 (EXIT), 0 (List of action), "
		"1 (MatrixSequenceMultiply), 2 (MatrixSequenceMultiplyGeneral), 3 (PrintAllMatrices), 4 (CompareMatrices)\n\n";
	printf(list);
	allm = &allmatrices;
	matrix = matrix2 = NULL;
	n = 0;
	printf("Please enter the number of matrices from 1 to 26: ");
	if (scanf("%d", &n) <= 0) {
		printf("\n\n\t| ERROR | Incorrect input |\n");
		return FAILURE;
	}
	if (n < 1 || n > 26) {
		printf("\n\n\t| ERROR | Incorrect input. Number must be between 1 and 26 |\n");
		return FAILURE;
	}
	seq.p = 0;
	if ((seq.m = malloc(sizeof(Matrix_t*) * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	allmatrices.p = 0;
	if ((allmatrices.m = malloc(sizeof(Matrix_t*) * n * 100)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return FAILURE;
	}
	while (seq.p < n) {
		printf("Please enter the dimension of matrix #%d, \"ROWS, COLUMNS\": ", seq.p + 1);
		if (scanf("%d, %d", &row, &col) <= 0) {
			printf("\n\n\t| ERROR | Incorrect input |\n");
			return FAILURE;
		}
		if ((matrix = CreateMatrix(row, col)) == NULL) {
			return FAILURE;
		}
		tmp = row * col;
		for (i = 0; i < tmp; i++) {
			matrix->el[i] = RANDOM(MIN, MAX);
		}
		seq.m[seq.p++] = matrix;
	}
#if PRINTMATRIXNAME
	name = 26;
#endif // PRINTMATRIXNAME
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
			matrix = MatrixSequenceMultiply(&seq);
			PrintMatrix(matrix);
			break;
		case 2:
			matrix2 = MatrixSequenceMultiplyGeneral(&seq);
			PrintMatrix(matrix2);
			break;
		case 3:
			printf("PrintAllMatrices:\n\n");
			for (i = 0; i < seq.p; i++) {
				PrintMatrix(seq.m[i]);
			}
			break;
		case 4:
			if (matrix != NULL && matrix2 != NULL && (j = matrix->row * matrix->col) == matrix2->row * matrix2->col) {
				tmp = 0;
				for (i = 0; i < j; i++) {
					if (matrix->el[i] != matrix2->el[i]) {
						tmp++;
					}
				}
				if (tmp > 0) {
					printf("\tMatrices is not equal (%d mismathces)\n", tmp);
				}
				else {
					printf("\tMatrices is equal\n");
				}
			}
			break;
		default:
			printf("\n\n\t| ERROR | Incorrect input |\n");
			break;
		}
	}
	while (allmatrices.p > 0) {
		free(allmatrices.m[--allmatrices.p]);
	}
	return SUCCESS;
}