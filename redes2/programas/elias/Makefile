CC=gcc
CPARAMS=-Wall -g

FILES=tcp-client tcp-server udp-client udp-server


all: $(FILES)



tcp-client:
	$(CC) $(CPARAMS) -o $@ $@.c


tcp-server:
	$(CC) $(CPARAMS) -o $@ $@.c


udp-client:
	$(CC) $(CPARAMS) -o $@ $@.c


udp-server:
	$(CC) $(CPARAMS) -o $@ $@.c


clean:
	rm -f *.o

cleanup:
	rm -f $(FILES)


