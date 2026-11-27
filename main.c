#include <stdio.h>

#include "libla/gc/gc.h"

#include "libla/matrix.h"
#include "libla/arithmetic.h"
#include "libla/algorithms/algorithms.h"

int main(int argc, char** argv) {
    GC_Init(256);

    // Create matrix-vector problem.
    Matrix A = Matrix_New(3, 3, (float[9]) {
         1,  1,  1,
        -3, -1,  2,
         0,  4, -1
    });
    Matrix b = Matrix_New(3, 1, (float[3]) {
        6,
        1,
        5
    });

    Matrix Ab = Matrix_Augment(&A, &b);
    printf("[A|b] =\n");
    Matrix_Print(&Ab, "%.0f");
    
    // Perform Gaussian elimination and backward substitution to solve.
    Matrix Uz = Matrix_Copy(&Ab);
    GaussianElimination(&Uz);
    printf("[U|z] =\n");
    Matrix_Print(&Uz, "%.0f");

    Matrix x = BackwardSubstitutionAugmented(Uz, 1);
    printf("x =\n");
    Matrix_Print(&x, "%.0f");

    // Check that A * x is equal to b.
    Matrix check = Matrix_Multiply(A, x);
    printf("A * x =\n");
    Matrix_Print(&check, "%.0f");
    
    GC_Destroy();
    return 0;
}