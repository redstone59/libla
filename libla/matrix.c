#include "matrix.h"

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "gc/gc.h"

#include "matrix_storage/full_matrix.h"

Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells) {
    Matrix new = FullMatrix_New(rows, cols, cells);
    Matrix_Mark(&new);
    return new;
}

Matrix Matrix_NewEmpty(uint64_t rows, uint64_t cols) {
    size_t toAllocate = rows * cols * sizeof(float);
    float *cells = GC_Alloc(toAllocate);
    memset(cells, 0, toAllocate);
    return Matrix_New(rows, cols, cells);
}

void Matrix_DestroyFloatVec(Matrix *self) {
    GC_Free(&self->cells.asFloatVec);
    self->cells.asFloatVec = NULL;
}

void Matrix_DestroyArray(Matrix *self) {
    DynamicArray_Free(&self->cells.asVec);
}

void Matrix_Destroy(Matrix *self) {
    panic_if(self->methods->Destroy == NULL, "`Matrix_Destroy()` not defined in matrix vtable!");
    self->methods->Destroy(self);
}

void Matrix_MarkFloatVec(Matrix *self) {
    GC_Mark(self->cells.asFloatVec);
}

void Matrix_MarkArray(Matrix *self) {
    GC_Mark(&self->cells.asVec.elements);    
}

void Matrix_Mark(Matrix *self) {
    panic_if(self->methods->Mark == NULL, "`Matrix_Mark()` not defined in matrix vtable!");
    self->methods->Mark(self);
}

float Matrix_GetAtIndex(Matrix *self, uint64_t index) {
    panic_if(index < 0 || index >= self->rows * self->cols, "Attempted to index outside the bounds of the matrix.");
    panic_if(self->methods->GetAtIndex == NULL, "`Matrix_GetAtIndex()` not defined in matrix vtable!");

    return self->methods->GetAtIndex(self, index);
}

float Matrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    panic_if(self->cells.asArrays == NULL, "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || col >= self->cols, "Attempted to index column outside of matrix bounds");
    panic_if(self->methods->GetCell == NULL, "`Matrix_GetCell()` not defined in matrix vtable!");
    
    return self->methods->GetCell(self, row, col);
}

void Matrix_SetIndex(Matrix *self, uint64_t index, float value) {
    panic_if(index < 0 || index >= self->rows * self->cols, "Attempted to index outside the bounds of the matrix.");
    panic_if(self->methods->SetIndex == NULL, "`Matrix_SetIndex()` not defined in matrix vtable!");

    self->methods->SetIndex(self, index, value);
}

void Matrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    panic_if(self->cells.asArrays == NULL, "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || col >= self->cols, "Attempted to index column outside of matrix bounds");
    panic_if(self->methods->SetCell == NULL, "`Matrix_SetCell()` not defined in matrix vtable!");
    
    self->methods->SetCell(self, row, col, value);
}

Matrix Matrix_GetRow(Matrix *self, uint64_t row) {
    return Matrix_GetRange(self, RANGE_SINGULAR(row), RANGE_EXCLUSIVE(0, self->cols));
}

Matrix Matrix_GetCol(Matrix *self, uint64_t col) {
    return Matrix_GetRange(self, RANGE_EXCLUSIVE(0, self->rows), RANGE_SINGULAR(col));
}

void Matrix_SetRow(Matrix *self, uint64_t row, Matrix values) {
    not_implemented;
}

void Matrix_SetCol(Matrix *self, uint64_t col, Matrix values) {
    not_implemented;
}

Matrix Matrix_GetRange(Matrix *self, Range rowRange, Range colRange) {
    size_t rows = RANGE_LEN(rowRange);
    size_t cols = RANGE_LEN(colRange);
    float *elements = GC_Alloc(rows * cols * sizeof(float));

    size_t index = 0;
    for (EACH_IN_RANGE(size_t, row, rowRange)) {
        for (EACH_IN_RANGE(size_t, col, colRange)) {
            elements[index++] = Matrix_GetCell(self, row, col);
        }
    }

    return Matrix_New(rows, cols, elements);
}

void Matrix_SetRange(Matrix *self, Range rowRange, Range colRange, Matrix values) {
    panic_if(values.rows != RANGE_LEN(rowRange), "Attempted to set matrix range with mismatching row count.");
    panic_if(values.cols != RANGE_LEN(colRange), "Attempted to set matrix range with mismatching column count.");
    
    for (EACH_IN_RANGE(size_t, row, rowRange)) {
        for (EACH_IN_RANGE(size_t, col, colRange)) {
            Matrix_SetCell(
                self,
                row, col,
                Matrix_GetCell(&values, row - rowRange.start, col - colRange.start)
            );
        }
    }
}


void Matrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB) {
    panic_if(rowA < 0 || rowA >= self->rows, "Attempted to index row outside of matrix bounds.");
    panic_if(rowB < 0 || rowB >= self->rows, "Attempted to index row outside of matrix bounds.");
    panic_if(self->methods->SwapRows == NULL, "`Matrix_SwapRows()` not defined in matrix vtable!");

    if (rowA == rowB) {
        return;
    }

    self->methods->SwapRows(self, rowA, rowB);
}

void Matrix_MultiplyRow(Matrix *self, uint64_t row, float multiplier) {
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds.");
    
    for (size_t i = 0; i < self->cols; i++) {
        Matrix_SetCell(
            self,
            row, i, 
            Matrix_GetCell(self, row, i) * multiplier
        );
    }
}

void Matrix_AddMultipleOfRow(Matrix *self, float multiplier, uint64_t rowA, uint64_t rowB) {
    panic_if(rowA < 0 || rowA >= self->rows, "Attempted to index row outside of matrix bounds.");
    panic_if(rowB < 0 || rowB >= self->rows, "Attempted to index row outside of matrix bounds.");

    if (multiplier == 0) {
        return;
    }

    for (size_t i = 0; i < self->cols; i++) {
        Matrix_SetCell(
            self,
            rowB, i, 
            Matrix_GetCell(self, rowB, i) + Matrix_GetCell(self, rowA, i) * multiplier
        );
    }
}

Matrix Matrix_Augment(Matrix *left, Matrix *right) {
    panic_if(left->rows != right->rows, "Attempted to augment two matrices with different row counts");

    size_t rows = left->rows;
    size_t cols = left->cols + right->cols;
    float *elements = GC_Alloc(rows * cols * sizeof(float));

    size_t index = 0;
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            float cell;
            if (col < left->rows) {
                cell = Matrix_GetCell(left, row, col);
            } else {
                cell = Matrix_GetCell(right, row, col - left->cols);
            }
            
            elements[index] = cell;
            index++;
        }
    }

    return Matrix_New(rows, cols, elements);
}

uint64_t Matrix_CellToIndex(Matrix *self, uint64_t row, uint64_t col) {
    return row * self->cols + col;
}

#define LA_MATRIX_PRINT_MAX_LEN 256
#define LA_FANCY_PRINT_TOPLEFT "┌"
#define LA_FANCY_PRINT_TOPRIGHT "┐"
#define LA_FANCY_PRINT_BOTTOMLEFT "└"
#define LA_FANCY_PRINT_BOTTOMRIGHT "┘"
#define LA_FANCY_PRINT_PIPE "│"

void Matrix_Print(Matrix *self, const char *specifier) {
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

#ifndef LA_NO_FANCY_PRINT
    printf(LA_FANCY_PRINT_TOPLEFT " ");
    for (int col = 0; col < self->cols; col++) {
        printf("%*s ", longestInColumn[col], "");
    }
    printf(LA_FANCY_PRINT_TOPRIGHT "\n");
#endif // LA_NO_FANCY_PRINT
    
    // Print matrix elements
    for (int row = 0; row < self->rows; row++) {
        char cellStr[LA_MATRIX_PRINT_MAX_LEN];
#ifndef LA_NO_FANCY_PRINT
        printf(LA_FANCY_PRINT_PIPE " ");
#endif
        for (int col = 0; col < self->cols; col++) {
            snprintf(
                cellStr, 
                LA_MATRIX_PRINT_MAX_LEN, 
                specifier, 
                Matrix_GetCell(self, row, col)
            );
            printf("%*s ", longestInColumn[col], cellStr);
        }
#ifndef LA_NO_FANCY_PRINT
        printf(LA_FANCY_PRINT_PIPE "\n");
#else
        printf("\n");   
#endif // LA_NO_FANCY_PRINT
    }

#ifndef LA_NO_FANCY_PRINT
    printf(LA_FANCY_PRINT_BOTTOMLEFT " ");
    for (int col = 0; col < self->cols; col++) {
        printf("%*s ", longestInColumn[col], "");
    }
    printf(LA_FANCY_PRINT_BOTTOMRIGHT "\n");
#endif // LA_NO_FANCY_PRINT

    printf("\n");
}