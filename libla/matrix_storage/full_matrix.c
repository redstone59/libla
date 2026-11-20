#include "full_matrix.h"

static float FullMatrix_GetAtIndex(Matrix *self, uint64_t index) {
    return self->cells.asFloatVec[index];
}

static float FullMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    return FullMatrix_GetAtIndex(self, Matrix_CellToIndex(self, row, col));
}

static void FullMatrix_SetIndex(Matrix *self, uint64_t index, float value) {
    self->cells.asFloatVec[index] = value;
}

static void FullMatrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    FullMatrix_SetIndex(self, Matrix_CellToIndex(self, row, col), value);
}

static MatrixVTable fullMethods = (MatrixVTable){
    .GetAtIndex = FullMatrix_GetAtIndex,
    .GetCell = FullMatrix_GetCell,
    .SetIndex = FullMatrix_SetIndex,
    .SetCell = FullMatrix_SetCell
};

Matrix FullMatrix_New(uint64_t rows, uint64_t cols, float *cells)
{
    return (Matrix){
        .rows = rows,
        .cols = cols,
        .count = rows * cols,
        .kind = LA_MATKIND_FULL,
        .cells.asFloatVec = cells,

        .methods = fullMethods
    };
}