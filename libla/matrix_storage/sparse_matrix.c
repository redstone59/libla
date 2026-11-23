#include "sparse_matrix.h"

#include <stdio.h>
#include "../common.h"

#define LA_SPARSE_ROW_VEC_INDEX 0
#define LA_SPARSE_COL_VEC_INDEX 1
#define LA_SPARSE_VAL_VEC_INDEX 2

static void SparseMatrix__GetVecs(Matrix *self, DynamicArray **rowVec, DynamicArray **colVec, DynamicArray **valVec) {
    *rowVec = &self->cells.asArrays[LA_SPARSE_ROW_VEC_INDEX];
    *colVec = &self->cells.asArrays[LA_SPARSE_COL_VEC_INDEX];
    *valVec = &self->cells.asArrays[LA_SPARSE_VAL_VEC_INDEX];
}

static float SparseMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col) {
    DynamicArray *rowVec, *colVec, *valVec;
    SparseMatrix__GetVecs(self, &rowVec, &colVec, &valVec);

    // TODO: change to binary search/other search alg
    //       for speed
    for (int i = 0; i < self->count; i++) {
        if (DynamicArray_Get(rowVec, i) == row && DynamicArray_Get(colVec, i) == col) {
            return DynamicArray_Get(valVec, i);
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
    DynamicArray *rowVec, *colVec, *valVec;
    SparseMatrix__GetVecs(self, &rowVec, &colVec, &valVec);

    // TODO: change to binary search/other search alg
    //       for speed
    for (int i = 0; i < self->count; i++) {
        float currentRow = DynamicArray_Get(rowVec, i);
        float currentCol = DynamicArray_Get(colVec, i);
        // If we're overwriting a non-zero cell, then overwrite it.
        if (currentRow == row && currentCol == col) {
            if (value == 0) {
                DynamicArray_RemoveAt(rowVec, i);
                DynamicArray_RemoveAt(colVec, i);
                DynamicArray_RemoveAt(valVec, i);
                self->count--;
            } else {
                DynamicArray_Set(valVec, i, value);
            }
            return;
        }
        
        // Otherwise, insert new element before element that comes after it.
        if (currentRow > row || (currentRow == row && currentCol > col)) {
            if (value != 0) {
                DynamicArray_Insert(rowVec, i, row);
                DynamicArray_Insert(colVec, i, col);
                DynamicArray_Insert(valVec, i, value);
                self->count++;
            }
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

static void SparseMatrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB) {
    DynamicArray *rowVec, *colVec, *valVec;
    SparseMatrix__GetVecs(self, &rowVec, &colVec, &valVec);

    for (size_t i = 0; i < rowVec->count; i++) {
        float row = DynamicArray_Get(rowVec, i);
        if (row == rowA) {
            DynamicArray_Set(rowVec, i, rowB);
            continue;
        }

        if (row == rowB) {
            DynamicArray_Set(rowVec, i, rowA);
            continue;
        }
    }

    // TODO: sort row, col, val vec to be in row, column order
}

static MatrixVTable sparseMethods = {
    .GetAtIndex = SparseMatrix_GetAtIndex,
    .GetCell = SparseMatrix_GetCell,
    .SetIndex = SparseMatrix_SetIndex,
    .SetCell = SparseMatrix_SetCell,

    .SwapRows = SparseMatrix_SwapRows
};

Matrix SparseMatrix_New(uint64_t rows, uint64_t cols, float **vecs, size_t nz, size_t capacity)
{
    // NOTE: maybe pull out this initialisation code into own function SparseMatrix__InitVecs()?
    DynamicArray rowArr = DynamicArray_New(capacity);
    DynamicArray colArr = DynamicArray_New(capacity);
    DynamicArray valArr = DynamicArray_New(capacity);

    float *rowVec = vecs[LA_SPARSE_ROW_VEC_INDEX];
    float *colVec = vecs[LA_SPARSE_COL_VEC_INDEX];
    float *valVec = vecs[LA_SPARSE_VAL_VEC_INDEX];

    for (size_t i = 0; i < nz; i++) {
        DynamicArray_Append(&rowArr, rowVec[i]);
        DynamicArray_Append(&colArr, colVec[i]);
        DynamicArray_Append(&valArr, valVec[i]);
    }

    DynamicArray *arrays = LA_ALLOC(3 * sizeof(DynamicArray));
    arrays[LA_SPARSE_ROW_VEC_INDEX] = rowArr;
    arrays[LA_SPARSE_COL_VEC_INDEX] = colArr;
    arrays[LA_SPARSE_VAL_VEC_INDEX] = valArr;

    return (Matrix){
        .rows = rows,
        .cols = cols,
        
        .count = nz,

        .kind = LA_MATKIND_SPARSE,
        .cells.asArrays = arrays,

        .methods = &sparseMethods
    };
}