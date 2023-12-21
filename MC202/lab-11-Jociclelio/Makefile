all: halloween
halloween: halloween.o hash.o 
	gcc halloween.o hash.o -lm -o halloween

halloween.o: halloween.c 
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm halloween.c

hash.o: hash.c
	gcc -std=c99 -Wall -Werror -Wvla -c -g -lm hash.c

