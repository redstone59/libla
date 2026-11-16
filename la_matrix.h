#ifndef LA_MATRIX_H_
#define LA_MATRIX_H_

#include <stdint.h>

typedef enum MatrixKind {
    LA_MATKIND_NONSPARSE,
    LA_MATKIND_SCALAR,
    // LA_MATKIND_CSR,
    // LA_MATKIND_TRIANGULAR,
    // LA_MATKIND_BANDED,
    LA_MATKIND_COUNT
} MatrixKind;

typedef struct Matrix {
    uint64_t rows;
    uint64_t cols;
    MatrixKind kind;

    float *cells;
} Matrix;

Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells);
void Matrix_Destroy(Matrix* self);
float Matrix_GetIndex(Matrix* self, uint64_t index);
float Matrix_GetCell(Matrix* self, uint64_t row, uint64_t col);

int Matrix_GetNonzeroIndicies(Matrix* self);

void Matrix_Print(Matrix* self);

#endif // LA_MATRIX_H_