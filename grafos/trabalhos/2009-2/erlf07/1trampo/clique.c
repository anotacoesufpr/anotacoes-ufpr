#include "clique.h"

Pgin*
pgin_info(void) {
    Pgin *pgin;
    pgin = (Pgin *) malloc(2 * sizeof(Pgin));

    /* Inclui clique como primeiro algoritmo do plugin */
    pgin[0].type = PGIN_TEST_ALG;
    pgin[0].label = "Clique";
    pgin[0].name = "clique";
    pgin[0].flags = 0;

    /* Indica o final da lista de algoritmos */
    pgin[1].type = PGIN_LIST_END;
    pgin[1].label = 0;
    pgin[1].name = 0;
    pgin[1].flags = 0;

    return pgin;
}

/** Colore todos os vertices com a cor 'color'*/
int 
paintAllPoints(Graph *G, int color) {
    int i;
    for (i=0; i<G->size; i++)
        G->vertex[i].color = color;
    return 1;
}

/** Colore o vertice da posicao 'pos' com a cor 'color'*/
int 
paintPoint(Graph *G, int pos, int color) {
    G->vertex[pos].color = color;
    return 1;
}

/** Colore todas as arestas com a cor 'color'*/
int 
paintAllEdges(Graph *G, int color) {
    int i,j;
    for (i=0; i<G->nedges; i++)
        for (j=0; j<G->nedges; j++)
            G->prop[i][j].color = color;
    return 1;
}

/** Colore a aresta da posicao 'x,y' com a cor 'color'*/
void
paintEdge(Graph *G, int x, int y, int color) {
    G->prop[x][y].color = color;
}

void
paintMaior(Graph *G, Mclique maior, int color) {
    int k,l;
    for (k=maior.lin; k<maior.tam; k++)
        for (l=maior.col_inicio; l<maior.col_fim; l++) 
            G->prop[k][l].color = color;
};

void
printMatrizAdj(Graph *G) {
    int k,l;
    for (k=0; k<G->size; k++) {
        for (l=0; l<G->size; l++) 
            printf("%d",G->edge[k][l]);
        printf("\n");
    }
}

int
kClique(Lista *candidatos, Graph *G, int grau) {
   int i,j;
   j=0;

   for(i=0; i<G->size; i++) {
      if (G->vertex[i].degree >= grau) {
           candidatos->vet[j++] = i;
      //printf ("Dentro de kClique: grau (%d) elemento(%d)\n",grau,candidatos->vet[j-1]);
      }
   }
   //printf ("Encontrei %d elemento(s) de grau >= %d\n",j,grau);
   candidatos->n_elem = j;

   //printf ("Tamanho da lista depois do for: %d\n",l->n_elem);
   /* uma K-clique tem K vertices, e o grau de cada vertice eh k-1 */
   /* alem disso j fica igual o numero esperado de elementos, pois j comeca
    * com zero e grau comeca com 1 */
   //printf("kClique return (%d >= %d)?1:0 = %d\n",j,grau,(j>=grau)?1:0);
   return (j>=grau) ? 1 : 0;

}

int vizin (Lista *eleitos, int v, Lista *candidatos,Graph *G) {
	int i;
	printf("Eleitos tem %d elementos\n",eleitos->n_elem);
	for (i=0; i<eleitos->n_elem; i++)
		if (!G->edge[v][eleitos->vet[i]])
			return 0;
	return 1;
}

int
conexos(Lista *candidatos, Lista *eleitos, int grau, Graph *G) {
	int i,ii,j;
	int cont=0;

	printf ("Dentro de conexos, procuro uma %d-clique \n",grau+1);
	printf("Candidatos = %d\n",candidatos->n_elem);
	printf("Eleitos = %d\n",eleitos->n_elem);

	/* vertices de grau 1 formam uma 2-clique */
	if ((grau < 1) || candidatos->n_elem < (grau+1))
		return 0;


	/* Percorrendo todos os candidatos */
	for (i=0; i<candidatos->n_elem; i++) {

		/* Seleciona um elemento para o conjunto */
		eleitos->vet[i] = candidatos->vet[i];
		eleitos->n_elem++;
		/* contando um elemento na lista dos eleitos */
		cont = 1;

		/* Verificando a vizinhanca entre eles */
		for(j=0; j<candidatos->n_elem; j++) {
			printf ("Entrando em vizin\n");
			if (vizin(eleitos,candidatos->vet[j],candidatos,G)) {
//			if (i!=j && G->edge[eleitos->vet[i]][candidatos->vet[j]]) {
				printf ("Sai de vizin\n");
				eleitos->vet[i+cont] = candidatos->vet[j];
				eleitos->n_elem += 1;
				cont += 1;
				if (cont == grau+1 ){
					printf ("conexos retornando um\n");
					return 1;
				}
			}
		} /* 2o for */
	}/* 1o for */

	/* Se nao encontrou, zera os eleitos */
	for (j=0; j<eleitos->n_elem; j++)
		eleitos->vet[j] = -1;
	eleitos->n_elem = 0;
	cont = 0;

	printf ("conexos retornando zero\n");
	return 0;
}


void
pinta (Lista *l, int tam, Graph *G, int color) {
   int i,j;
   /* pintando vertices */
   printf("Pinta: %d-clique - %d vertices\n",tam,l->n_elem);
   for(i=0; i<tam; i++) {
       printf("pintando o vertice: %d\n", l->vet[i]);
       paintPoint(G,l->vet[i],color);
    }
   /* pintando arestas */
   for(i=0; i<tam; i++)
      for(j=i+1; j<tam; j++) {
           if (G->edge[l->vet[i]][l->vet[j]])
            printf("pintando a aresta: %d,%d\n", l->vet[i],l->vet[j]);
            G->prop[l->vet[i]][l->vet[j]].color = color;
      }
}

/** */
void
Edges(Graph *G, int color) {
    int i,grau;
    Lista *candidatos, *eleitos;

	/* Alocando os candidatos */
	candidatos = (Lista*)malloc(sizeof(Lista));
	candidatos->n_elem = 0;
    candidatos->vet = (int*)malloc(sizeof(int) * G->size);
	for (i=0; i<G->size; i++)
		candidatos->vet[i]=-1;

	/* Alocando os eleitos */
	eleitos = (Lista*)malloc(sizeof(Lista));
	eleitos->n_elem = 0;
    eleitos->vet = (int*)malloc(sizeof(int) * G->size);
	for (i=0; i<G->size; i++)
		eleitos->vet[i]=-1;

    printMatrizAdj(G);

    for (grau=G->size-1; grau>0; grau--) {

        if (kClique(candidatos,G,grau) && \
			conexos(candidatos,eleitos,grau,G)) {

            //printf (" grau %d pintando...\n",grau);
            pinta(eleitos,grau+1,G,color);
			break;
        }
		else {
			for (i=0; i<eleitos->n_elem; i++)
				eleitos->vet[i]=0;
			eleitos->n_elem = 0;
		}
    }

}


/** Esta funcao e' a funcao principal do plugin */
int
clique(Graph *G, char *mess) {
    sprintf(mess, "Clique");
    Edges(G,BLUE);
    return 1;
}

