#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct Matrix {
	int row;					// rows in matrix
	int col;					// column in matrix
	long long int* el;			// element of matrix
#if PRINTMATRIXNAME
	char name[8];
#endif // PRINTMATRIXNAME
} Matrix_t;

typedef struct MatrixSequence {
	struct Matrix** m;			// stack for matrix
	int p;						// stack pointer
} MSequence_t;

#endif