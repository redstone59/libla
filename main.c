#include <stdio.h>

#include "libla/matrix.h"
#include "libla/arithmetic.h"
#include "libla/matrix_types.h"

#include "libla/array/dynamic_array.h"

int main(int argc, char** argv) {
    DynamicArray arr = DynamicArray_New(1);

    DynamicArray_Append(&arr, 0);
    DynamicArray_Append(&arr, 1);
    for (int i = 1; i < 512; i++) {
        float next = DynamicArray_Get(&arr, i) + DynamicArray_Get(&arr, i - 1);
        DynamicArray_Append(&arr, next);
        DynamicArray_Print(&arr, "%.0f");
    }

    DynamicArray_Free(&arr);

    return 0;
    Matrix a = Matrix_New(2, 3, (float[6]) {
        2, 3, 4, 
        1, 0, 0
    });
    Matrix_Print(&a);
    float row[8] = {  0,  0,  1,  1,  2,  2,  2,  3 };
    float col[8] = {  0,  1,  1,  3,  2,  3,  4,  5 };
    float val[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
    float *sparse[3] = { row, col, val };

    Matrix b = SparseMatrix_New(4, 6, sparse, 8, 16);
    Matrix_Print(&b);

    Matrix c = Matrix_Multiply(Matrix_Transpose(a), a);
    Matrix_Print(&c);
    
    return 0;
}