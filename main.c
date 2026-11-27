#include <stdio.h>
#include <string.h>

#include "libla/gc/gc.h"

#include "libla/matrix.h"
#include "libla/arithmetic.h"
#include "libla/matrix_types.h"

#include "libla/algorithms/algorithms.h"

int main(int argc, char** argv) {
    GC_Init(256);

    Matrix a = Matrix_New(3, 4, (float[12]) {
         1,  1,  1,  6,
        -3, -1,  2,  1,
         0,  4, -1,  5,
    });
    Matrix_Print(&a, "%.0f");
    Matrix u = Matrix_NewEmpty(a.rows, a.cols);
    memcpy(u.cells.asFloatVec, a.cells.asFloatVec, a.count * sizeof(float));

    GaussianElimination(&u);
    Matrix_Print(&u, "%.2f");

    Matrix x = BackwardSubstitutionAugmented(u, 1);
    Matrix_Print(&x, "%.2f");

    Matrix solve = Matrix_Multiply(Matrix_GetRange(&a, RANGE_EXCLUSIVE(0, a.rows), RANGE_EXCLUSIVE(0, a.rows)), x);
    Matrix_Print(&solve, "%.2f");
    
    return 0;
    float row[8] = {  0,  0,  1,  1,  2,  2,  2,  3 };
    float col[8] = {  0,  1,  1,  3,  2,  3,  4,  5 };
    float val[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
    float *sparse[3] = { row, col, val };
    
    Matrix s = SparseMatrix_New(4, 6, sparse, 8, 16);
    Matrix_Print(&s, "%.0f");
    
    GaussianElimination(&s);
    Matrix_Print(&s, "%.0f");
    
    Matrix_Destroy(&s);

    GC_Sweep();

    Matrix insuranceP = Matrix_New(5, 5, (float[25]) {
         1 / 4.f,  3 / 4.f,        0,       0,       0,
         1 / 4.f,        0,  3 / 4.f,       0,       0,
        1 / 16.f, 3 / 16.f,        0, 3 / 4.f,       0,
        1 / 16.f,        0, 3 / 16.f,       0, 3 / 4.f,
        1 / 16.f,        0, 3 / 16.f,       0, 3 / 4.f
    });
    GC_MakePermanent(&insuranceP.cells);
    
    Matrix pn = insuranceP;

    for (int i = 0; i < 2500; i++) {
        pn = Matrix_Multiply(pn, insuranceP);
        if (i % 10 == 0) GC_Sweep();
    }
    Matrix_Print(&pn, "%.4f");
    GC_Sweep();
    
    GC_Destroy();

    return 0;
}