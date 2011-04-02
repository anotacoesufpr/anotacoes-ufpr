# Compila os .java de ./src, gerando os .class em ./bin
# Cria scripts BASH executávies no diretório corrente

all: compilacao exec

MODULES=Vertice Aresta Grafo BuscaEmLargura CombinationGenerator Isomorfismo KConexo

compilacao: $(MODULES)
	@echo "Compilação realizada com sucesso!"

exec:
	@chmod +x k-conexo
	@chmod +x isomorfos


Vertice:
	javac -classpath ./src -d ./bin ./src/$@.java


Aresta:
	javac -classpath ./src -d ./bin ./src/$@.java


Grafo:
	javac -classpath ./src -d ./bin ./src/$@.java


BuscaEmLargura:
	javac -classpath ./src -d ./bin ./src/$@.java


CombinationGenerator:
	javac -classpath ./src -d ./bin ./src/$@.java


Isomorfismo:
	javac -classpath ./src -d ./bin ./src/$@.java


KConexo:
	javac -classpath ./src -d ./bin ./src/$@.java


clean:
	rm -f bin/*

cleanup: clean
	
