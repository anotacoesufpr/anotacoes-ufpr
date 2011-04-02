CC = gcc
PARAMS = -g

# Nome do executável
EXEC = trab

all:
	$(CC) $(PARAMS) -c aloca.s -o aloca.o
	$(CC) $(PARAMS) -c teste.c -o teste.o
	$(CC) $(PARAMS) -o $(EXEC) aloca.o teste.o
	$(CC) $(PARAMS) -c bruno.c -o bruno.o
	$(CC) $(PARAMS) -o bruno aloca.o bruno.o



clean:
	rm -rf *.o
