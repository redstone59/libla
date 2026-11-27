#include "substitutions.h"

#include "../../common.h"
#include <stdio.h>

// TODO: allow for `b` with more than one column
Matrix ForwardSubstitution(Matrix L, Matrix b) {
    Matrix x = Matrix_NewEmpty(b.rows, b.cols);

    for (size_t row = 0; row < L.rows; row++) {
        float cell = Matrix_GetCell(&b, row, 0);

        for (size_t i = 0; i < L.rows - 1; i++) {
            cell -= Matrix_GetCell(&L, row, i) * Matrix_GetCell(&x, i, 0);
        }

        cell /= Matrix_GetCell(&L, row, row);
        Matrix_SetCell(&x, row, 0, cell);
    }

    return x;
}

Matrix ForwardSubstitutionAugmented(Matrix Lb, size_t numVectors) {
    return ForwardSubstitution(
        Matrix_GetRange(&Lb, RANGE_EXCLUSIVE(0, Lb.rows), RANGE_EXCLUSIVE(0, Lb.cols - numVectors)),
        Matrix_GetRange(&Lb, RANGE_EXCLUSIVE(0, Lb.rows), RANGE_EXCLUSIVE(numVectors, Lb.cols))
    );
}

Matrix BackwardSubstitution(Matrix U, Matrix b) {
    Matrix x = Matrix_NewEmpty(b.rows, b.cols);

    for (size_t row = U.rows - 1;; row--) {
        float cell = Matrix_GetCell(&b, row, 0);

        for (size_t col = row + 1; col < U.rows; col++) {
            cell -= Matrix_GetCell(&U, row, col) * Matrix_GetCell(&x, col, 0);
        }

        cell /= Matrix_GetCell(&U, row, row);
        Matrix_SetCell(&x, row, 0, cell);

        if (row == 0) {
            break;
        }
    }

    return x;
}

Matrix BackwardSubstitutionAugmented(Matrix Ub, size_t numVectors) {
    Matrix U = Matrix_GetRange(&Ub, RANGE_EXCLUSIVE(0, Ub.rows), RANGE_EXCLUSIVE(0, Ub.cols - numVectors));
    Matrix b = Matrix_GetRange(&Ub, RANGE_EXCLUSIVE(0, Ub.rows), RANGE_EXCLUSIVE(Ub.cols - numVectors, Ub.cols));
    Matrix_Print(&U, "%.2f");
    Matrix_Print(&b, "%.2f");
    return BackwardSubstitution(
        U, b
    );
}