#include "full_matrix.h"

#include <string.h>

#include "../common.h"

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

static void FullMatrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB) {
    float *temp[self->cols];
    memset(temp, 0, sizeof(temp));

    size_t rowSize = self->cols * sizeof(float);
    size_t rowAStart = rowA * self->cols;
    size_t rowBStart = rowB * self->cols;

    memcpy(temp, &self->cells.asFloatVec[rowAStart], rowSize);
    memcpy(&self->cells.asFloatVec[rowAStart], &self->cells.asFloatVec[rowBStart], rowSize);
    memcpy(&self->cells.asFloatVec[rowBStart], temp, rowSize);
}

static MatrixVTable fullMethods = (MatrixVTable) {
    .GetAtIndex = FullMatrix_GetAtIndex,
    .GetCell = FullMatrix_GetCell,
    .SetIndex = FullMatrix_SetIndex,
    .SetCell = FullMatrix_SetCell,

    .SwapRows = FullMatrix_SwapRows,
};

Matrix FullMatrix_New(uint64_t rows, uint64_t cols, float *cells)
{
    return (Matrix){
        .rows = rows,
        .cols = cols,
        .count = rows * cols,
        .kind = LA_MATKIND_FULL,
        .cells.asFloatVec = cells,

        .methods = &fullMethods
    };
}