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

static void FullMatrix_SetIndex(Matrix *self, uint64_t index, float value) {
    self->cells[index] = value;
}

static void FullMatrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    FullMatrix_SetIndex(self, Matrix_CellToIndex(self, row, col), value);
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
            .SetCell = FullMatrix_SetCell
        }
    };
}