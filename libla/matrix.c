#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#include "matrix_storage/full_matrix.h"

Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells) {
    return FullMatrix_New(rows, cols, cells);
}

void Matrix_Destroy(Matrix* self) {
    free(&self->cells.asArrays);
    self->cells.asArrays = NULL;
}

float Matrix_GetAtIndex(Matrix *self, uint64_t index) {
    panic_if(index < 0 || index >= self->rows * self->cols, "Attempted to index outside the bounds of the matrix.");
    return self->methods.GetAtIndex(self, index);
}

float Matrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    panic_if(self->cells.asArrays == NULL, "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || col >= self->cols, "Attempted to index column outside of matrix bounds");
    
    return self->methods.GetCell(self, row, col);
}

void Matrix_SetIndex(Matrix *self, uint64_t index, float value) {
    panic_if(index < 0 || index >= self->rows * self->cols, "Attempted to index outside the bounds of the matrix.");
    self->methods.SetIndex(self, index, value);
}

void Matrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    panic_if(self->cells.asArrays == NULL, "Matrix has not been initialised!");
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

void Matrix_AddMultipleOfRow(Matrix *self, uint64_t rowA, uint64_t rowB, float multiplier) {
    not_implemented;
}

uint64_t Matrix_CellToIndex(Matrix* self, uint64_t row, uint64_t col) {
    return row * self->cols + col;
}

#define LA_MATRIX_PRINT_MAX_LEN 256

void Matrix_Print(Matrix* self, const char* specifier) {
    // Determine longest string inside one cell.
    int longestInColumn[self->cols];
    memset(longestInColumn, 0, sizeof(longestInColumn));
    for (int row = 0; row < self->rows; row++) {
        for (int col = 0; col < self->cols; col++) {
            char cellStr[LA_MATRIX_PRINT_MAX_LEN];
            int length = snprintf(
                cellStr, 
                LA_MATRIX_PRINT_MAX_LEN, 
                specifier, 
                Matrix_GetCell(self, row, col)
            );
            if (length > longestInColumn[col]) {
                longestInColumn[col] = length;
            }
        }
    }

    // Print matrix elements and surrounding box characters.
    for (int row = 0; row < self->rows; row++) {
        char cellStr[LA_MATRIX_PRINT_MAX_LEN];
#ifndef LA_NO_FANCY_PRINT
        if (row == 0) {
            printf("┌ ");
        } else if (row == self->rows - 1) {
            printf("└ ");
        } else {
            printf("│ ");
        }
#endif // LA_NO_FANCY_PRINT

        for (int col = 0; col < self->cols; col++) {
            int length = snprintf(
                cellStr, 
                LA_MATRIX_PRINT_MAX_LEN, 
                specifier, 
                self->methods.GetCell(self, row, col)
            );
            // how delightfully disgusting
            printf("%-*s%s ", (int)(longestInColumn[col] - length), "", cellStr);
        }
        
#ifndef LA_NO_FANCY_PRINT
        if (row == 0) {
            printf("┐\n");
        } else if (row == self->rows - 1) {
            printf("┘\n");
        } else {
            printf("│\n");
        }
#else
        printf("\n");
#endif // LA_NO_FANCY_PRINT
    }


    printf("\n");
}