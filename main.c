#include <stdio.h>

#include "./libla/matrix.h"
#include "./libla/arithmetic.h"

int main(int argc, char** argv) {
    Matrix a = Matrix_New(2, 3, (float[6]) {
        2, 3, 4, 
        1, 0, 0
    });
    Matrix_Print(&a);

    Matrix c = Matrix_Multiply(Matrix_Transpose(a), a);
    Matrix_Print(&c);
    
    return 0;
}