#ifndef LA_SCALARMATRIX_H_
#define LA_SCALARMATRIX_H_

#include "../matrix.h"

// This matrix type is only used in one case - matrix-scalar addition. This is not recommended to be used by the end-user.
Matrix ScalarMatrix_New(uint64_t rows, uint64_t cols, float *value);

#endif // LA_SCALARMATRIX_H_