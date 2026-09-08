CC = gcc
CFLAGS = -Wall -Wextra -std=c11

scheduler: main.o tarefa.o
	$(CC) $(CFLAGS) main.o tarefa.o -o scheduler

main.o: main.c tarefa.h
	$(CC) $(CFLAGS) -c main.c

tarefa.o: tarefa.c tarefa.h
	$(CC) $(CFLAGS) -c tarefa.c

clean:
	rm -f scheduler *.o