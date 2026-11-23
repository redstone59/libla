#ifndef LA_SUBSTITUTIONS_H_
#define LA_SUBSTITUTIONS_H_

#include "../../matrix.h"
#include <stddef.h>

Matrix ForwardSubstitution(Matrix *a, Matrix *b);
Matrix ForwardSubstitutionAugmented(Matrix *ab, size_t numVectors);

Matrix BackwardSubstitution(Matrix *a, Matrix *b);
Matrix BackwardSubstitutionAugmented(Matrix *ab, size_t numVectors);

#endif // LA_SUBSTITUTIONS_H_