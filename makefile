FLAGS= -g -Wall
CC = gcc

frequency: frequency.c frequency.h
	$(CC) $(FLAGS) frequency.c -o frequency


.PHONY:  clean

clean:
	rm frequency
