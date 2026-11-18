#include "sparse_matrix.h"

#include "../common.h"

static float SparseMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    float *rowVec = self->cells.asArrays[0];
    float *colVec = self->cells.asArrays[1];
    float *valVec = self->cells.asArrays[2];

    for (int i = 0; i < self->count; i++) {
        if (rowVec[i] == row && colVec[i] == col) {
            return valVec[i];
        }
    }

    return 0;
}
static float SparseMatrix_GetAtIndex(Matrix *self, uint64_t index) {
    uint64_t row = index / self->cols;
    uint64_t col = index % self->cols;
    
    return SparseMatrix_GetCell(self, row, col);
}

static void SparseMatrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value) {
    not_implemented;
}

static void SparseMatrix_SetIndex(Matrix *self, uint64_t index, float value) {
    uint64_t row = index / self->cols;
    uint64_t col = index % self->cols;
    
    SparseMatrix_SetCell(self, row, col, value);
}

/*
0 1 0
3 0 4
0 0 0


row = [ 0 1 1 
col =   1 0 2 
val =   1 3 4 ]
*/

Matrix SparseMatrix_New(uint64_t rows, uint64_t cols, float **vecs, size_t nz) {
    return (Matrix){
        .rows = rows,
        .cols = cols,
        .count = nz,
        .kind = LA_MATKIND_SPARSE,
        .cells.asArrays = vecs,

        .methods = {
            .GetAtIndex = SparseMatrix_GetAtIndex,
            .GetCell = SparseMatrix_GetCell,
            .SetIndex = SparseMatrix_SetIndex,
            .SetCell = SparseMatrix_SetCell
        }
    };
}