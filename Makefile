CC=gcc
CFLAGS=-Wall

FILES=la_matrix.c la_arithmetic.c

main: main.c
	${CC} ${CFLAGS} -o main main.c ${FILES}
	mv main ./bin