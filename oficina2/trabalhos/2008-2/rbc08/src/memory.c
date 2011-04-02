#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "error.h"



/**
 * @brief Função que aloca memória para a matriz que armazenará o mapa.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
 * @return Retorna uma matriz (vetor bidimensional) na qual serão armazenados os caracteres do mapa.
*/
char ** alocar_memoria_mapa(tLABIRINTO *labirinto)
{
	register int i;
	
	/* Aloca memória para as linhas do labirinto */
	labirinto->mapa = (char **) malloc(labirinto->linhas * sizeof(char*));
	
	if (labirinto->mapa == NULL)
	{
		log_error("Não foi possível alocar memória", 1, __FILE__, __LINE__);
		exit(1);	
	}
	
	/* Aloca memória para as colunas do labirinto */
	for (i = 0; i < labirinto->linhas; i++)
	{
		labirinto->mapa[i] = (char *) malloc(labirinto->colunas * sizeof(char));
		
		if (labirinto->mapa[i] == NULL)
		{
			log_error("Não foi possível alocar memória", 1, __FILE__, __LINE__);
			exit(1);
		}
		
	}
	
	
	return labirinto->mapa;
}
/*********************************************/



/**
 * @brief Função que libera a memória usada pela matriz "mapa".
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
*/
void destroi_mapa(tLABIRINTO *labirinto)
{
	register int i;
	
	if (labirinto->mapa != NULL)
	{
		/* Libera a memória das colunas */
		for (i = 0; i < labirinto->linhas; i++)
		{
			free(labirinto->mapa[i]);
		}
		
		/* Libera a memória das linhas */
		free(labirinto->mapa);
	}
}
/*******************************************/



/**
 * @brief Aloca memória para os arquivos de entrada/saída e lhes atribui os valores padrões.
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
*/
void init_io_files(tLABIRINTO *labirinto)
{
	labirinto->in_file = (char *) malloc(6 * sizeof(char));/* strlen("stdin") == 5 (+=1 (do '\0') */
	
	if (labirinto->in_file == NULL)
	{
		log_error("Erro ao alocar memória para in_file", 1, __FILE__, __LINE__);
	}
	
	labirinto->out_file = (char *) malloc(7 * sizeof(char));/* strlen("stdout") == 6 (+=1 (do '\0') */;
	
	
	if (labirinto->out_file == NULL)
	{
		log_error("Erro ao alocar memória para out_file", 1, __FILE__, __LINE__);
	}
	
	strcpy(labirinto->in_file, "stdin");
	strcpy(labirinto->out_file, "stdout");
}
/*********************************************/



/**
 * @brief Libera a memória usada pelos arquivos de entrada e saída (in_file e out_file).
 * @param labirinto Ponteiro para a estrutura tLABIRINTO.
*/
void free_io_files(tLABIRINTO *labirinto)
{
	
	free(labirinto->in_file);
	free(labirinto->out_file);
}
/*****************************************/





/**
 * @brief Aloca memória para o vetor que armazenará os passos do jogador.
 * @param jogador Ponteiro para a estrutura tJOGADOR
 * @param tamanho Número de índices do vetor. Se for zero, usa o valor padrão definido na função.
 * @return Retorna um vetor bidimensional para o tipo unsigned int.
*/
unsigned int ** aloca_memoria_passos(tJOGADOR *jogador, int tamanho)
{
	register unsigned int i = 0;
	int posicoes_vetor;
	
	/*------------------------------------------------------------------------------------*
	 *  Aqui há um bug conhecido. Quando se faz realocação de memória, a variável i,      *
	 *  do loop FOR que percorre as linhas do vetor, não passa de um determinado número,  *
	 *  de forma que nem todas as linhas tenham duas colunas para armazer as posições     *
	 *  X e Y, gerando erro de execução.                                                  *
	 *  Por esse motivo, a variável posicoes_vetor terá um valor alto como padrão, a fim  *
	 *  de evitar a necessidade de realocação.                                            *
	**------------------------------------------------------------------------------------*/
	
	/* Se for passado o tamanho 0, usa-se um valor padrão */
	posicoes_vetor = (tamanho == 0) ? 200 : tamanho;
	
	/* Se a capacidade for maior que zero, faz realocação */
	if (jogador->caminho.capacidade > 0)
	{
		
		/* Aloca memória para os índices que conterão os passos do jogador */
		jogador->caminho.passos = (unsigned int **) realloc(jogador->caminho.passos, posicoes_vetor * sizeof(unsigned int *));
	
		if (jogador->caminho.passos == NULL)
		{
			log_error("Falha na alocação de memória para o vetor de passos", 1, __FILE__, __LINE__);
			return NULL;
		}
		
		fprintf(stderr, "Realocadas %d posições de INT *\n", posicoes_vetor);
	
		/* Aloca duas posições para cada índice do vetor, a fim de salvar as posições X e Y de cada passo */
		for (i = 0; i < posicoes_vetor; i++)
		{
			jogador->caminho.passos[i] = (unsigned int *) realloc(jogador->caminho.passos[i], 2 * sizeof(unsigned int));
			
			if (jogador->caminho.passos[i] == NULL)
			{
				log_error("Falha na alocação de memória para o vetor de passos", 1, __FILE__, __LINE__);
				return NULL;
			}
		}
		
		jogador->caminho.capacidade = posicoes_vetor;
		
		return jogador->caminho.passos;
	}
	
	/* Aloca memória para os índices que conterão os passos do jogador */
	jogador->caminho.passos = (unsigned int **) malloc(posicoes_vetor * sizeof(unsigned int *));
	
	if (jogador->caminho.passos == NULL)
	{
		log_error("Falha na alocação de memória para o vetor de passos", 1, __FILE__, __LINE__);
		return NULL;
	}
	
	
	/* Aloca duas posições para cada índice do vetor, a fim de salvar as posições X e Y de cada passo */
	for (i = 0; i < posicoes_vetor; i++)
	{
		jogador->caminho.passos[i] = (unsigned int *) malloc(2 * sizeof(unsigned int));
		
		if (jogador->caminho.passos[i] == NULL)
		{
			log_error("Falha na alocação de memória para o vetor de passos", 1, __FILE__, __LINE__);
			return NULL;
		}
	}
	
	jogador->caminho.capacidade = posicoes_vetor;
	
	return jogador->caminho.passos;
}
/*******************************************************/
