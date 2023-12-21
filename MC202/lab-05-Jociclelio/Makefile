all: testar

testar: batmemory
	python3 testar.py -c && valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./batmemory <./testes/teste2.in

rodar: batmemory
	./batmemory < testes/teste1.in	

batmemory: batmemory.o batmemoria_virtual.o vetor_dinamico.o
	gcc batmemory.o batmemoria_virtual.o vetor_dinamico.o -lm -o batmemory

batmemory.o: batmemory.c 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm batmemory.c

batmemoria_virtual.o: batmemoria_virtual.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm batmemoria_virtual.c

vetor_dinamico.o: vetor_dinamico.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm vetor_dinamico.c

