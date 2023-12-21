all: mapeamento

testar: compilar
	python3 testar.py -c && valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./mapeamento <./testes/teste2.in

rodar: compilar
	./mapeamento < testes/teste1.in	

mapeamento: mapeamento.o matriz.o 
	gcc  mapeamento.o matriz.o -lm -o mapeamento

mapeamento.o: 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm mapeamento.c

matriz.o: 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm matriz.c




