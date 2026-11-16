#ifndef LA_ARITHMETIC_H_
#define LA_ARITHMETIC_H_

#include "la_matrix.h"

Matrix Matrix_Add(Matrix a, Matrix b);
Matrix Matrix_Sub(Matrix a, Matrix b);
Matrix Matrix_Multiply(Matrix a, Matrix b);

Matrix Matrix_AddScalar(Matrix a, float scalar);
Matrix Matrix_SubScalar(Matrix a, float scalar);
Matrix Matrix_MultiplyScalar(Matrix a, float scalar);

Matrix Matrix_Inverse(Matrix self);
float Matrix_Det(Matrix self);
Matrix Matrix_Tranpose(Matrix self);

#endif // LA_ARITHMETIC_H_