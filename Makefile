CC=gcc
CFLAGS=-Wall

FILES=./libla/matrix.c ./libla/arithmetic.c ./libla/matrix_storage/full_matrix.c ./libla/matrix_storage/scalar_matrix.c ./libla/matrix_storage/sparse_matrix.c

main: main.c
	${CC} ${CFLAGS} -o main main.c ${FILES}
	mv main ./bin