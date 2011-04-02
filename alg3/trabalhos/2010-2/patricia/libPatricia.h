#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define tamPalavra 5
#define tamBuff 256

typedef struct _nodo *nodo;
struct _nodo {
	int bit, key;
	nodo left, right;
};

/** 
* @brief binario para decimal
* 
* @param binario a ser convertido
* 
* @return decimal
*/ 
int binarioParaDecimal (int bin);

/** 
* @brief decimal para binario
* 
* @param decimal a ser convertido
* 
* @return binario
*/ 
unsigned int *apl_dec2bin (int dec);

/** 
* @brief conversao de patricia para patriz
* 
* @param endereco da arvore
* 
* @return endereco da nova arvore
*/ 
nodo apl_patr2patz (nodo p);

/** 
* @brief pega o bit
* 
* @param chave
* @param bit da chave
* 
* @return devolve bit[bit]
*/ 
int apl_digit       (int key, int bit);

/** 
* @brief Limpa buffer de transicao das arvores
* 
* @param nenhum
* 
* @return sem retorno
*/ 
void apl_free_transicaoBuff (void);

/** 
* @brief Imprimir a Arvore Patricia
* 
* @param endereco inicial
* @param bit
* 
* @return sem retorno
*/ 
void patriciaImpressao (nodo p, int bit);

/** 
* @brief Insercao na Patricia
* 
* @param nodo
* @param chave
* 
* @return nodo inserido
*/ 
nodo PatriciaInsere (nodo p, int key);

/** 
* @brief parte da insercao na patricia
* 
* @param endereco inicial
* @param chave
* @param bit
* @param nodo pai
* 
* @return nodo
*/ 
nodo PatriciaInsereNodo (nodo p, int key, int bit, nodo parent);

/** 
* @brief Busca na patricia
* 
* @param endereco inicial
* @param chave
* @param bit
* 
* @return sem retorno
*/ 
void patriciaBusca (nodo p, int key, int bit);

/** 
* @brief Busca na patricia por nodo
* 
* @param endereco inicial
* @param chave
* @param bit
* @param pai do nodo
* 
* @return nodo encontrado
*/ 
nodo patriciaBuscaNodo (nodo p, int key, int bit, nodo parent);

/** 
* @brief acesso a patria em ordem
* 
* @param endereco inicial
* @param bit
* 
* @return sem retorno
*/ 
void patriciaEmOrdem (nodo p, int bit);

/** 
* @brief avaliacao de custo da patricia
* 
* @param endereco inicial
* @param bit
* 
* @return sem retorno
*/ 
void patriciaAnalisaCusto (nodo p, int bit);


/** 
* @brief transforma Patriz em Patricia
* 
* @param endereco inicial
* 
* @return endereco da nova arv
*/
nodo transformaPatrizEmPatricia (nodo p);

/** 
* @brief Cria nodo
* 
* @param chave
* @param bit
* 
* @return nodo criado
*/ 
nodo criaNodo (int key, int bit);

/**
 * @var transicaoBuff  Variavel usada nas transformacoes entre Patricia e Patriz
 *
 */
extern int *transicaoBuff;

/**
 * @var countAux1
 *      countAux2
 * 		Devido a transformacoes de arvores, servem como índices e contadores
 * 		para o buffer [de transicao] entre as arvores  
 */
extern int countAux1, countAux2;
