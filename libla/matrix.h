#ifndef LA_MATRIX_H_
#define LA_MATRIX_H_

#include <stddef.h>
#include <stdint.h>

#include "array/dynamic_array.h"
#include "range.h"

typedef struct Matrix Matrix;

typedef enum MatrixKind {
    LA_MATKIND_FULL,
    LA_MATKIND_SCALAR,

    LA_MATKIND_SPARSE,
    // LA_MATKIND_CSR,
    // LA_MATKIND_TRIANGULAR,
    // LA_MATKIND_BANDED,
    LA_MATKIND_COUNT
} MatrixKind;

typedef struct MatrixVTable {
    void (*Destroy)(Matrix *self);
    void (*Mark)(Matrix *self);

    float (*GetAtIndex)(Matrix *self, uint64_t index);
    float (*GetCell)(Matrix *self, uint64_t row, uint64_t col);
    void (*SetIndex)(Matrix *self, uint64_t index, float value);
    void (*SetCell)(Matrix *self, uint64_t row, uint64_t col, float value);

    void (*SwapRows)(Matrix *self, uint64_t rowA, uint64_t rowB);
    // void (*MultiplyRow)(Matrix *self, uint64_t row, float multiplier);
    // void (*AddMultipleOfRow)(Matrix *self, float multiplier, uint64_t rowA, uint64_t rowB);
} MatrixVTable;

struct Matrix {
    uint64_t rows;
    uint64_t cols;

    size_t count;

    MatrixKind kind;

    union {
        float *asFloatVec;
        DynamicArray asVec;
        DynamicArray *asArrays;
    } cells;

    MatrixVTable *methods;
};

/**
 * Creates a new matrix with given cells.
 * 
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @param cells A pointer to the cells in a `rows * cols` long array.
 * 
 * @returns The `Matrix` according to provided parameters.
 */
Matrix Matrix_New(uint64_t rows, uint64_t cols, float* cells);

/**
 * Creates a new matrix with all cells set to zero.
 * 
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * 
 * @returns The `Matrix` with the provided size. This matrix is allocated on the heap.
 */
Matrix Matrix_NewEmpty(uint64_t rows, uint64_t cols);

void Matrix_DestroyFloatVec(Matrix *self);
void Matrix_DestroyArray(Matrix *self);

/**
 * Frees a matrix.
 * 
 * @param self A pointer to the matrix to free.
 */
void Matrix_Destroy(Matrix *self); // TODO: properly implement

void Matrix_MarkFloatVec(Matrix *self);
void Matrix_MarkArray(Matrix *self);

/**
 * Marks a matrix so that it doesn't get cleaned by the garbage collector.
 * 
 * @param self A pointer to the matrix to preserve.
 */
void Matrix_Mark(Matrix *self);

float Matrix_GetAtIndex(Matrix *self, uint64_t index);
float Matrix_GetCell(Matrix *self, uint64_t row, uint64_t col);
void Matrix_SetIndex(Matrix *self, uint64_t index, float value);
void Matrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value);

Matrix Matrix_GetRow(Matrix *self, uint64_t row);
Matrix Matrix_GetCol(Matrix *self, uint64_t col);
void Matrix_SetRow(Matrix *self, uint64_t row, Matrix values);
void Matrix_SetCol(Matrix *self, uint64_t col, Matrix values);

Matrix Matrix_GetRange(Matrix *self, Range rowRange, Range colRange);
void Matrix_SetRange(Matrix *self, Range rowRange, Range colRange, Matrix values);

/**
 * Swaps two rows in a matrix in place.
 * 
 * @param self The matrix to operate on.
 * @param rowA The first row to swap.
 * @param rowB The second row to swap.
 */
void Matrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB);

// void Matrix_SwapCols(Matrix *self, uint64_t colA, uint64_t colB);
/**
 * Multiplies all cells in a row by a scalar in place.
 * 
 * @param self The matrix to operate on.
 * @param row The row to multiply
 * @param multiplier The scalar to multiply the row by.
 */
void Matrix_MultiplyRow(Matrix *self, uint64_t row, float multiplier);

/**
 * Adds a multiple of a row in place such that `rowB` = `rowB` + `multiplier` * `rowA` .
 * 
 * i.e. `Matrix(&A, 3, 0, 2)` would be "add 3 times the zeroth row of `A` to the second row of `A`".
 * 
 * @param self The matrix to operate on.
 * @param multiplier The scalar to multiply `rowA` by.
 * @param rowA The row to add to `rowB`.
 * @param rowB The row that will be summed with `rowA * multiplier`.
 */
void Matrix_AddMultipleOfRow(Matrix *self, float multiplier, uint64_t rowA, uint64_t rowB);

/**
 * Augments two matrices into one.
 * 
 * @param left The matrix to augment on the left.
 * @param right The matrix to augment on the right.
 * 
 * @returns The two matrices augmented.
 */
Matrix Matrix_Augment(Matrix *left, Matrix *right);

// TODO: make this not assume full storage matrix only
uint64_t Matrix_CellToIndex(Matrix *self, uint64_t row, uint64_t col);

/**
 * Prints a matrix.
 * 
 * @param self The matrix to print
 * @param specifier The `printf` specifier to use for each cell.
 */
void Matrix_Print(Matrix *self, const char *specifier);

#endif // LA_MATRIX_H_