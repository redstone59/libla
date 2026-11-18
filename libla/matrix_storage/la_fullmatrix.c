#include "la_fullmatrix.h"

#include <stdlib.h>
#include "../la_common.h"

static float FullMatrix_GetAtIndex(Matrix *self, uint64_t index) {
    return self->cells[index];
}

static float FullMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    panic_if(self->cells == NULL,          "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || col >= self->cols, "Attempted to index column outside of matrix bounds");

    return FullMatrix_GetAtIndex(self, Matrix_CellToIndex(self, row, col));
}

static float FullMatrix_SetIndex(Matrix *self, uint64_t index, float value) {
    not_implemented;
}

static float FullMatrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    not_implemented;
}

static Matrix FullMatrix_GetRow(Matrix *self, uint64_t row) {
    not_implemented;
}

static Matrix FullMatrix_GetCol(Matrix *self, uint64_t col) {
    not_implemented;
}

static Matrix FullMatrix_SetRow(Matrix *self, uint64_t row, Matrix values) {
    not_implemented;
}

static Matrix FullMatrix_SetCol(Matrix *self, uint64_t col, Matrix values) {
    not_implemented;
}

static Matrix FullMatrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB) {
    not_implemented;
}

static Matrix FullMatrix_SwapCols(Matrix *self, uint64_t colA, uint64_t colB) {
    not_implemented;
}

static Matrix FullMatrix_MultiplyRow(Matrix *self, uint64_t row, float multiplier) {
    not_implemented;
}

static Matrix FullMatrix_AddMultipleOfRow(Matrix *self, uint64_t rowA, uint64_t rowB, float multiplier) {
    not_implemented;
}

Matrix FullMatrix_New(uint64_t rows, uint64_t cols, float* cells) {
    return (Matrix){
        .rows = rows,
        .cols = cols,
        .kind = LA_MATKIND_FULL,
        .cells = cells,

        .methods = {
            .GetAtIndex = FullMatrix_GetAtIndex,
            .GetCell = FullMatrix_GetCell,
            .SetIndex = FullMatrix_SetIndex,
            .SetCell = FullMatrix_SetCell,
            .GetRow = FullMatrix_GetRow,
            .GetCol = FullMatrix_GetCol,
            .SetRow = FullMatrix_SetRow,
            .SetCol = FullMatrix_SetCol,
            .SwapRows = FullMatrix_SwapRows,
            .SwapCols = FullMatrix_SwapCols,
            .MultiplyRow = FullMatrix_MultiplyRow,
            .AddMultipleOfRow = FullMatrix_AddMultipleOfRow,
        }
    };
}