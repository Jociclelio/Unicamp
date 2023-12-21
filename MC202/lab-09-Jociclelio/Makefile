all: dracarys

dracarys: dracarys.o arvore_de_busca_binaria.o acumulador.o
	gcc dracarys.o arvore_de_busca_binaria.o acumulador.o -lm -o dracarys

arvore_de_busca_binaria.o: arvore_de_busca_binaria.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm arvore_de_busca_binaria.c

acumulador.o: acumulador.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm acumulador.c

dracarys.o: dracarys.c 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm dracarys.c

