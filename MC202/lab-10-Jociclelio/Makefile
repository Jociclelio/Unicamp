all: cozinha
cozinha: cozinha.o sobrevivente.o fila_de_pedidos.o
	gcc cozinha.o sobrevivente.o fila_de_pedidos.o -lm -o cozinha

cozinha.o: cozinha.c 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm cozinha.c

sobrevivente.o: sobrevivente.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm sobrevivente.c

fila_de_pedidos.o: fila_de_pedidos.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm fila_de_pedidos.c
