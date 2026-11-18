#include "la_arithmetic.h"

#include "la_common.h"
#include <stdlib.h>

Matrix Matrix_Add(Matrix a, Matrix b) {
    assert(a.rows == b.rows && a.cols == b.cols);

    int size = a.rows * a.cols;
    float *elements = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        elements[i] = Matrix_GetIndex(&a, i) + Matrix_GetIndex(&b, i);
    }

    return Matrix_New(a.rows, a.cols, elements);
}

Matrix Matrix_Sub(Matrix a, Matrix b) {
    not_implemented;
    // return Matrix_Add(a, Matrix_MultiplyScalar(b, -1f));
}

static float _Matrix_GetProductCell(Matrix a, Matrix b, int row, int col) {
    int n = a.cols;
    float out = 0;

    for (int i = 0; i < n; i++) {
        out += Matrix_GetCell(&a, row, i) * Matrix_GetCell(&b, i, col);
    }

    return out;
}

Matrix Matrix_Multiply(Matrix a, Matrix b) {
    assert(a.cols == b.rows);

    int size = a.rows * b.cols;
    float *elements = malloc(size * sizeof(float));

    for (int row = 0; row < a.rows; row++) {
        for (int col = 0; col < b.cols; col++) {
            int index = row * b.cols + col;
            elements[index] = _Matrix_GetProductCell(a, b, row, col);
        }
    }

    return Matrix_New(a.rows, b.cols, elements);
}

Matrix Matrix_AddScalar(Matrix a, float scalar) {
    return Matrix_Add(a, (Matrix) {
        a.rows, a.cols,
        LA_MATKIND_SCALAR,
        &scalar
    });
}

Matrix Matrix_SubScalar(Matrix a, float scalar) {
    return Matrix_AddScalar(a, -1 * scalar);
}

Matrix Matrix_MultiplyScalar(Matrix a, float scalar) {
    not_implemented;
}

Matrix Matrix_Inverse(Matrix self) {
    not_implemented;
}

float Matrix_Det(Matrix self) {
    not_implemented;
}

Matrix Matrix_Tranpose(Matrix self) {
    not_implemented;
}
