CC=gcc
CFLAGS=-Wall -std=c99

DA_FILES=./libla/array/dynamic_array.c
MATRIX_STORAGE_FILES=./libla/matrix_storage/full_matrix.c ./libla/matrix_storage/scalar_matrix.c ./libla/matrix_storage/sparse_matrix.c
FILES=./libla/matrix.c ./libla/arithmetic.c ${MATRIX_STORAGE_FILES} ${DA_FILES} 

main: ${FILES}
	${CC} ${CFLAGS} -o main main.c ${FILES}
	mv main ./bin

debug: ${FILES}
	${CC} ${CFLAGS} -ggdb -fsanitize=address -o main main.c ${FILES}
	mv main ./bin