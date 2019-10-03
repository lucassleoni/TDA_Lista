CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compile: lista.c minipruebas_lista_se.c
	$(CC) $(CFLAGS) *.c -o lista_se -g 

lista: compile
	clear
	./lista_se

valgrind: compile
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se