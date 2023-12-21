all: expressoes

expressoes: expressoes.o arvore_expressoes.o  arvore_binaria.o otimizador_de_expressoes.o
	gcc expressoes.o arvore_binaria.o arvore_expressoes.o otimizador_de_expressoes.o -lm -o expressoes

arvore_binaria.o: arvore_binaria.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm arvore_binaria.c

expressoes.o: expressoes.c 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm expressoes.c

arvore_expressoes.o: arvore_expressoes.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm arvore_expressoes.c

otimizador_de_expressoes.o: otimizador_de_expressoes.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm otimizador_de_expressoes.c
