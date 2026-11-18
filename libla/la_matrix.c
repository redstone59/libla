#include "la_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include "la_common.h"

Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells) {
    return (Matrix) {
        .rows = rows,
        .cols = cols,
        .kind = LA_MATKIND_FULL,
        .cells = cells,

        .methods = {0}
    };
}

void Matrix_Destroy(Matrix* self) {
    if (self->cells == NULL) {
        return;
    }

    free(self->cells);
    self->cells = NULL;
}

float Matrix_GetAtIndex(Matrix *self, uint64_t index) {
    self->methods.GetAtIndex(self, index);
}

float Matrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    self->methods.GetCell(self, row, col);
}

float Matrix_SetIndex(Matrix *self, uint64_t index, float value) {
    self->methods.SetIndex(self, index, value);
}

float Matrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    self->methods.SetCell(self, row, col, value);
}

Matrix Matrix_GetRow(Matrix *self, uint64_t row) {
    not_implemented;
}

Matrix Matrix_GetCol(Matrix *self, uint64_t col) {
    not_implemented;
}

Matrix Matrix_SetRow(Matrix *self, uint64_t row, Matrix values) {
    not_implemented;
}

Matrix Matrix_SetCol(Matrix *self, uint64_t col, Matrix values) {
    not_implemented;
}

Matrix Matrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB) {
    not_implemented;
}

Matrix Matrix_SwapCols(Matrix *self, uint64_t, uint64_t) {
    not_implemented;
}

Matrix Matrix_MultiplyRow(Matrix *self, uint64_t row, float multiplier) {
    not_implemented;
}

Matrix Matrix_AddMultipleOfRow(Matrix *self, uint64_t rowA, uint64_t rowB, float multiplier) {
    not_implemented;
}


uint64_t Matrix_CellToIndex(Matrix* self, uint64_t row, uint64_t col) {
    return row * self->cols + col;
}

void Matrix_Print(Matrix* self) {
    for (int row = 0; row < self->rows; row++) {
        for (int col = 0; col < self->cols; col++) {
            printf("%.2f ", self->methods.GetCell(self, row, col));
        }
        printf("\n");
    }
    printf("\n");
}