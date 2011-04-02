#include <stdio.h>
#include <stdlib.h>
#include "pgin.h"
#include "graph.h"

#define GREEN 1
#define BLUE 2 
#define YELLOW 3 
#define CYAN 4 

typedef struct {
    int lin;
    int col_inicio;
    int col_fim;
    int tam;
} Mclique;
Pgin *pgin_info(void);

typedef struct {
	int n_elem;
	int *vet;
} Lista; /* lista que contem o seu tamanho */

int ashf03_erlf07_las05(Graph *G, char *mess);

