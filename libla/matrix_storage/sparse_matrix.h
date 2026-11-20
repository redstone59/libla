#ifndef LA_SPARSE_MATRIX_H_
#define LA_SPARSE_MATRIX_H_

#include "../matrix.h"
#include <stddef.h>

Matrix SparseMatrix_New(uint64_t rows, uint64_t cols, float **vecs, size_t nz, size_t capacity);

#endif // LA_SPARSE_MATRIX_H_