CC = gcc
CFLAGS = -Wall -Wextra -std=c11

scheduler: main.c tarefa.c simulacao.c
	$(CC) $(CFLAGS) main.c tarefa.c simulacao.c -o scheduler

clean:
	rm -f scheduler