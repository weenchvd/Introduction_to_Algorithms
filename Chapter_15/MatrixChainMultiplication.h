#ifndef _MATRIXCHAINMULTIPLICATION_H
#define _MATRIXCHAINMULTIPLICATION_H

#include "MatrixChainMultiplication_common.h"
#include "MatrixChainMultiplication_struct.h"
#include <stdio.h>
#include <stdlib.h>

#define NUMBEROFLETTERS 26
#define mtitem(i, j, n) n * (i - 1) + (j - 1)
#define stitem(i, j, n) n * (n - i) + (n - j)

Matrix_t* MatrixSequenceMultiply(MSequence_t* seq);
Matrix_t* MatrixChainMultiply(MSequence_t* seq, int* mstable, int i, int j);
void MatrixChainOrder(MSequence_t* seq, int** mstable);
Matrix_t* MatrixMultiply(Matrix_t* ma, Matrix_t* mb);
Matrix_t* CreateMatrix(int row, int col);
void PrintMatrix(Matrix_t* m);
Matrix_t* MatrixSequenceMultiplyGeneral(MSequence_t* seq);

#endif