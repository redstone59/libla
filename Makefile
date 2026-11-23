CC=gcc
CFLAGS=-Wall -std=c99

DA_FILES=./libla/array/dynamic_array.c
ALGORITHM_FILES=./libla/algorithms/gaussian_elimination.c
SOLVER_FILES=./libla/algorithms/solvers/substitutions.c
MATRIX_STORAGE_FILES=./libla/matrix_storage/full_matrix.c ./libla/matrix_storage/scalar_matrix.c ./libla/matrix_storage/sparse_matrix.c
FILES=./libla/matrix.c ./libla/arithmetic.c ${MATRIX_STORAGE_FILES} ${DA_FILES} ${ALGORITHM_FILES}

main: ${FILES}
	${CC} ${CFLAGS} -o main main.c ${FILES}
	@mv main ./bin

debug: ${FILES}
	${CC} ${CFLAGS} -ggdb -fsanitize=address -o main main.c ${FILES}
	@mv main ./bin

so: ${FILES}
# TODO: do metaprogramming so then it also automatically creates the header file
#       better yet, turn it into a header-only library. that would be cool.
	${CC} ${CFLAGS} -shared -o libla.so -fPIC ${FILES}
	@mv libla.so ./bin