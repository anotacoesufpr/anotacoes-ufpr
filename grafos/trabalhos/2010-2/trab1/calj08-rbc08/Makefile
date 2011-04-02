# Compilador C++
CC=g++

# Paraâmetros de compilação
CFLAGS=-Wall -g -O3

# Nome do Executável do BFS
BFSEXEC=bfs

# Nome do Executável do DFS
DFSEXEC=dfs

LIBS=src/lib/vertice.o src/lib/aresta.o src/lib/grafo.o

all: $(LIBS)
	$(CC) $(CFLAGS) -o $(BFSEXEC) $(LIBS) src/$(BFSEXEC).cpp
	$(CC) $(CFLAGS) -o $(DFSEXEC) $(LIBS) src/$(DFSEXEC).cpp


src/$(DFSEXEC).o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/$(BFSEXEC).o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@

src/lib/vertice.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@

src/lib/aresta.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@

src/lib/grafo.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@

clean:
	rm -rf *.o src/*.o src/lib/*.o

cleanup: clean
	rm -f $(DFSEXEC) $(BFSEXEC)

