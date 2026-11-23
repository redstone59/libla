#include <stdio.h>

#include "libla/matrix.h"
#include "libla/arithmetic.h"
#include "libla/matrix_types.h"

int main(int argc, char** argv) {
    Matrix a = Matrix_New(4, 4, (float[16]) {
        2, 3, 4, 5, 
        1, 0, 0, 0,
        3, 1, 4, 1,
        2, 7, 1, 8
    });
    Matrix_Print(&a, "%.0f");

    Matrix_SwapRows(&a, 1, 3);
    Matrix_Print(&a, "%.0f");

    float row[8] = {  0,  0,  1,  1,  2,  2,  2,  3 };
    float col[8] = {  0,  1,  1,  3,  2,  3,  4,  5 };
    float val[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
    float *sparse[3] = { row, col, val };
    
    Matrix b = SparseMatrix_New(4, 6, sparse, 8, 16);
    Matrix_Print(&b, "%.0f");

    Matrix_SwapRows(&b, 1, 2);
    Matrix_Print(&b, "%.0f");

    return 0;
}