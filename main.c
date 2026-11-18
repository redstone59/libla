#include <stdio.h>

#include "./libla/la_matrix.h"
#include "./libla/la_matrix_types.h"

int main(int argc, char** argv) {
    Matrix a = FullMatrix_New(2, 3, (float[6]) {
        2, 3, 4, 
        1, 0, 0
    });

    Matrix_Print(&a);
    return 0;
}