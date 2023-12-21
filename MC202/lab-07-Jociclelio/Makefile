all: simulador

simulador: simulador.o fila.o pilha.o peca.o registro.o operario.o
	gcc simulador.o peca.o fila.o pilha.o registro.o operario.o -lm -o simulador

peca.o: peca.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm peca.c

registro.o: registro.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm registro.c

simulador.o: simulador.c 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm simulador.c

fila.o: fila.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm fila.c

pilha.o: pilha.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm pilha.c

operario.o: operario.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm operario.c
