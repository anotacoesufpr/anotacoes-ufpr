# Universidade Federal do Parana
# CI065 - Algoritmos e teoria dos grafos - 2009/2
# Trabalho Pratico de Programacao - Clique Maxima
# Prof. André Luiz Pires Guedes 
#
# GRR20052411 LOIRTO ALVES DOS SANTOS
# GRR20034170 ARAMIS STACH HAIDUSKI FERNANDES
# GRR20070069 EDSON RAMIRO LUCAS FILHO
PLUGINS = ashf03_erlf07_las05.so

%.so : %.c
	$(CC) -Wall -fPIC -shared $< -o $@ $(CFLAGS)

all: $(PLUGINS)

clean:
	rm -f $(PLUGINS)
