#include "la_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include "la_common.h"

static float FullMatrix_GetAtIndex(Matrix *self, uint64_t index) {
    return self->cells[index];
}

static float FullMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    return FullMatrix_GetAtIndex(self, Matrix_CellToIndex(self, row, col));
}

static void FullMatrix_SetIndex(Matrix *self, uint64_t index, float value) {
    self->cells[index] = value;
}

static void FullMatrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    FullMatrix_SetIndex(self, Matrix_CellToIndex(self, row, col), value);
}

Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells) {
    return (Matrix) {
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

void Matrix_Destroy(Matrix* self) {
    if (self->cells == NULL) {
        return;
    }

    free(self->cells);
    self->cells = NULL;
}

float Matrix_GetAtIndex(Matrix *self, uint64_t index) {
    panic_if(index < 0 || index >= self->rows * self->cols, "Attempted to index outside the bounds of the matrix.");
    self->methods.GetAtIndex(self, index);
}

float Matrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    panic_if(self->cells == NULL,          "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || col >= self->cols, "Attempted to index column outside of matrix bounds");
    
    self->methods.GetCell(self, row, col);
}

void Matrix_SetIndex(Matrix *self, uint64_t index, float value) {
    panic_if(index < 0 || index >= self->rows * self->cols, "Attempted to index outside the bounds of the matrix.");
    self->methods.SetIndex(self, index, value);
}

void Matrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    panic_if(self->cells == NULL,          "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || col >= self->cols, "Attempted to index column outside of matrix bounds");
    
    self->methods.SetCell(self, row, col, value);
}

Matrix Matrix_GetRow(Matrix *self, uint64_t row) {
    float *cells = malloc(self->cols * sizeof(float));
    
    for (int i = 0; i < self->cols; i++) {
        cells[i] = Matrix_GetCell(self, i, row);
    }

    return Matrix_New(1, self->cols, cells);
}

Matrix Matrix_GetCol(Matrix *self, uint64_t col) {
    float *cells = malloc(self->rows * sizeof(float));
    
    for (int i = 0; i < self->rows; i++) {
        cells[i] = Matrix_GetCell(self, col, i);
    }

    return Matrix_New(self->rows, 1, cells);
}

void Matrix_SetRow(Matrix *self, uint64_t row, Matrix values) {
    not_implemented;
}

void Matrix_SetCol(Matrix *self, uint64_t col, Matrix values) {
    not_implemented;
}

void Matrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB) {
    not_implemented;
}

void Matrix_SwapCols(Matrix *self, uint64_t, uint64_t) {
    not_implemented;
}

void Matrix_MultiplyRow(Matrix *self, uint64_t row, float multiplier) {
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