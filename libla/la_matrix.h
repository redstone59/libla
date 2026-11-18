#ifndef LA_MATRIX_H_
#define LA_MATRIX_H_

#include <stdint.h>

typedef struct Matrix Matrix;

typedef enum MatrixKind {
    LA_MATKIND_FULL,
    LA_MATKIND_SCALAR,

    LA_MATKIND_SPARSE,
    // LA_MATKIND_CSR,
    // LA_MATKIND_TRIANGULAR,
    // LA_MATKIND_BANDED,
    LA_MATKIND_COUNT
} MatrixKind;

typedef struct MatrixVTable {
    float (*GetAtIndex)(Matrix *self, uint64_t index);
    float (*GetCell)(Matrix *self, uint64_t row, uint64_t col);
    float (*SetIndex)(Matrix *self, uint64_t index, float value);
    float (*SetCell)(Matrix *self, uint64_t row, uint64_t col, float value);

    Matrix (*GetRow)(Matrix *self, uint64_t row);
    Matrix (*GetCol)(Matrix *self, uint64_t col);
    Matrix (*SetRow)(Matrix *self, uint64_t row, Matrix values);
    Matrix (*SetCol)(Matrix *self, uint64_t col, Matrix values);

    Matrix (*SwapRows)(Matrix *self, uint64_t rowA, uint64_t rowB);
    Matrix (*SwapCols)(Matrix *self, uint64_t, uint64_t);
    Matrix (*MultiplyRow)(Matrix *self, uint64_t row, float multiplier);
    /** `rowA` = `rowA` + `multiplier` * `rowB` */
    Matrix (*AddMultipleOfRow)(Matrix *self, uint64_t rowA, uint64_t rowB, float multiplier);
} MatrixVTable;

struct Matrix {
    uint64_t rows;
    uint64_t cols;
    MatrixKind kind;
    
    float *cells;

    MatrixVTable methods;
};


Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells);
void Matrix_Destroy(Matrix* self);

uint64_t Matrix_CellToIndex(Matrix* self, uint64_t row, uint64_t col);
void Matrix_Print(Matrix* self);

#endif // LA_MATRIX_H_