#ifndef LA_SUBSTITUTIONS_H_
#define LA_SUBSTITUTIONS_H_

#include "../../matrix.h"

Matrix ForwardSubstitution(Matrix *a, Matrix *b);
Matrix ForwardSubstitutionAugmented(Matrix *ab);

Matrix BackwardSubstitution(Matrix *a, Matrix *b);
Matrix BackwardSubstitutionAugmented(Matrix *ab);

#endif // LA_SUBSTITUTIONS_H_