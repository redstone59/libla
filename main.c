#include <stdio.h>

#include "./libla/la_matrix.h"
#include "./libla/la_arithmetic.h"

int main(int argc, char** argv) {
    Matrix a = Matrix_New(2, 3, (float[6]) {
        2, 3, 4, 
        1, 0, 0
    });
    Matrix_Print(&a);

    Matrix b = Matrix_New(2, 3, (float[6]) {
        5, 2, 2,
        8, 1, 8
    });
    Matrix_Print(&b);

    Matrix c = Matrix_MultiplyScalar(a, 5);
    Matrix_Print(&c);
    
    return 0;
}