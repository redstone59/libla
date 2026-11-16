#include <stdio.h>

#include "la_matrix.h"
#include "la_arithmetic.h"

int main(int argc, char** argv) {
    Matrix a = Matrix_New(2, 3, (float[6]) {
        2, 3, 4, 
        1, 0, 0
    });
    Matrix_Print(&a);

    Matrix b = Matrix_New(3, 2, (float[6]) {
        0, 1000, 
        1,  100, 
        0,   10
    });
    Matrix_Print(&b);

    Matrix c = Matrix_Multiply(a, b);
    Matrix_Print(&c);

    Matrix d = Matrix_AddScalar(a, 5);
    Matrix_Print(&d);

    return 0;
}