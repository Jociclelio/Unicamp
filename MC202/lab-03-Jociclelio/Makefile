all: golfe

golfe: golfe.o partida.o circuito.o
	gcc golfe.o partida.o circuito.o -lm -o golfe

golfe.o: golfe.c partida.h circuito.h
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm golfe.c

circuito.o: circuito.c circuito.h
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm circuito.c

partida.o: partida.c circuito.h
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm partida.c
