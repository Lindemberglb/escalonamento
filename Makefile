CC = gcc
CFLAGS = -Wall -Wextra -std=c11

scheduler: main.c tarefa.c
	$(CC) $(CFLAGS) main.c tarefa.c -o scheduler

clean:
	rm -f scheduler