#include <stdio.h>

#include "libla/gc/gc.h"

#include "libla/matrix.h"
#include "libla/arithmetic.h"
#include "libla/matrix_types.h"

#include "libla/algorithms/algorithms.h"

int main(int argc, char** argv) {
    GC_Init(256);

    Matrix a = Matrix_New(3, 4, (float[12]) {
         2,  1, -1,   8, 
        -3, -1,  2, -11,
        -2,  1,  2,  -3,
    });
    Matrix_Print(&a, "%.0f");

    GaussianElimination(&a);
    Matrix_Print(&a, "%.0f");

    GC_Sweep();

    float row[8] = {  0,  0,  1,  1,  2,  2,  2,  3 };
    float col[8] = {  0,  1,  1,  3,  2,  3,  4,  5 };
    float val[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
    float *sparse[3] = { row, col, val };
    
    Matrix s = SparseMatrix_New(4, 6, sparse, 8, 16);
    Matrix_Print(&s, "%.0f");

    GaussianElimination(&s);
    Matrix_Print(&s, "%.0f");

    Matrix u = Matrix_New(3, 3, (float[9]) {
        1, 1, 1,
        0, 1, 1,
        0, 0, 1
    });
    Matrix b = Matrix_New(3, 1, (float[3]) {
        6,
        3,
        1
    });
    Matrix_Print(&u, "%.0f");
    Matrix_Print(&b, "%.0f");

    Matrix x = BackwardSubstitution(&u, &b);
    Matrix_Print(&x, "%.2f");

    Matrix bReconstructed = Matrix_Multiply(u, x);
    Matrix_Print(&bReconstructed, "%.2f");

    Matrix_Destroy(&s);

    GC_Destroy();

    return 0;
}