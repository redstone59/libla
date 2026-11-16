#include "la_matrix.h"

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
    return self->cells[index];
}

float Matrix_GetCell(Matrix* self, uint64_t row, uint64_t col) {
    panic_if(self->cells == NULL,          "Matrix has not been initialised!");
    panic_if(row < 0 || row >= self->rows, "Attempted to index row outside of matrix bounds");
    panic_if(col < 0 || row >= self->cols, "Attempted to index column outside of matrix bounds");

    int index = row * self->rows + col;
    return Matrix_GetIndex(self, index);
}

// TODO: setters, getting rows/columns