#ifndef LA_SPARSE_MATRIX_H_
#define LA_SPARSE_MATRIX_H_

#include "../matrix.h"
#include <stddef.h>

/**
 * Creates a new sparse matrix on the heap.
 * 
 * See: https://en.wikipedia.org/wiki/Sparse_matrix#Coordinate_list_(COO)
 * 
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @param vecs A pointer to 3 equal length arrays in the order row vector, column vector, value vector.
 *             Row and column vectors must contain only integers. 
 * @param nz The number of non-zero elements in the matrix.
 * @param capacity The number of elements that this matrix can hold before resizing. 
 */
Matrix SparseMatrix_New(uint64_t rows, uint64_t cols, float **vecs, size_t nz, size_t capacity);

#endif // LA_SPARSE_MATRIX_H_