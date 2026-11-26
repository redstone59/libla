# `libla` - a linear algebra library in C

`libla` is a library that is meant to provide an easy interface for working with matrices in C. 

```c
#include "libla/matrix.h"
#include "libla/algorithms/algorithms.h"

int main(int argc, char** argv) {
    Matrix a = Matrix_New(3, 4, (float[12]) {
         2,  1, -1,   8, 
        -3, -1,  2, -11,
        -2,  1,  2,  -3,
    });
    Matrix_Print(&a, "%.0f");

    GaussianElimination(&a);
    Matrix_Print(&a, "%.0f");
    
    Matrix_Destroy(&a);
    return 0;
}
```

# Features

- Able to store matrices with full storage or sparse storage.
- Basic matrix arithmetic between matrix and matrix and matrix and scalar.
- Elementary row operations on matrices
- Gaussian elimination, backward and forward substitution.
- Automatic memory management using a garbage collector.

To see future plans, check [the roadmap](ROADMAP.md).

# Contributing

As long as you don't use generative artificial intelligence tools, then I'll take a look at it. Other rules to be decided.

# Building

> [!NOTE]
> This has *not* been tested on platforms other than Linux.

## Macros

### Memory management

- `LA_ALLOC` (`./libla/common.h`): Defines the memory allocation function. Must have same calling convention as `malloc`. Defaults to `malloc`.
- `LA_FREE` (`./libla/common.h`): Defines the memory free function. Must have same calling convention as `free`. Defaults to `free`.
- `LA_REALLOC` (`./libla/common.h`): Defines the memory reallocation function. Must have same calling convention as `realloc`. Defaults to `realloc`.

> [!NOTE]
> If `LA_ALLOC`, `LA_FREE`, and `LA_REALLOC` are defined, then the library will not rely on `stdlib.h` to handle memory.

### Other

- `LA_NO_ASSERT` (`./libla/common.h`): If this macro is defined, all assertions are removed.
- `LA_NO_FANCY_PRINT` (`./libla/matrix.c`): If this macro is defined, `Matrix_Print()` will not print the braces.

## Initialising the directory

```console
$ make init
```

This creates two subdirectories that the Makefile compiles into.

## Cleaning

```console
$ make clean
```

Removes all files inside of `./bin/` and `./build/`.

## Building normally

```console
$ make main
```
This compiles the library and `main.c` to executable `main`. Useful if you wish to mess around with the library.

## Building with debug

```console
$ make debug
```
This is the same as `main` but with `gdb` and `-fsanitize=address`.

## Building as a shared library

```console
$ make so
```

> [!IMPORTANT]
> This isn't complete at all, and is a future endeavour of this project.

---

*Last modified: 26/11/26*