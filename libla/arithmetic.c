#include "arithmetic.h"

#include "common.h"
#include "matrix_storage/scalar_matrix.h"

Matrix Matrix_Add(Matrix a, Matrix b) {
    assert(a.rows == b.rows && a.cols == b.cols);

    int size = a.rows * a.cols;
    float *elements = LA_ALLOC(size * sizeof(float));
    for (int i = 0; i < size; i++) {
        elements[i] = Matrix_GetAtIndex(&a, i) + Matrix_GetAtIndex(&b, i);
    }

    return Matrix_New(a.rows, a.cols, elements);
}

Matrix Matrix_Sub(Matrix a, Matrix b) {
    return Matrix_Add(a, Matrix_MultiplyScalar(b, -1));
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

    size_t numElements = a.rows * b.cols;
    float *elements = LA_ALLOC(numElements * sizeof(float));

    // "schoolyard" method of multiplying matrices (O(n^3))
    for (int row = 0; row < a.rows; row++) {
        for (int col = 0; col < b.cols; col++) {
            int index = row * b.cols + col;
            elements[index] = _Matrix_GetProductCell(a, b, row, col);
        }
    }

    return Matrix_New(a.rows, b.cols, elements);
}

Matrix Matrix_AddScalar(Matrix a, float scalar) {
    return Matrix_Add(a, ScalarMatrix_New(a.rows, a.cols, &scalar));
}

Matrix Matrix_SubScalar(Matrix a, float scalar) {
    return Matrix_AddScalar(a, -1 * scalar);
}

Matrix Matrix_MultiplyScalar(Matrix a, float scalar) {
    size_t numElements = a.rows * a.cols;
    float* elements = LA_ALLOC(numElements * sizeof(float));
    
    // Only loop non-zero elements (if sparse storage)
    for (int i = 0; i < numElements; i++) {
        elements[i] = Matrix_GetAtIndex(&a, i) * scalar;
    }

    // Return same type of matrix back instead of full storage matrix.
    return Matrix_New(a.rows, a.cols, elements);
}

Matrix Matrix_Inverse(Matrix self) {
    // NOTE: augment with identity matrix,
    //       produce reduced row-echelon form
    not_implemented;
}

float Matrix_Det(Matrix self) {
    // NOTE: for large matrices use LU decomposition
    //      A = LU
    // det(A) = det(LU)
    // det(A) = det(L)det(U)
    //
    // Since L and U are triangular, determinant is product of diagonal entries.
    not_implemented;
}

Matrix Matrix_Transpose(Matrix a) {
    size_t numElements = a.rows * a.cols;
    float* elements = LA_ALLOC(numElements * sizeof(float));
    Matrix transposed = Matrix_New(a.cols, a.rows, elements);

    for (uint64_t row = 0; row < a.rows; row++) {
        for (uint64_t col = 0; col < a.cols; col++) {
            Matrix_SetCell(
                &transposed, 
                col, row, 
                Matrix_GetCell(&a, row, col)
            );
        }
    }

    return transposed;
}
