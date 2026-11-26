# Roadmap for `libla`

*Last updated: 26/11/26*

- **Data**
    - [ ] More comprehensive matrix storage
        - [x] Full storage matrices
        - [x] Sparse
        - [ ] Compressed Sparse Row (CSR)
        - [ ] Triangular/Symmetric
        - [ ] Banded matrices
        - [ ] Be able to convert between any of these matrix types
    - [ ] Be able to use types other than `float`s in matrices
        - [ ] Non-primitive types allowed with type generic math macros

- **Memory**
    - [x] Ability to decouple from `libc` memory functions
    - [x] Use of arenas or a garbage collector to prevent leaks
        - [ ] Potentially change garbage collector to hashmap/fat pointer for speed (if it is actually faster)

- **Matrix operations**
    - [x] Basic matrix-matrix arithmetic
    - [x] Basic matrix-scalar arithmetic
    - [ ] Determinants and inverses
    - [x] Elementary row operations
    - [ ] Check matrix properties
        - [ ] Cache matrix properties for speed
    - [ ] Set row/column of matrix
        - [ ] Set arbitrary range of cells
    - [ ] Norms
        - [ ] 1-norm (maximum absolute column sum)
        - [ ] 2-norm (largest singular value)
        - [ ] infinity-norm (maximum absolute row sum)
        - [ ] Frobenius norm
    - [ ] Matrix augmentation

- **Algorithms**
    - [x] Gaussian Elimination
    - [ ] Gauss-Jordan Elimination
    - [x] Forward substitution
    - [x] Backward substitution
    - [ ] Matrix decompositions
        - [ ] LU decomposition
        - [ ] LDL^T decomposition
        - [ ] QR decomposition
        - [ ] Cholesky decomposition GG^T
        - [ ] Eigendecomposition VDV^-1
        - [ ] Singular value decomposition
    - [ ] Generalised matrix linear equation solver (a la MATLAB's `x = A \ b`)

- **Other**
    - [ ] Figure/image generation
    - [ ] Testing codebase with `make test`
        - [ ] Benchmark system
    - [ ] Some way to test if this shit is good on other platforms
    - [ ] Build into stb-style single-header library(?)
    - [ ] Better logging system (i.e. warn floating point error, etc.)