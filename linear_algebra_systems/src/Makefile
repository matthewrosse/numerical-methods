CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g
DEPS=matrix.c linear_algebra.c
LIBS=-lm


all: main.c
	$(CC) main.c $(DEPS) -o main $(CFLAGS) $(LIBS)
