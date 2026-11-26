CC=gcc
CFLAGS=-Wall -std=c99

DA_FILES=./libla/array/dynamic_array.c
GC_FILES=./libla/gc/gc.c ./libla/gc/allocation_array.c
ALGORITHM_FILES=./libla/algorithms/gaussian_elimination.c
SOLVER_FILES=./libla/algorithms/solvers/substitutions.c
MATRIX_STORAGE_FILES=./libla/matrix_storage/full_matrix.c ./libla/matrix_storage/scalar_matrix.c ./libla/matrix_storage/sparse_matrix.c
FILES=./libla/matrix.c ./libla/arithmetic.c ./libla/logging.c ${MATRIX_STORAGE_FILES} ${DA_FILES} ${ALGORITHM_FILES} ${SOLVER_FILES} ${GC_FILES}

OBJECT_NAME=libla

init:
	@mkdir bin
	@mkdir build

clean:
	@rm -r ./build
	@rm -r ./bin
	@make init

main: main.c
	@echo Building main...
	@make static
	${CC} ${CFLAGS} -o $@ $< -l:${OBJECT_NAME}.a -L./bin
	@mv main ./bin

# TODO: do some %.o: %.c shit to only compile the changed shit
# See:
# - https://www.twoistoomany.com/make-wildcard-patterns-aka-build-all-the-files-you-find/
# - https://stackoverflow.com/questions/4036191/sources-from-subdirectories-in-makefile
static: ${FILES}
	@echo Compiling libla to static library...
	${CC} ${CFLAGS} -c $^
	@mv *.o ./build
	ar rvs ${OBJECT_NAME}.a build/*
	@mv ${OBJECT_NAME}.a ./bin

shared: ${FILES}
# TODO: do metaprogramming so then it also automatically creates the header file
#       better yet, turn it into a header-only library. that would be cool.
	${CC} ${CFLAGS} -shared -o ${OBJECT_NAME}.so -fPIC ${FILES}

debug: ${FILES}
	${CC} ${CFLAGS} -ggdb -fsanitize=address -o main main.c ${FILES} -DLA_LOG_THRESHOLD=LA_LOGLEVEL_DEBUG
	@mv main ./bin
	@mv ${OBJECT_NAME}.so ./bin

test:
	@echo TODO: test

benchmark:
	@echo TODO: benchmark