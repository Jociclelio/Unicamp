
CC=gcc

C_FLAGS=-std=c99 -Wall -Werror -Wvla -c -g -lm

all: redecomep
redecomep: redecomep.o grafo.o lista.o fila.o
	$(CC) redecomep.o grafo.o lista.o fila.o -o redecomep

redecomep.o: redecomep.c 
	$(CC) $(C_FLAGS) redecomep.c

grafo.o: grafo.c
	$(CC) $(C_FLAGS) grafo.c

fila.o: fila.c
	$(CC) $(C_FLAGS) fila.c
lista.o: lista.c
	$(CC) $(C_FLAGS) lista.c

