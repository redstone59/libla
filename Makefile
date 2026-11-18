CC=gcc
CFLAGS=-Wall

FILES=./libla/la_matrix.c ./libla/la_arithmetic.c ./libla/matrix_storage/la_fullmatrix.c ./libla/matrix_storage/la_scalarmatrix.c

main: main.c
	${CC} ${CFLAGS} -o main main.c ${FILES}
	mv main ./bin