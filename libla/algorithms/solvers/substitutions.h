#ifndef LA_SUBSTITUTIONS_H_
#define LA_SUBSTITUTIONS_H_

#include "../../matrix.h"
#include <stddef.h>

/**
 * Returns the vectors `x` that satisfies `Lx = b` by forward substitution.
 * 
 * @param L A lower triangular matrix
 * @param b The solution vectors `[b_1 | b_2 | ... | b_n]`
 * @returns The column vectors that satisfy `Lx_1 = b_1`, `Lx_2 = b_2`, ... `Lx_n = b_n` augmented.
 */
Matrix ForwardSubstitution(Matrix *L, Matrix *b);

/**
 * Returns the vectors `x` that satisfies `Lx = b` by forward substitution on an augmented matrix `[L|b]`.
 * 
 * @param Lb The augmented matrix `[L|b_1|b_2|...|b_n]`
 * @param numVectors The number of solution vectors.
 * @returns The column vectors that satisfy `Lx_1 = b_1`, `Lx_2 = b_2`, ... `Lx_n = b_n` augmented.
 */
Matrix ForwardSubstitutionAugmented(Matrix *Lb, size_t numVectors);

/**
 * Returns the vectors `x` that satisfies `Ux = b` by backward substitution.
 * 
 * @param U A lower triangular matrix
 * @param b The solution vectors `[b_1 | b_2 | ... | b_n]`
 * @returns The column vectors that satisfy `Ux_1 = b_1`, `Ux_2 = b_2`, ... `Ux_n = b_n` augmented.
 */
Matrix BackwardSubstitution(Matrix *U, Matrix *b);

/**
 * Returns the vectors `x` that satisfies `Ux = b` by forward substitution on an augmented matrix `[L|b]`.
 * 
 * @param Lb The augmented matrix `[U|b_1|b_2|...|b_n]`
 * @param numVectors The number of solution vectors.
 * @returns The column vectors that satisfy `Ux_1 = b_1`, `Ux_2 = b_2`, ... `Ux_n = b_n` augmented.
 */
Matrix BackwardSubstitutionAugmented(Matrix *Ub, size_t numVectors);

#endif // LA_SUBSTITUTIONS_H_