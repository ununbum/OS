OBJ = main.o list.o hash.o bitmap.o
SRC = main.c list.c hash.c bitmap.c

CC = gcc
CFLAGS = -Wall -g

TAR = testlib

$(TAR): $(OBJ) list.h hash.h bitmap.h
	          $(CC) -Wall -o $(TAR) $(OBJ)

clean: 
	rm $(OBJ) $(TAR)
