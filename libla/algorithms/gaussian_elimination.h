#ifndef LA_GAUSSIAN_ELIMINATION_H_
#define LA_GAUSSIAN_ELIMINATION_H_

#include "../matrix.h"

/**
 * Performs Gaussian elimination in place on the matrix `a`, putting `a` into row-echelon form.
 * 
 * @param a The matrix in which to perform Gaussian elimination on.
 */
void GaussianElimination(Matrix *a);

#endif // LA_GAUSSIAN_ELIMINATION_H_