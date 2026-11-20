#include "sparse_matrix.h"

#include <stdio.h>
#include <stdlib.h>

static float SparseMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    DynamicArray rowVec = self->cells.asArrays[0];
    DynamicArray colVec = self->cells.asArrays[1];
    DynamicArray valVec = self->cells.asArrays[2];

    // TODO: change to binary search/other search alg
    //       for speed
    for (int i = 0; i < self->count; i++) {
        if (DynamicArray_Get(&rowVec, i) == row && DynamicArray_Get(&colVec, i) == col) {
            return DynamicArray_Get(&valVec, i);
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
    DynamicArray rowVec = self->cells.asArrays[0];
    DynamicArray colVec = self->cells.asArrays[1];
    DynamicArray valVec = self->cells.asArrays[2];

    // TODO: change to binary search/other search alg
    //       for speed
    for (int i = 0; i < self->count; i++) {
        if (DynamicArray_Get(&rowVec, i) == row && DynamicArray_Get(&colVec, i) == col) {
            DynamicArray_Set(&valVec, i, value);
            return;
        }
    }

    return;
}

static void SparseMatrix_SetIndex(Matrix *self, uint64_t index, float value) {
    uint64_t row = index / self->cols;
    uint64_t col = index % self->cols;
    
    SparseMatrix_SetCell(self, row, col, value);
}

static MatrixVTable sparseMethods = {
    .GetAtIndex = SparseMatrix_GetAtIndex,
    .GetCell = SparseMatrix_GetCell,
    .SetIndex = SparseMatrix_SetIndex,
    .SetCell = SparseMatrix_SetCell
};

Matrix SparseMatrix_New(uint64_t rows, uint64_t cols, float **vecs, size_t nz, size_t capacity)
{
    DynamicArray rowArr = DynamicArray_New(capacity);
    DynamicArray colArr = DynamicArray_New(capacity);
    DynamicArray valArr = DynamicArray_New(capacity);

    float *rowVec = vecs[0];
    float *colVec = vecs[1];
    float *valVec = vecs[2];

    for (size_t i = 0; i < nz; i++) {
        DynamicArray_Append(&rowArr, rowVec[i]);
        DynamicArray_Append(&colArr, colVec[i]);
        DynamicArray_Append(&valArr, valVec[i]);
    }

    DynamicArray *arrays = malloc(3 * sizeof(DynamicArray));
    arrays[0] = rowArr;
    arrays[1] = colArr;
    arrays[2] = valArr;

    return (Matrix){
        .rows = rows,
        .cols = cols,
        
        .count = nz,

        .kind = LA_MATKIND_SPARSE,
        .cells.asArrays = arrays,

        .methods = sparseMethods
    };
}