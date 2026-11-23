#include "substitutions.h"

#include "../../common.h"
#include <stdio.h>

// TODO: allow for `b` with more than one column
Matrix ForwardSubstitution(Matrix *L, Matrix *b) {
    Matrix x = Matrix_NewEmpty(b->rows, b->cols);

    for (size_t row = 0; row < L->rows; row++) {
        float cell = Matrix_GetCell(b, row, 0);

        for (size_t i = 0; i < L->rows - 1; i++) {
            cell -= Matrix_GetCell(L, row, i) * Matrix_GetCell(&x, i, 0);
        }

        cell /= Matrix_GetCell(L, row, row);
        Matrix_SetCell(&x, row, 0, cell);
    }

    return x;
}

Matrix ForwardSubstitutionAugmented(Matrix *Lb, size_t numVectors) {
    not_implemented;
}

Matrix BackwardSubstitution(Matrix *U, Matrix *b) {
    Matrix x = Matrix_NewEmpty(b->rows, b->cols);

    for (size_t row = U->rows - 1;; row--) {
        float cell = Matrix_GetCell(b, row, 0);

        for (size_t col = row + 1; col < U->rows; col++) {
            cell -= Matrix_GetCell(U, row, col) * Matrix_GetCell(&x, col, 0);
        }

        cell /= Matrix_GetCell(U, row, row);
        Matrix_SetCell(&x, row, 0, cell);

        if (row == 0) {
            break;
        }
    }

    return x;
}

Matrix BackwardSubstitutionAugmented(Matrix *Ub, size_t numVectors) {
    not_implemented;
}