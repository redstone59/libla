#include <stdio.h>

#include "libla/matrix.h"
#include "libla/arithmetic.h"
#include "libla/matrix_types.h"


int main(int argc, char** argv) {
    Matrix a = Matrix_New(3, 4, (float[12]) {
         2,  1, -1,   8, 
        -3, -1,  2, -11,
        -2,  1,  2,  -3,
    });
    Matrix_Print(&a, "%.0f");

    GaussianElimination(&a);
    Matrix_Print(&a, "%.0f");

    float row[8] = {  0,  0,  1,  1,  2,  2,  2,  3 };
    float col[8] = {  0,  1,  1,  3,  2,  3,  4,  5 };
    float val[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
    float *sparse[3] = { row, col, val };
    
    Matrix b = SparseMatrix_New(4, 6, sparse, 8, 16);
    Matrix_Print(&b, "%.0f");

    Matrix_AddMultipleOfRow(&b, -3 / 2.f, 0, 1);
    Matrix_Print(&b, "%.0f");

    return 0;
}