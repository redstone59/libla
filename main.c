#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv) {
    float values[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    Matrix a = Matrix_New(3, 3, values);

    for (int row = 0; row < a.rows; row++) {
        for (int col = 0; col < a.cols; col++) {
            printf("%.2f ", Matrix_GetCell(&a, row, col));
        }
        printf("\n");
    }

    return 0;
}