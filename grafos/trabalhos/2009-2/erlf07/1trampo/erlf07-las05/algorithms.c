/*
 *  grafo - graph editor
 *  Copyright (c) 2003-2008
 *      Murilo Vicente Goncalves da Silva <murilo@pet.inf.ufpr.br>
 *      Oliver Matias van Kaick <oliver@pet.inf.ufpr.br>
 *      Ulisses Cordeiro Pereira <ulisses@cordeiropereira.com.br>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details (file COPYING).
 */ 


/* **************** */
/* * algorithms.c * */
/* **************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"
#include "graph.h"
#include "geometry.h"
#include "list.h"
#include "draw.h"
#include "iface/iface.h"
#include "step.h"

/* Draw structure: draw.c */
extern DrawStruct DS;

/* Step structure: step.c */
extern Step S[MAX_STEPS];

/* Interface: iface.c */
extern Iface iface;


/* Complement */
int Complement(Graph *G, char *mess){
int i,j;

    if (G->size < 1) {
        sprintf(mess, "%s", "Empty graph!");
        return 1;
    }

    for (i=0; i<G->size; i++) {
        for (j=0; j<G->size; j++) {
            if (i!=j) {
                if (G->edge[i][j]) {
                    G->edge[i][j] = 0;
                } else {
                    G->edge[i][j] = 1;
                }
            }
        }
    }


    return 1;
}

/* Search in a graph in a depth first manner. The arc_edges list will
 * hold the tree edges and the verts list will holds all the verts
 * reachable from x in the order of the depht first search */
int DepthSearch(Graph *G, char *mess, int x, List *arc_edges, List *verts){
SEdge *E;
Node N;
Stack stk;
int i, v, parent;
SVertex *V;
int first;

    if (G->size < 1) {
        sprintf(mess, "%s", "Empty graph!");
        return 1;
    }

    V = (SVertex *) malloc (sizeof(SVertex));
    E = (SEdge *) malloc (sizeof(SEdge));
    ClearMarkedVerts(G);
    InitStack(&stk);

    // Push the parent of the first vertex
    parent = -1; // the root do not have parent
    N = MakeNode(&parent, sizeof(int));
    PushNode(&stk, N);
    // Push the start vertex
    v = x; // start vertex
    N = MakeNode(&v, sizeof(int));
    PushNode(&stk, N);

    while ((N = PopNode(&stk)) != NULL) {
		/* v = poped node; 
		 * mark v as visited.*/
        memcpy(&v, N->data, sizeof(int));
        DestroyNode(N);
        first = 1;
        
        if (G->vertex[v].mark == 1) {
            continue;
        }
        
        /* Put v on the list of visited vertex */
        *V = v;
        N = MakeNode(V, sizeof(SVertex));
        InsertNode(verts, N); 
        G->vertex[v].mark = 1;

        /* pop the parent of the node */
        N = PopNode(&stk);
        memcpy(&parent, N->data, sizeof(int));
        DestroyNode(N);
			
        /* I know that this is not efficient... */
        if (parent !=-1) {
            E->u = parent;
            E->v = v;
            N = MakeNode(E, sizeof(SEdge));
            InsertNode(arc_edges, N);
            free(E);
            E = (SEdge *) malloc (sizeof(SEdge));
        }
        
        parent = v;
        for (i=0; i < G->size; i++) {
            if ((G->edge[v][i]) && (G->vertex[i].mark == 0)) {
                /* Push the parent */
                N = MakeNode(&parent, sizeof(int));
                PushNode(&stk, N);
                /* Push vertices */
                N = MakeNode(&i, sizeof(int));
                PushNode(&stk, N);
            }
        }
    }

    free(V);
    free(E);
    ClearMarkedVerts(G);
    sprintf(mess,"%s","Depth First Search");
    return 1;

}

int Step_DepthSearch(Graph *G, char *mess, int x, List *arc_edges, List *verts){
SEdge *E;
Node N;
Stack stk;
int i, v, parent;
SVertex *V;
int first;

    if (G->size < 1) {
        sprintf(mess, "%s", "Empty graph!");
        return 1;
    }

    V = (SVertex *) malloc (sizeof(SVertex));
    E = (SEdge *) malloc (sizeof(SEdge));
    ClearMarkedVerts(G);
    InitStack(&stk);

    /* Add first step */
    AddStep(G, arc_edges, verts);
        
    // Push the parent of the first vertex
    parent = -1; // the root do not have parent
    N = MakeNode(&parent, sizeof(int));
    PushNode(&stk, N);
    // Push the start vertex
    v = x; // start vertex
    N = MakeNode(&v, sizeof(int));
    PushNode(&stk, N);

    while ((N = PopNode(&stk)) != NULL) {
		/* v = poped node; 
		 * mark v as visited.*/
        memcpy(&v, N->data, sizeof(int));
        DestroyNode(N);
        first = 1;
        
        if (G->vertex[v].mark == 1) {
            continue;
        }
        
        /* Put v on the list of visited vertex */
        *V = v;
        N = MakeNode(V, sizeof(SVertex));
        InsertNode(verts, N); 
        G->vertex[v].mark = 1;

        /* pop the parent of the node */
        N = PopNode(&stk);
        memcpy(&parent, N->data, sizeof(int));
        DestroyNode(N);
        
        /* I know that this is not efficient... */
        if (parent !=-1) {
            E->u = parent;
            E->v = v;
            N = MakeNode(E, sizeof(SEdge));
            InsertNode(arc_edges, N);
            free(E);
            E = (SEdge *) malloc (sizeof(SEdge));
        }
       
        parent = v;
        for (i=0; i < G->size; i++) {
            if ((G->edge[v][i]) && (G->vertex[i].mark == 0)) {
                /* Push the parent */
                N = MakeNode(&parent, sizeof(int));
                PushNode(&stk, N);
                /* Push vertices */
                N = MakeNode(&i, sizeof(int));
                PushNode(&stk, N);
            }
        }
        /* Add new step */
        AddStep(G, arc_edges, verts);
    }

    free(V);
    free(E);
    ClearMarkedVerts(G);
    sprintf(mess,"%s","Depth First Search");
    return 1;
}

