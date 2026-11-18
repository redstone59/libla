#include "scalar_matrix.h"

static float ScalarMatrix_GetAtIndex(Matrix *self, uint64_t index) {
    return *self->cells.asVec;
}

static float ScalarMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    return *self->cells.asVec;
}

static void ScalarMatrix_SetIndex(Matrix *self, uint64_t index, float value) {
    return;
}

static void ScalarMatrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    return;
}

Matrix ScalarMatrix_New(uint64_t rows, uint64_t cols, float *value) {
    return (Matrix) {
        .rows = rows,
        .cols = cols,
        .count = 1,
        .kind = LA_MATKIND_SCALAR,
        .cells.asVec = value,

        .methods = {
            .GetAtIndex = ScalarMatrix_GetAtIndex,
            .GetCell = ScalarMatrix_GetCell,
            .SetIndex = ScalarMatrix_SetIndex,
            .SetCell = ScalarMatrix_SetCell
        }
    };
}