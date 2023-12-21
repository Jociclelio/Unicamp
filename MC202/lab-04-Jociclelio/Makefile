all: testar

testar: compilar
	python3 testar.py -c && valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./mapeamento <./testes/teste2.in


rodar: compilar
	./mapeamento < testes/teste1.in	

compilar: 
	gcc -std=c99 -Wall -Werror -Wvla -g -lm -c mapeamento.c -o mapeamento

