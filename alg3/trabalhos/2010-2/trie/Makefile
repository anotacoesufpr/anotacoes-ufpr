CFLAGS=-W -ansi -pedantic -ggdb
tudo: apl
apl: apl.o libArvBin.o
	gcc $(CFLAGS) -o apl apl.o libArvBin.o
libArvBin.o: libArvBin.c libArvBin.h
	gcc $(CFLAGS) -c libArvBin.c -o libArvBin.o
apl.o: apl.c libArvBin.h
	gcc $(CFLAGS) -c apl.c -o apl.o
clean:
	rm -f *~ *.bak *.core
cleanup:
	rm -f *~ *.bak *.core *.o apl
