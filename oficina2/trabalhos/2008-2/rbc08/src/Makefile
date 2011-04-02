# Diretório onde será salvo o arquivo executável e os arquivos binários
BIN_DIRECTORY=../bin/


# Nome do arquivo executável
EXEC_FILENAME=labirinto


# Diretório em que será gerada a documentação. 
# O valor dessa variável é usada somente na regra de limpeza. Para alterar o diretório de destino da documentação, é necessário alterar o Doxyfile.
HTML_DIRECTORY=../html/



# Compilador a ser utilizado
CC=gcc

# Parâmetros de compilação
PARAMS=-g -Wall


#---------------------------------------#



# Regra principal. Realiza a compilação e gera a documentação
tudo: limpa compilar doc
	@echo "Compilação realizada com sucesso"


# Regra responsável pela compilação do programa e geração do executável
compilar:GLOBAL FILES ERROR MEMORY MY_REGEX LABIRINTO
	@echo "Compilando os módulos e gerando o arquivo executável..."
	@$(CC) $(PARAMS) $(BIN_DIRECTORY)*.o -o $(BIN_DIRECTORY)$(EXEC_FILENAME) -lncurses




########################################
# Compilação dos módulos do programa   #
########################################

# Após a compilação, os respectivos arquivos .o são movidos para o diretório dos arquivos binários

LABIRINTO:
	@$(CC) $(PARAMS) -c labirinto.c
	@mv labirinto.o $(BIN_DIRECTORY)labirinto.o


GLOBAL:
	@$(CC) $(PARAMS) -c global.c
	@mv global.o $(BIN_DIRECTORY)global.o

FILES:
	@$(CC) $(PARAMS) -c files.c
	@mv files.o $(BIN_DIRECTORY)files.o


MEMORY:
	@$(CC) $(PARAMS) -c memory.c
	@mv memory.o $(BIN_DIRECTORY)memory.o


ERROR:
	@$(CC) $(PARAMS) -c error.c
	@mv error.o $(BIN_DIRECTORY)error.o

MY_REGEX:
	@$(CC) $(PARAMS) -c my_regex.c
	@mv my_regex.o $(BIN_DIRECTORY)my_regex.o


##---------------------------##






# Criação da documentação usando o Doxygen
# A saída padrão é redirecionada para /dev/null, a fim de não mostrá-la durante a execução do Makefile
doc:
	@echo "Gerando a documentação..."
	@doxygen Doxyfile > /dev/null



limpa:
	@echo "Realizando limpeza..."
	@rm -rf *.~ *.~* *.bak
	@echo "Limpeza realizada com sucesso"


faxina: limpa
	@echo "Realizando faxina..."
	@rm -rf $(BIN_DIRECTORY)* $(HTML_DIRECTORY)*
	@echo "Faxina realizada com sucesso"
	
