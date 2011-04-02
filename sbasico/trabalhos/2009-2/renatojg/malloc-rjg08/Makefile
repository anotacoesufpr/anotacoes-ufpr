all: alloc.o teste.o
	gcc -o alloc alloc.o teste.o -g -m32

alloc.o: alloc.s
	as alloc.s -o alloc.o -g --32

teste.o: teste.c
	gcc -c teste.c -g -m32

clean:
	rm *.o
	rm alloc
