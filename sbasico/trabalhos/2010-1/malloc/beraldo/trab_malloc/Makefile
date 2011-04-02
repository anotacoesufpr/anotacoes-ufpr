CC = gcc
PARAMS = -g

# Nome do executável
EXEC = meuMalloc

all:
	$(CC) $(PARAMS) -c aloca.s -o aloca.o
	$(CC) $(PARAMS) -c meuMalloc.c -o meuMalloc.o
	$(CC) $(PARAMS) -o $(EXEC) aloca.o meuMalloc.o



clean:
	rm -rf *.o $(EXEC)
