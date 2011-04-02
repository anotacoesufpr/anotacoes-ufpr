#ifndef _ARVBIN
#define _ARVBIN

#define OK    1
#define ERRO -1

typedef long TipoChave;
typedef struct Registro {
  TipoChave Chave;
  /* outros componentes */
} Registro;

typedef struct No *Apontador;

typedef struct No {
  Registro Reg;
  Apontador Esq, Dir;    /* filhos esquerdo e direito do no'*/
  int AltEsq, AltDir;    /* altura das subarvores esq. e direita */
	int balanceamento;
} No;

static Apontador nodoNull;

Apontador criaNo( Registro r, Apontador esq, Apontador dir );
void Inicializa(Apontador *raiz);
void imprimeArv(Apontador p);
Apontador Pesquisa(TipoChave k, Apontador p);
Apontador Busca(TipoChave k, Apontador p);
Apontador esquerda( Apontador p );
Apontador direita( Apontador p );
void rotacaoDireita( Apontador *p );
void rotacaoEsquerda( Apontador *p );
void RotEsqComAlt( Apontador *p );
void RotDirComAlt( Apontador *p );
int Insere(Registro r, Apontador *raiz);
void balanceia( Apontador *p );



#endif
