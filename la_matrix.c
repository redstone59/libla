#include "la_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include "la_common.h"

Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells) {
    return (Matrix) {
        .rows = rows,
        .cols = cols,
        .kind = LA_MATKIND_NONSPARSE,
        .cells = cells
    };
}

void Matrix_Destroy(Matrix* self) {
    if (self->cells == NULL) {
        return;
    }

    free(self->cells);
    self->cells = NULL;
}

float Matrix_GetIndex(Matrix* self, uint64_t index) {
    switch (self->kind) {
        case LA_MATKIND_NONSPARSE:
            return self->cells[index];
        case LA_MATKIND_SCALAR:
            return *self->cells;
        default:
            assert(0 && "Attempted to get value of invalid matrix type");
    }
}

float Matrix_GetCell(Matrix* self, uint64_t row, uint64_t col) {
    panic_if(self->cells == NULL,          "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || col >= self->cols, "Attempted to index column outside of matrix bounds");

    int index = row * self->cols + col;
    return Matrix_GetIndex(self, index);
}

// TODO: setters, getting rows/columns

int Matrix_GetNonzeroIndicies(Matrix* self) {

}

void Matrix_Print(Matrix* self) {
    for (int row = 0; row < self->rows; row++) {
        for (int col = 0; col < self->cols; col++) {
            printf("%.2f ", Matrix_GetCell(self, row, col));
        }
        printf("\n");
    }
    printf("\n");
}