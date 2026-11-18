#ifndef LA_FULLMATRIX_H_
#define LA_FULLMATRIX_H_

#include "../la_matrix.h"

Matrix FullMatrix_New(uint64_t rows, uint64_t cols, float* cells);

/*
float FullMatrix_GetAtIndex(Matrix *self, uint64_t index);
float FullMatrix_GetCell(Matrix *self, uint64_t row, uint64_t col);
float FullMatrix_SetIndex(Matrix *self, uint64_t index, float value);
float FullMatrix_SetCell(Matrix *self, uint64_t row, uint64_t col, float value);

Matrix FullMatrix_GetRow(Matrix *self, uint64_t row);
Matrix FullMatrix_GetCol(Matrix *self, uint64_t col);
Matrix FullMatrix_SetRow(Matrix *self, uint64_t row, Matrix values);
Matrix FullMatrix_SetCol(Matrix *self, uint64_t col, Matrix values);

Matrix FullMatrix_SwapRows(Matrix *self, uint64_t rowA, uint64_t rowB);
Matrix FullMatrix_SwapCols(Matrix *self, uint64_t colA, uint64_t colB);
Matrix FullMatrix_MultiplyRow(Matrix *self, uint64_t row, float multiplier);
/** `rowA` = `rowA` + `multiplier` * `rowB` *
Matrix FullMatrix_AddMultipleOfRow(Matrix *self, uint64_t rowA, uint64_t rowB, float multiplier);
*/
#endif // LA_FULLMATRIX_H_