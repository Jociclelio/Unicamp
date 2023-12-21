all: livros

livros: livros.o lista_ligada.o 
	gcc livros.o lista_ligada.o  -lm -o livros

livros.o: livros.c 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm livros.c

lista_ligada.o: lista_ligada.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm lista_ligada.c

