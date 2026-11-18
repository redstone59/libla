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