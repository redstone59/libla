#include "gaussian_elimination.h"
#include "../common.h"

void GaussianElimination(Matrix *a) {
    // Derived from https://en.wikipedia.org/wiki/Gaussian_elimination#Pseudocode
    // despite how despicably ugly the code is.
    size_t pivotRow = 0;
    size_t pivotCol = 0;

    while (pivotRow < a->rows - 1 && pivotCol < a->cols) {
        size_t largestPivotRow = 0;
        float largestPivot = 0;

        for (size_t i = pivotRow; i < a->rows; i++) {
            float value = Matrix_GetCell(a, i, pivotCol);
            value = LA_ABS(value);

            if (value > largestPivot) {
                largestPivot = value;
                largestPivotRow = i;
            }
        }

        if (largestPivot == 0) {
            pivotCol++;
            continue;
        }

        Matrix_SwapRows(a, pivotRow, largestPivotRow);
        for (size_t i = pivotRow + 1; i < a->rows; i++) {
            float multiplier = -Matrix_GetCell(a, i, pivotCol) / Matrix_GetCell(a, pivotRow, pivotCol);
            Matrix_AddMultipleOfRow(a, multiplier, pivotRow, i);
        }

        pivotRow++;
        pivotCol++;
    }
}