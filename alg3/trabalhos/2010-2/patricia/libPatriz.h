#include "libPatricia.h"

/** 
* @brief Impressao da Arvore Patriz
* 
* @param endereco da arvore
* 
* @return sem retorno
*/ 
void patrizImpressao (nodo p);

/** 
* @brief Insercao na Arvore Patriz
* 
* @param chave
* @param endereco inicial
* 
* @return nodo inserido
*/ 
nodo patrizInsere (nodo p, int key);

/** 
* @brief Insere nodo na Arvore Patriz
* 
* @param endereco inicial
* @param chave
* @param bit da chave
* @param nodo pai
* 
* @return nodo inserido
*/ 
nodo patrizInsereNodo (nodo p, int key, int bit, nodo parent);

/** 
* @brief Transforma Patricia em Patriz
* 
* @param endereço da Arvore
* 
* @return  endereco da arvore
*/ 
nodo transformaPatriciaEmPatriz (nodo p);

/** 
* @brief Busca na Arvore Patriz
* 
* @param endereco da arvore
* @param chave a ser buscada
* @param bit da chave
* 
* @return sem retorno
*/ 
void buscaPatriz (nodo p, int key, int bit);

/** 
* @brief Busca por um nodo
* 
* @param endereco inicial
* @param chave
* @param bit da chave
* @param nodo pai
* 
* @return nodo buscado
*/ 
nodo buscaPatrizNodo (nodo p, int key, int bit, nodo parent);

/** 
* @brief Custo da Arvore atualmente carregada
* 
* @param endereco da Arvore
* 
* @return sem retorno
*/ 
void patrizAnalisaCusto (nodo p);
