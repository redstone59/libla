#ifndef LA_MATRIX_H_
#define LA_MATRIX_H_

#include <stdint.h>

typedef enum MatrixKind {
    LA_MATKIND_FULL,
    LA_MATKIND_SCALAR,

    LA_MATKIND_SPARSE,
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

    MatrixVTable methods;
} Matrix;

typedef struct MatrixVTable {
    float (*GetAtIndex)(Matrix, uint64_t);
    float (*GetCell)(Matrix, uint64_t, uint64_t);
    float (*SetIndex)(Matrix, uint64_t, float);
    float (*SetCell)(Matrix, uint64_t, uint64_t, float);

    Matrix (*GetRow)(Matrix*, uint64_t);
    Matrix (*GetCol)(Matrix*, uint64_t, Matrix);
    Matrix (*SetRow)(Matrix*, uint64_t);
    Matrix (*SetCol)(Matrix*, uint64_t, Matrix);

    Matrix (*SwapRows)(Matrix*, uint64_t, uint64_t);
    Matrix (*SwapCols)(Matrix*, uint64_t, uint64_t);
    Matrix (*MultiplyRow)(Matrix*, uint64_t, float);
    /** `rowA` = `rowA` + `multiplier` * `rowB` */
    Matrix (*AddMultipleOfRow)(Matrix*, uint64_t, uint64_t, float);
} MatrixVTable;

Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells);
void Matrix_Destroy(Matrix* self);

uint64_t Matrix_CellToIndex(Matrix* self, uint64_t row, uint64_t col);
void Matrix_Print(Matrix* self);

#endif // LA_MATRIX_H_