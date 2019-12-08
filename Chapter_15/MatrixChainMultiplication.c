#include "MatrixChainMultiplication.h"

#if PRINTMATRIXNAME
int name;
#endif // PRINTMATRIXNAME

extern MSequence_t* allm;

Matrix_t* MatrixSequenceMultiply(MSequence_t* seq)
{
	int* mstable; // mstable - M-table + S-table
	Matrix_t* result;
	MatrixChainOrder(seq, &mstable);
	result = MatrixChainMultiply(seq, mstable, 1, seq->p);
	free(mstable);
	return result;
}

Matrix_t* MatrixChainMultiply(MSequence_t* seq, int* mstable, int i, int j)
{
	Matrix_t* ma, * mb;
	if (i == j) {
		return seq->m[i - 1];
	}
	else {
		ma = MatrixChainMultiply(seq, mstable, i, mstable[stitem(i, j, seq->p)]);
		mb = MatrixChainMultiply(seq, mstable, mstable[stitem(i, j, seq->p)] + 1, j);
#if PRINTMATRIXNAME
		printf("%s * %s\n", ma->name, mb->name);
#endif // PRINTMATRIXNAME
		return MatrixMultiply(ma, mb);
	}
}

void MatrixChainOrder(MSequence_t* seq, int** mstable)
{
	int i, j, k, l, n, min;
	int* mt, * st, * dim; // mt - M-table; st - S-table
	n = seq->p;
	if ((dim = malloc(sizeof(int) * (n + 1))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	if (seq->p > 0) {
		dim[0] = seq->m[0]->row;
	}
	for (i = 0; i < seq->p; i++) {
		dim[i + 1] = seq->m[i]->col;
	}
	if ((mt = st = malloc(sizeof(int) * n * n)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return;
	}
	for (i = 1; i <= n; i++) {
		mt[mtitem(i, i, n)] = 0;
	}
	for (l = 2; l <= n; l++) {
		for (i = 1; i <= n - l + 1; i++) {
			j = i + l - 1;
			mt[mtitem(i, j, n)] = INT_MAX;
			for (k = i; k <= j - 1; k++) {
				min = mt[mtitem(i, k, n)] + mt[mtitem(k + 1, j, n)] + dim[i - 1] * dim[k] * dim[j];
				if (min < mt[mtitem(i, j, n)]) {
					mt[mtitem(i, j, n)] = min;
					st[stitem(i, j, n)] = k;
				}
			}
		}
	}
	*mstable = mt;
	free(dim);
	return;
}

Matrix_t* MatrixMultiply(Matrix_t* ma, Matrix_t* mb)
{
	int i, j, k;
	long long int sum;
	Matrix_t* mc;
	if (ma->col != mb->row) {
		printf("\n\n\t| ERROR | Incompatible dimensions |\n");
		return NULL;
	}
	if ((mc = CreateMatrix(ma->row, mb->col)) == NULL) {
		printf("\n\n\t| ERROR | Matrix not created |\n");
		return NULL;
	}
	for (i = 0; i < ma->row; i++) {
		for (j = 0; j < mb->col; j++) {
			sum = 0;
			for (k = 0; k < ma->col; k++) {
				sum = sum + ma->el[i * ma->col + k] * mb->el[k * mb->col + j];
			}
			mc->el[i * mc->col + j] = sum;
		}
	}
	return mc;
}

Matrix_t* CreateMatrix(int row, int col)
{
#if PRINTMATRIXNAME
	int i, k;
#endif // PRINTMATRIXNAME
	Matrix_t* matrix;
	if ((matrix = malloc(sizeof(Matrix_t))) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return NULL;
	}
	matrix->row = row;
	matrix->col = col;
#if PRINTMATRIXNAME
	k = name;
	for (i = 0, k = k / NUMBEROFLETTERS; k > 0; k = k / NUMBEROFLETTERS) {
		i++;
	}
	i++;
	matrix->name[i] = '\0';
	for (k = name, i--; i >= 0; i--) {
		matrix->name[i] = k % NUMBEROFLETTERS + 'A';
		k = k / NUMBEROFLETTERS - 1;
	}
	name++;
#endif // PRINTMATRIXNAME
	if ((matrix->el = malloc(sizeof(long long int) * matrix->row * matrix->col)) == NULL) {
		printf("\n\n\t| ERROR | Memory allocator error. No memory allocated |\n");
		return NULL;
	}
	allm->m[allm->p++] = matrix;
	return matrix;
}

void PrintMatrix(Matrix_t* m)
{
#if PRINTMATRIXBODY
	int i, j;
#endif // PRINTMATRIXBODY
	int row, col;
	row = m->row;
	col = m->col;
#if PRINTMATRIXNAME
	printf("Matrix %s (%d x %d):\n", m->name, m->row, m->col);
#else
	printf("Matrix (%d x %d):\n", m->row, m->col);
#endif // PRINTMATRIXNAME
#if PRINTMATRIXBODY
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%12lli ", m->el[i * col + j]);
		}
		putchar('\n');
	}
	putchar('\n');
#endif // PRINTMATRIXBODY
	return;
}

Matrix_t* MatrixSequenceMultiplyGeneral(MSequence_t* seq)
{
	int i, j;
	Matrix_t* ma, * mb;
	i = 0;
	ma = seq->m[i++];
	j = seq->p;
	while (i < j) {
		mb = seq->m[i++];
#if PRINTMATRIXNAME
		printf("%s * %s\n", ma->name, mb->name);
#endif // PRINTMATRIXNAME
		ma = MatrixMultiply(ma, mb);
	}
	return ma;
}