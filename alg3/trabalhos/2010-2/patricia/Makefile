#CFLAGS=-W -ansi -pedantic -ggdb -lm
CFLAGS=-lm

tudo: libPatricia libPatriz
	gcc $(CFLAGS) apl.c libPatricia.o libPatriz.o -o Pat
libPatricia:
	gcc $(CFLAGS) -c libPatricia.c	
libPatriz: libPatricia
	gcc $(CFLAGS) -c libPatriz.c 
clean:
	rm -f *~ *.bak *.core
cleanup:
	rm -f *~ *.bak *.core *.o apl
