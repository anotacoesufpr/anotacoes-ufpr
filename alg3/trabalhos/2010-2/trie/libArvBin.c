#include <stdio.h>
#include <stdlib.h>
#include "libArvBin.h"

Apontador criaNo( Registro r, Apontador esq, Apontador dir ){
  Apontador p;
  
  p = (Apontador) malloc( sizeof(No) );
  p->Reg = r; 
  p->Esq = esq; 
  p->Dir = dir;
  p->AltEsq = p->AltDir = 0;
  return p;
}

	/* inicializa a arvore */
void Inicializa(Apontador *raiz){
  Registro r;

  r.Chave = 0;
  nodoNull = criaNo( r, (Apontador)0, (Apontador)0 );
  *raiz = nodoNull;
  return;
} 
    /* imprime a arvore */
void imprimeArv(Apontador p){
  int bal;

  if( p == nodoNull )
    printf("()");
  else{
    printf("(");
    imprimeArv( p->Esq );
    bal = p->AltEsq - p->AltDir;
    printf("% ld[%d] ", p->Reg.Chave, bal);
    imprimeArv( p->Dir );
    printf(")");
  }
  return;
}
  
	/* pesquisa por um no (padrao do trabalho)*/
Apontador Pesquisa(TipoChave k, Apontador p){
  if (p == nodoNull || k == p->Reg.Chave)
    return p;
  if (k < p->Reg.Chave) 
    return Pesquisa(k, p->Esq);
  else 
    return Pesquisa(k, p->Dir);
} 

/*
 * Pesquisa por um no (funcao nova)
 *
 * foi necessaria uma funcao nova porque:
 * 1) Foi solicitado a nao alteracao das funcoes padroes
 * 2) Embora pedido para utilizar as funcoes padroes sempre
 * que possivel, neste caso não foi devido ao fato de termos que
 * imprimir todas as chaves pelas quais passamos, conforme a
 * especificacao do trabalho
*/
Apontador Busca(TipoChave k, Apontador p){
  if (p == NULL ){
		return p;
	}
	else {
		if (k == p->Reg.Chave){
    	printf("%ld", p->Reg.Chave);
			return p;
		}
		else {
			printf("%ld", p->Reg.Chave);
		}
	}
	if (k < p->Reg.Chave) {
    if (esquerda(p) != NULL)
    {
      printf(",");
      return Busca(k, esquerda(p));
    }
	}
  else {
    if (direita(p) != NULL) {
      printf(",");      
      return Busca(k, direita(p));
    }
	}
}

/* Apontador esquerdo */
Apontador esquerda( Apontador p ){
  if (p != NULL)
    return p->Esq;
  return NULL;
}

/* Apontador direito */
Apontador direita( Apontador p ){
  if (p != NULL)
    return p->Dir;
  return NULL;
}

/*antiga rotacao*/
void rotacaoDireita( Apontador *p ){
  Apontador fe, netoDir;

  fe = (*p)->Esq;
  netoDir = fe->Dir;
  (*p)->Esq = netoDir;
  fe->Dir = *p;
  *p = fe;
  return;
}

/*antiga rotacao*/
void rotacaoEsquerda( Apontador *p ){
  Apontador fd, netoEsq;

  fd = (*p)->Dir;
  netoEsq = fd->Esq;
  (*p)->Dir = netoEsq;
  fd->Esq = *p;
  *p = fd;
  return;
}

/*nova rotacao*/
void RotEsqComAlt( Apontador *p )
{
}

/*nova rotacao*/
void RotDirComAlt( Apontador *p )
{
}


/* insercao de um no na raiz */
int Insere(Registro r, Apontador *raiz){
	Registro novoNo;
	r.Chave = 0;

  /*if (raiz == NULL) {
  
  nodoNull = criaNo( r, (Apontador)0, (Apontador)0 );
  *raiz = nodoNull;
  return;
    }
    if (v < h->chave) { 
       h->l = insertT(h->l, v); 
       h = rotR(h); 
    } 
    else { 
       h->r = insertT(h->r, v); 
       h = rotL(h); 
    }
    return h;*/

} 


/* Balanceamento de no */
void balanceia( Apontador *p ){
  Apontador  pai, f, n;

  pai = *p;
  if( pai->balanceamento < 0 ){   /* esta' desbalanceado para a direita */
    f = direita( *p ); 
    if( f->balanceamento < 0){
      RotEsqComAlt( p );
      pai->balanceamento = 0;
      f->balanceamento = 0;
    } else{
      n = esquerda( f );
      RotDirComAlt( &(*p)->Dir );
      RotEsqComAlt( p );
      if( n->balanceamento == 0 ){
	pai->balanceamento = 0;
	f->balanceamento = 0;
      }else if( n->balanceamento > 0 ){
	pai->balanceamento = 0;
	f->balanceamento = -1;
      }else{
	pai->balanceamento = 1;
	f->balanceamento = 0;
      }
      n->balanceamento = 0;
    }
  }
  else{                            /* esta' desbalanceado para a esquerda */
    f = esquerda( *p ); 
    if( f->balanceamento > 0){
      RotDirComAlt( p );
      pai->balanceamento = 0;
      f->balanceamento = 0;
    } else{
      n = direita( f );
      RotEsqComAlt( &(*p)->Esq );
      RotDirComAlt( p );
      if( n->balanceamento == 0 ){
	pai->balanceamento = 0;
	f->balanceamento = 0;
      }else if( n->balanceamento > 0 ){
	pai->balanceamento = -1;
	f->balanceamento = 0;
      }else{
	pai->balanceamento = 0;
	f->balanceamento = 1;
      }
      n->balanceamento = 0;
    }
  }
  return;
}
