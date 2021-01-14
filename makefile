FLAGS= -g -Wall
CC = gcc

all : frequency

frequency: frequency.c frequency.h
	$(CC) $(FLAGS) frequency.c -o frequency


.PHONY: all clean

clean:
	rm frequency
