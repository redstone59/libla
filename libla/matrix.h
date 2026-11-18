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
    void (*SetIndex)(Matrix *self, uint64_t index, float value);
    void (*SetCell)(Matrix *self, uint64_t row, uint64_t col, float value);
} MatrixVTable;

struct Matrix {
    uint64_t rows;
    uint64_t cols;
    uint64_t count;

    MatrixKind kind;

    union {
        float *asVec;
        float **asArrays;
    } cells;

    MatrixVTable methods;
};


Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells);
void Matrix_Destroy(Matrix* self);

float Matrix_GetAtIndex(Matrix *self, uint64_t index);
float Matrix_GetCell(Matrix *self, uint64_t row, uint64_t col);
void Matrix_SetIndex(Matrix *self, uint64_t index, float value);
void Matrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value);

Matrix Matrix_GetRow(Matrix *self, uint64_t row);
Matrix Matrix_GetCol(Matrix *self, uint64_t col);
void Matrix_SetRow(Matrix *self, uint64_t row, Matrix values);
void Matrix_SetCol(Matrix *self, uint64_t col, Matrix values);

void Matrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB);
void Matrix_SwapCols(Matrix *self, uint64_t, uint64_t);
void Matrix_MultiplyRow(Matrix *self, uint64_t row, float multiplier);
/** `rowA` = `rowA` + `multiplier` * `rowB` */
void Matrix_AddMultipleOfRow(Matrix *self, uint64_t rowA, uint64_t rowB, float multiplier);

uint64_t Matrix_CellToIndex(Matrix* self, uint64_t row, uint64_t col);
void Matrix_Print(Matrix* self);

#endif // LA_MATRIX_H_