/* SpanningTree */
int SpanningTree(Graph *G, char *mess, List *arc_edges, List *verts) {

    if (G->size < 1) {
        sprintf(mess,"%s","Empty graph!");
        return 1;
    } 
   
	DepthSearch(G, mess, 0, arc_edges, verts);
   
    /* I only want the edges */
    CleanList(verts);

    sprintf(mess,"%s","Sp. Tree");
    return 1;
}



/* 
 * Testa se um grafo e' cordal usando algoritmo proposto por
 * Fulkerson e Rose, descrito em Gavril [72]. A ideia e' verificar 
 * se ha uma R-orientacao no grafo.
 */
int Chordal(Graph *G, char *mess) {
Graph H;

    if (G->size < 1) {
        sprintf(mess,"%s","Empty graph!");
        return 1;
    }

    /* Aloca H e copia G nele */
    //H = (Graph *) malloc (sizeof (Graph));
    //memcpy(H, G, sizeof(Graph));
    CopyGraph(&H,G);

    /* Caso existam sumidouros, eles sao eliminados 
     * ate' que apenas sobre 1 vertice em H */
    while ((H.size > 1) && (Delete_Sink(&H) != -1 )); 
    
    /* Considerar <=, pois o grafo pode vir vazio */
    if (H.size <= 1) {
        sprintf(mess,"%s","Chordal");
        return 1;
    } else {
        sprintf(mess,"%s","Not Chordal");
        return 0;
    }
	
}


int Line(Graph *G, char *mess) {
Graph *H;
int **aux;
int i,j;
int maxedges;   

    if (G->size < 1) {
        sprintf(mess,"%s","Empty graph!");
        return 1;
    }


    maxedges = G->size * (G->size - 1);
    aux = (int **) malloc(maxedges * sizeof(int *));
    for (i = 0; i < maxedges; i++) {
        aux[i] = (int *) malloc(2 * sizeof(int));
    }

    /* Allocs and Initializes the graph H */
    H = (Graph *) malloc (sizeof (Graph));
    AllocGraph(H);
	InitGraph(H, GRAPH);

    /* Creates the vertices */
    for (i=0; i<G->size; i++) {
        for (j=i; j<G->size; j++) {
            if (G->edge[i][j]) {
                AddPoint(H, 100, 100);
                aux[H->size-1][0] = i;
                aux[H->size-1][1] = j;
            }
        }
    }
    /* For each edge */ 
    for (i=0; i<H->size - 1; i++) {
        /* Look for incident edges */
        for (j=i+1; j<H->size; j++) {
            if (
                ((aux[j][0] == aux[i][0]) || (aux[j][1] == aux[i][0])) ||
                ((aux[j][0] == aux[i][1]) || (aux[j][1] == aux[i][1])) 
               ) {
                AddEdge(H, i, j);
            }
        }
    }

    memcpy(G, H, sizeof(Graph));
   
    sprintf(mess,"%s","The line graph!");
    return 1;
}


/* 
 * Removes the sink and returns its position.
 * The algorithm treat the graph as an undirected one. The
 * sink is the vertex such that all its adjacents vertex
 * are a clique.
 * If there are no sink, it is returned -1 
 */
int Delete_Sink(Graph *G) {
int vertice[MAX_POINTS]; /* Holds the adj. of a given vertex */
int NAdj; /* Number of vertex in vertice[]  */
int fail; /* 1 if the set of vertex in vertice[] are not a clique */
int found = 0; /* 1 when a sink is found */
int i,j,k;

    /* Para cada vertice do grafo */
    i = 0;
    while ((!found) && (i<G->size)) {
        /* Guarda em vertice[] os k vertices adj. ao i-esimo vertice */
        NAdj=0;
        for (j=0; j<G->size; j++) {
            if (G->edge[i][j]) {
                vertice[NAdj] = j;
                NAdj++;
            }
        }
        /* Verifica se esses k adjacentes sao uma clique */
        fail = 0;
        for (j=0; j<NAdj-1; j++) {
            for (k=j+1; k<NAdj; k++) {
                if(!G->edge[vertice[j]][vertice[k]]) {
                    fail=1;
                    goto FASTSKIP;
                }
            }
        }
        FASTSKIP:

        /* Caso os vertices em vertice[] sejam uma clique */
        if (!fail) {
            found = 1;
        }

        i++;
    }

    /* Retira o vertice e o retorna */
    if (found) {
        RemovePoint(G, i-1);
        return (i-1);
    } else {
        return -1;
    }

}


#if 0
int GetNextColor(PalOpt opt) {
static int color=0;

    if (opt == RESET) {
        color = 0;
    } else {
        color++;
    }
    return color;
}
#endif


/* 
 *  F. Gavril [72],
 * "ALGORITHMS FOR MINIMUM COLORING, MAXIMUM CLIQUE, MINIMUM
 *  COVERING BY CLIQUES, AND MAXIMUM INDEPENDENT SET OF A 
 *  CHORDAL GRAPH",
 *  SIAM J. Comput., Vol. 1, No. 2, June 1972.
 */

/* ******* */
/* * End * */
/* ******* */

