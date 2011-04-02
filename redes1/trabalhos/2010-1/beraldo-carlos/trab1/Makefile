CC=g++
CFLAGS=-Wall -g

LIBS=src/lib/SocketException.o src/lib/MySocket.o src/lib/RawSocket.o src/lib/Pacote.o src/lib/Conexao.o src/lib/Cliente.o src/lib/Servidor.o src/lib/Protocolo.o src/lib/Util.o src/lib/Comandos.o

all: $(LIBS)
	$(CC) $(CFLAGS) -o bin/cliente $^ src/cliente.cpp
	$(CC) $(CFLAGS) -o bin/servidor $^ src/servidor.cpp


src/lib/Protocolo.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/Clienbte.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/Servidor.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/Comandos.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/Util.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/MySocket.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@

src/lib/SocketException.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/RawSocket.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/Pacote.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


src/lib/Conexao.o:
	$(CC) $(CFLAGS) -c $*.cpp -o $@


clean:
	rm -rf *.o bin/* src/*.o src/lib/*.o