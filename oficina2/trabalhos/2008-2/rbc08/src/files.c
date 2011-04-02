#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>

#include "global.h"
#include "error.h"
#include "memory.h"
#include "my_regex.h"



/* Protótipos de funções não inclusas em files.h */
void salva_coordenadas_caracteres(char c, int x, int y, tLABIRINTO *labirinto, tJOGADOR *jogador);
void carregar_mapa_from_txt(tLABIRINTO *labirinto, tJOGADOR *jogador);
void carregar_mapa_from_bin(tLABIRINTO *labirinto, tJOGADOR *jogador);
int is_binary_file(const char *filename);


/**
 * @brief Função utilizada para abrir arquivos. Se a abertura falhar, é gerado um erro, porém, a execução não é interrompida. Ou seja, genericamente, a falha na abertura de arquivos não é considerada um erro fatal.
 * @param arquivo Nome do arquivo que se deseja abrir.
 * @param modo Modo de abertura do arquivo.
 * @return Retorna um ponteiro para o arquivo aberto ou NULL em caso de falha.
**/
FILE * abrir_arquivo(const char *arquivo, const char *modo)
{
	FILE *fp;
	
	/* A abertura do arquivo só deve ocorrer se o nome passado como parâmetro for diferente de "stdin" e "stdout" */
	
	if (strcmp(arquivo, "stdin") == 0)
	{
		return stdin;
	}
	else
	{
		if (strcmp(arquivo, "stdin") == 0)
		{
			return stdout;
		}
		else
		{
			if ((fp = fopen(arquivo, modo)) == NULL)
			{
				char msg[40];
				sprintf("Erro ao abrir o arquivo '%d'", arquivo);
				log_error(msg, 0, __FILE__, __LINE__);
				return NULL;
			}
			else
			{
				return fp;
			}
		}
	}
}
/********************************************************/



/**
 * @brief Função para fechar arquivo.
 * @param fp Ponteiro para o arquivo que se deseja fechar.
 * @return Retorna o valor retornado por fclose().
*/
int fechar_arquivo(FILE *fp)
{
	return fclose(fp);
}
/*********************************************************/



/**
 * @brief Função que carrega o mapa do arquivo e o armazena na matriz mapa. Também são armazenadas na estrutura "labirinto", as posições das portas, chaves, saída(s) e a posição do jogador.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void carregar_mapa(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	
	/* Verifica se o arquivo é binário ou não, chamando a função adequada para cada caso */
	
	if (is_binary_file(labirinto->in_file))
	{
		carregar_mapa_from_bin(labirinto, jogador);
	}
	else
	{
		carregar_mapa_from_txt(labirinto, jogador);
	}
}
/******************************************************/



/*
 * @brief Carrega o mapa lido a partir de um arquivo texto.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void carregar_mapa_from_txt(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	FILE *fp;
	char c, line[10];
	int i = 0, j = 0, chars_mapa = 0, total_chars_mapa;
	
	
	if ((fp = abrir_arquivo(labirinto->in_file, "r")) == NULL)
	{
		exit(1);
	}
	

	/* Lê a primeira linha do arquivo e usa sscanf() para armazenar o tamanho do labirinto */
	fgets(line, 10, fp);
	sscanf(line, "%d %d", &labirinto->linhas, &labirinto->colunas);
	
	/* Total de caracteres que o mapa possui */
	total_chars_mapa = labirinto->linhas * labirinto->colunas;
	
	/* Aloca memória para a matriz que representa o mapa */
	alocar_memoria_mapa(labirinto);
	
	
	/* Lê os caracteres do arquivo e os armazena na matriz "mapa" */
	while (chars_mapa < total_chars_mapa)
	{
		c = fgetc(fp);
		
		if (c != '\n')
		{
			/* Se o valor corrente de j (representante das colunas da matriz) for igual ao número de colunas do labirinto, incrementa-se o número da linha (i) e zera-se o valor de j, a fim de escrever o caractere na linha seguinte. */
			if (j == labirinto->colunas)
			{
				i++;
				j = 0;
			}
			
			labirinto->mapa[i][j] = c;
			
			salva_coordenadas_caracteres(c, j, i, labirinto, jogador);			
			
			j++;
			
			chars_mapa++;
		}
	}
	
	fechar_arquivo(fp);
	
	salva_posicao(jogador);
}
/*******************************************************/


/*
 * @brief Carrega o mapa e as demais informações a partir de um arquivo binário, gerado pelo próprio programa, quando o jogador pausa o jogo.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @param jogador Ponteiro para a estrutura tJOGADOR.
*/
void carregar_mapa_from_bin(tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	FILE *fp;
	register unsigned int i = 0;
	
	fp = abrir_arquivo(labirinto->in_file, "rb");
	fread(labirinto, sizeof(tLABIRINTO), 1, fp);
	fread(jogador, sizeof(tJOGADOR), 1, fp);
	
	
	/* Aloca memória para a matriz que representa o mapa */
	alocar_memoria_mapa(labirinto);
	
	/* Lê o mapa */
	for (i = 0; i < labirinto->linhas; i++)
	{
		fread(labirinto->mapa[i], sizeof(char), labirinto->colunas, fp);
	}
	
	/* Aloca memória para a matriz de passos do jogador */
	aloca_memoria_passos(jogador, jogador->caminho.capacidade);
	
	/* Lê a matriz dos passos do jogador */
	for (i = 0; i < jogador->caminho.tamanho; i++)
	{
		fread(jogador->caminho.passos[i], sizeof(unsigned int), 2, fp);
	}
	
	
	fechar_arquivo(fp);
	
}
/*************************************************/




/*
 * @brief Esta função salva as coordenadas dos principais caracteres do labirinto. Ela viabiliza a implementação do modo batch, salvando as posições de portas, chaves, saídas e a posição inicial do jogador.
*/
void salva_coordenadas_caracteres(char c, int x, int y, tLABIRINTO *labirinto, tJOGADOR *jogador)
{
	switch (c)
	{
		case CHAR_JOGADOR:
			jogador->pos_x = x;
			jogador->pos_y = y;
			break;
	}
}
/*****************************************************/



/**
 * @brief Função que verifica o mime-type do arquivo passado como parâmetro, a fim de classificá-lo como binário ou não.
 * @param filename Nome do arquivo cujo mime-type será verificado.
 * @return Retorna 1 se o arquivo for binário. Caso contrário retorna 0. 
*/
int is_binary_file(const char *filename)
{
	FILE *fp;
	char str[50], com[50];
	int retorno;
	
	sprintf(com, "file -bi %s", filename);
	
	/*========================================================================================
	| A função popen() funciona semelhantemente a system(). Ela executa um comando no shell e |
	| armazena seu resultado num ponteiro, que poderá ser lido como se fosse um arquivo texto |
	| comum.                                                                                  |
	|========================================================================================*/
	
	fp = popen(com, "r");
	
	fgets(str, 50, fp);
	
	/* Função implementada em my_regex.c. Assemelha-se à função homônima do PHP. */
	if ( preg_match("^application\\/(octet-stream|bin(ary)?)", str) )
	{
		retorno = 1;
	}
	else
	{
		retorno = 0;
	}
		
	pclose(fp);
	
	return retorno;
}
/*************************************************************/
