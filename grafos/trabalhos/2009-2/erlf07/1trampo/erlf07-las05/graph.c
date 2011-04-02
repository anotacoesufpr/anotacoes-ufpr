/*
 *  grafo - graph editor
 *  Copyright (c) 2003
 *      Murilo Vicente Goncalves da Silva <murilo@pet.inf.ufpr.br>
 *      Oliver Matias van Kaick <oliver@pet.inf.ufpr.br>
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


/* *********** */
/* * graph.c * */
/* *********** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "geometry.h"
#include "color.h"


/* Color definitions: color.c */
extern Color_def color_def[];

/* Error string */
char graph_error[MAXSTRSIZE];


/* Alloc memory for the graph */
void AllocGraph(Graph *G){
int i;

    /* Set allocated size */
    G->allocated_size = MAX_POINTS;
   
    /* Alloc vertices array */
    G->vertex = (Vertex *) malloc(G->allocated_size * sizeof(Vertex));
    if (!G->vertex){
        sprintf(graph_error, "Error allocating vertex array");
        return ;
    }
    
    /* Alloc edge array */
    G->edge = (Edge **) malloc(G->allocated_size * sizeof(Edge *));
    if (!G->edge){
        sprintf(graph_error, "Error allocating edge array");
        return ;
    }
    G->edge[0] = (Edge *) malloc(G->allocated_size *
            G->allocated_size * sizeof(Edge));
    if (!G->edge[0]){
        sprintf(graph_error, "Error allocating edge data");
        return ;
    }
    for (i = 1; i < G->allocated_size; i++){
        G->edge[i] = G->edge[0] + (G->allocated_size * i);
    }
    
    /* Alloc edge properties array */
    G->prop = (Edge_prop **) malloc(G->allocated_size *
            sizeof(Edge_prop *));
    if (!G->prop){
        sprintf(graph_error, "Error allocating edge properties array");
        return ;
    }
    G->prop[0] = (Edge_prop *) malloc(G->allocated_size *
            G->allocated_size * sizeof(Edge_prop));
    if (!G->prop[0]){
        sprintf(graph_error, "Error allocating edge properties data");
        return ;
    }
    for (i = 1; i < G->allocated_size; i++){
        G->prop[i] = G->prop[0] + (G->allocated_size * i);
    }

}


/* Increase graph's allocated memory */
void ReAllocGraph(Graph *G, int size){
int i, j;
Graph temp;

    /* Check if new size is valid */
    if (size <= G->allocated_size){
        sprintf(graph_error, "Size to realloc too small");
        return ;
    }
   
    /* Alloc first temp, so that the graph is not already changed */
    /* Alloc vertex array */
    temp.vertex = (Vertex *) malloc(size * sizeof(Vertex));
    if (!temp.vertex){
        sprintf(graph_error, "Error allocating vertex array");
        return ;
    }
    
    /* Alloc edge array */
    temp.edge = (Edge **) malloc(size * sizeof(Edge *));
    if (!temp.edge){
        free(temp.vertex);
        sprintf(graph_error, "Error allocating edge array");
        return ;
    }
    temp.edge[0] = (Edge *) malloc(size * size * sizeof(Edge));
    if (!temp.edge[0]){
        free(temp.vertex);
        free(temp.edge);
        sprintf(graph_error, "Error allocating edge data");
        return ;
    }
    for (i = 1; i < size; i++){
        temp.edge[i] = temp.edge[0] + (size * i);
    }
    
    /* Alloc edge properties array */
    temp.prop = (Edge_prop **) malloc(size * sizeof(Edge_prop *));
    if (!temp.prop){
        free(temp.vertex);
        free(temp.edge[0]);
        free(temp.edge);
        sprintf(graph_error, "Error allocating edge properties array");
        return ;
    }
    temp.prop[0] = (Edge_prop *) malloc(size * size * sizeof(Edge_prop));
    if (!temp.prop[0]){
        free(temp.vertex);
        free(temp.edge[0]);
        free(temp.edge);
        free(temp.prop);
        sprintf(graph_error, "Error allocating edge properties data");
        return ;
    }
    for (i = 1; i < size; i++){
        temp.prop[i] = temp.prop[0] + (size * i);
    }

    /* Reset temp */
    memset(temp.vertex, 0, sizeof(Vertex) * size);
    memset(temp.edge[0], 0, sizeof(Edge) * size * size);
    memset(temp.prop[0], 0, sizeof(Edge_prop) * size * size);

    /* Copy graph data */
    for (i = 0; i < G->size; i++){
        memcpy(&(temp.vertex[i]), &(G->vertex[i]), sizeof(Vertex));
    }
    for (i = 0; i < G->size; i++){
        for (j = 0; j < G->size; j++){
            memcpy(&(temp.edge[i][j]), &(G->edge[i][j]), sizeof(Edge));
            memcpy(&(temp.prop[i][j]), &(G->prop[i][j]),
                    sizeof(Edge_prop));
        }
    }

    /* Free old graph data */
    free(G->vertex);
    free(G->edge[0]);
    free(G->edge);
    free(G->prop[0]);
    free(G->prop);

    /* Set new pointers in graph */
    G->vertex = temp.vertex;
    G->edge = temp.edge;
    G->prop = temp.prop;
    G->allocated_size = size;
}


/* Free graph memory */
void FreeGraph(Graph *G){

    free(G->vertex);
    free(G->edge[0]);
    free(G->edge);
    free(G->prop[0]);
    free(G->prop);
    G->allocated_size = 0;
}


/* Reset graph */
void InitGraph(Graph *G, GraphType type){

    G->size = 0;
    G->nedges = 0;
    G->narcs = 0;
    G->ncomp = -1;
    G->ncolor = -1;
    G->encolor = -1;
    G->type = type;
    G->nextid = 0;

    memset(G->vertex, 0, sizeof(Vertex) * G->allocated_size);
    memset(G->edge[0], 0, sizeof(Edge) *
            G->allocated_size * G->allocated_size);
    memset(G->prop[0], 0, sizeof(Edge_prop) *
            G->allocated_size * G->allocated_size);
}

/* Takes a not allocated graph H and copy G into it */
void CopyGraph(Graph *H, Graph *G) {
int i,j;

	AllocGraph(H);
    ReAllocGraph(H, G->allocated_size);

    /* Copy graph data */
    H->type = G->type;
    H->size = G->size;
    H->nextid = G->nextid;
    H->nedges = G->nedges;
    H->narcs = G->narcs;
    H->ncomp = G->ncomp;
    H->ncolor = G->ncolor;
    H->encolor = G->encolor;
	
    for (i = 0; i < G->size; i++){
        memcpy(&(H->vertex[i]), &(G->vertex[i]), sizeof(Vertex));
    }
    for (i = 0; i < G->size; i++){
        for (j = 0; j < G->size; j++){
            memcpy(&(H->edge[i][j]), &(G->edge[i][j]), sizeof(Edge));
				memcpy(&(H->prop[i][j]), &(G->prop[i][j]),
                    sizeof(Edge_prop));
        }
    }
}


/* Reset graph's edges */
void InitEdges(Graph *G){

    G->nedges = 0;
    G->encolor = 0;

    memset(G->edge[0], 0, sizeof(Edge) *
            G->allocated_size * G->allocated_size);
    memset(G->prop[0], 0, sizeof(Edge_prop) *
            G->allocated_size * G->allocated_size);
}


/* Add a vertex */
void AddPoint(Graph *G, float x, float y) {

    if (G->size + 1 > G->allocated_size) {
        ReAllocGraph(G, G->allocated_size * 2);
    }

    G->vertex[G->size].id = G->nextid; 
    G->vertex[G->size].degree = 0;
    G->vertex[G->size].indegree = 0;
    G->vertex[G->size].outdegree = 0;
    G->vertex[G->size].weight = 0;
    G->vertex[G->size].label = NULL;
    G->vertex[G->size].x = x;
    G->vertex[G->size].y = y;
    G->vertex[G->size].color = RED; // default color
    G->vertex[G->size].concomp = -1;
    G->vertex[G->size].mark = 0; // not marked
   
    G->size++;
    G->nextid++;
}


void RemovePoint(Graph *G, int p) {
int i,j,k;

    /* Change vertex degree */
    for (i = 0; i < G->size; i++) {
		if (G->type == GRAPH) {
			if (G->edge[p][i]) {
				if (G->prop[p][i].label)
					free(G->prop[p][i].label);
				if (G->prop[i][p].label)
					free(G->prop[i][p].label);
			    G->nedges--;
			    G->vertex[i].degree--;
			}
		} else if (G->type == DIGRAPH){
			if (G->edge[p][i]) {
				if (G->prop[p][i].label)
					free(G->prop[p][i].label);
				G->narcs--;
				G->vertex[i].indegree--;
			} 
			if (G->edge[i][p]) {
				if (G->prop[i][p].label)
					free(G->prop[i][p].label);
				G->narcs--;
				G->vertex[i].outdegree--;
		    }
		}
    }
    
    /* Remove the vertex */
    for (i = p; i < G->size-1; i++) {
        G->vertex[i].x = G->vertex[i+1].x;
        G->vertex[i].y = G->vertex[i+1].y;
        G->vertex[i].color = G->vertex[i+1].color;
        G->vertex[i].weight = G->vertex[i+1].weight;
        G->vertex[i].label = G->vertex[i+1].label;
        G->vertex[i].concomp = G->vertex[i+1].concomp;
        G->vertex[i].mark = G->vertex[i+1].mark;
        G->vertex[i].id = G->vertex[i+1].id;
        G->vertex[i].degree = G->vertex[i+1].degree;
        G->vertex[i].indegree = G->vertex[i+1].indegree;
        G->vertex[i].outdegree = G->vertex[i+1].outdegree;
    }
    G->vertex[G->size-1].x = 0.0; 
    G->vertex[G->size-1].y = 0.0; 
    G->vertex[G->size-1].degree = 0;
    G->vertex[G->size-1].indegree = 0;
    G->vertex[G->size-1].outdegree = 0;
    G->vertex[G->size-1].weight = 0;
    G->vertex[G->size-1].label = NULL;
    G->vertex[G->size-1].color = RED; // default color
    G->vertex[G->size-1].concomp = -1;
    G->vertex[G->size-1].mark = 0; // not marked


	
    /* Remove edges */
    for (i = 0; i < G->size; i++) {
        for (j = p; j < G->size-1; j++) {
            /* aresta */
            G->edge[i][j] = G->edge[i][j+1];
            G->prop[i][j].weight = G->prop[i][j+1].weight;
            G->prop[i][j].label = G->prop[i][j+1].label;
            G->prop[i][j].color = G->prop[i][j+1].color;
            G->prop[i][j].mark = G->prop[i][j+1].mark;
            /* pontos de controle */
            for (k = 0; k < 4; k++) {
                G->prop[i][j].ctrlpoints[k][X] =
                        G->prop[i][j+1].ctrlpoints[k][X];
            }
            for (k = 0; k < 4; k++) {
                G->prop[i][j].ctrlpoints[k][Y] =
                        G->prop[i][j+1].ctrlpoints[k][Y];
            }
           
        }
    }
    for (i = 0; i < G->size; i++) {
        for (j = p; j < G->size-1; j++) {
            /* aresta */
            G->edge[j][i] = G->edge[j+1][i];
            G->prop[j][i].weight = G->prop[j+1][i].weight;
            G->prop[j][i].label = G->prop[j+1][i].label;
            G->prop[j][i].color = G->prop[j+1][i].color;
            G->prop[j][i].mark = G->prop[j+1][i].mark;
            /* pontos de controle */
            for (k = 0; k < 4; k++) {
                G->prop[j][i].ctrlpoints[k][X] =
                        G->prop[j+1][i].ctrlpoints[k][X];
            }
            for (k = 0; k < 4; k++) {
                G->prop[j][i].ctrlpoints[k][Y] =
                        G->prop[j+1][i].ctrlpoints[k][Y];
            }
        }
    }
    for (i = 0; i < G->size; i++) {
        /* arestas */
        G->edge[i][G->size-1] = 0;
        G->edge[G->size-1][i] = 0;
        /* pontos de controle */
        for (k = 0; k < 4; k++) {
            G->prop[i][G->size].ctrlpoints[k][X] = 0;
        }
        for (k = 0; k < 4; k++) {
            G->prop[G->size][i].ctrlpoints[k][X] = 0;
        }
        for (k = 0; k < 4; k++) {
            G->prop[i][G->size].ctrlpoints[k][Y] = 0;
        }
        for (k = 0; k < 4; k++) {
            G->prop[G->size][i].ctrlpoints[k][Y] = 0;
        }
    }            
  
    /* Atualiza valores */
    G->size--;
    //G->nedges -= G->degree[p];
}



void AddEdge(Graph *G, int x, int y) {

    if ((x != y) && 
        ((!G->edge[x][y]) &&
         (!G->edge[y][x]) 
        ) 
       ){
        G->edge[x][y] = 1;
        G->prop[x][y].weight = 0.0;
        G->prop[x][y].color = 0;
        G->prop[x][y].mark = 0;
        G->prop[x][y].label = NULL;

        G->edge[y][x] = 1;
        G->prop[y][x].weight = 0.0;
        G->prop[y][x].color = 0;
        G->prop[y][x].mark = 0;
        G->prop[y][x].label = NULL;
        
        G->nedges++;
    }
    G->vertex[x].degree++;
    G->vertex[y].degree++;
    
    UpdateCtrlPoints(G, x, y, LINES);
}



void RemoveEdge(Graph *G, int x, int y) {

    if (x != y) {
        G->edge[x][y] = 0;
        G->edge[y][x] = 0;
        if (G->prop[x][y].label)
            free(G->prop[x][y].label);
        if (G->prop[y][x].label)
            free(G->prop[y][x].label);
        G->nedges--;
    }
    G->vertex[x].degree--;
    G->vertex[y].degree--;
}


void AddArc(Graph *G, int x, int y) {

    if (x != y) {
        G->edge[x][y] = 1;
        G->prop[x][y].weight = 0.0;
        G->prop[x][y].color = 0;
        G->prop[x][y].mark = 0;
        G->prop[x][y].label = NULL;
        G->narcs++;
    }
    G->vertex[x].outdegree++;
    G->vertex[y].indegree++;
    UpdateCtrlPoints(G, x, y, LINES);
}


void RemoveArc(Graph *G, int x, int y) {

    if (x != y) {
        G->edge[x][y] = 0;
        if (G->prop[x][y].label)
            free(G->prop[x][y].label);
        G->narcs--;
    }
    G->vertex[x].outdegree--;
    G->vertex[y].indegree--;
}


void ClearMarkedVerts(Graph *G) {
int i;

    for (i = 0; i < G->size; i++) {
        G->vertex[i].mark = 0;
    }

}


void ClearMarkedEdges(Graph *G) {
int i, j;

    for (i = 0; i < G->size; i++) {
        for (j = 0; j < G->size; j++) {
            G->prop[i][j].mark = 0;
		}
    }

}


/* Verifica se determinado vertice pertence ao grafo, e retorna tal vertice */
int IDinG(Graph *G, int ID) {
int i;

    for (i=0; i < G->size; i++) {
        if (G->vertex[i].id == ID) {
            return i;
        } 
    }

    return -1;
    
}



void CreateRandomGraph(Graph *G, int n, float p) {
int i,j;

    srand(time(NULL));
    InitGraph(G, G->type);

    for (i = 0; i < n; i++)
        AddPoint(G, 0, 0);
    
    for (i = 0; i < n; i++) { 
        for (j = i+1; j < n; j++) { 
            if (p > (random() / (float) RAND_MAX)) {
                AddEdge(G, i, j);
            }
        }
    }

}


void CreateKn(Graph *G, int n) {
int i, j;

    InitGraph(G, G->type);

    for (i = 0; i < n; i++)
        AddPoint(G, 0, 0);
    
    for (i = 0; i < n; i++) { 
        for (j = i+1; j < n; j++) { 
            AddEdge(G, i, j);
        }
    }
}


void CreateKnn(Graph *G, int n1, int n2){
int i, j;

    InitGraph(G, G->type);

    for (i = 0; i < n1+n2; i++)
        AddPoint(G, 0, 0);

    /* Create bipartite edges */
    for (i = 0; i < n1; i++) { 
        for (j = n1; j < n1+n2; j++) { 
            AddEdge(G, i, j);
        }
    }
}


void CreateRegular(Graph *G, int n, int r){
/*int i, j;
time_t t;*/

    (void) r;
    (void) n;
    (void) G;

/*    srand(time(&t));
    for (i = 0; i < n; i++) { 
        while (G->degree[i] < (2*r)){
            j = (random() % (n-i-1))+i+1;
            while ((G->edge[i][j] > 0) ||
                   (G->degree[j] >= (2*r)))
               j  = (random() % (n-i-1))+i+1;
            AddEdge(G, i, j);
        }
    }*/

    /* Forma cliques:
    for (i = 0; i < n; i++) { 
        for (j = (i+1); (j < n) && (G->degree[i] < (2*r)); j++){
            if ((G->degree[j] < (2*r)) && (G->edge[i][j] == 0))
                AddEdge(G, i, j);
        }
    }*/
}


void CreateStar(Graph *G, int n){
int i;

    InitGraph(G, G->type);

    for (i = 0; i < n; i++)
        AddPoint(G, 0, 0);
    
    for (i = 1; i < n; i++) { 
        AddEdge(G, 0, i);
    }
}


char *DotChooseColor(int i, Graph *G) {
char *color;

    if ((G->vertex[i].color < 0) || (G->vertex[i].color > LASTCOLOR)){
        fprintf(stderr, "Unexpected color (%d) of vertex %d\n", 
                G->vertex[i].color, i);
        exit(1);
    }

    color = (char *) malloc (80 * sizeof(char));
    sprintf(color, "%s", color_def[G->vertex[i].color].name);
	
    return color;
}

Color Rgb2Code(RGB value) {

    (void) value;

    return 0;    
}

RGB *Code2Rgb(Color value) {
RGB *color;

    if ((value < 0) || (value > LASTCOLOR)){
        fprintf(stderr, "Unexpected color (%d)", value);
        exit(1);
    }

    color = (RGB *) malloc(sizeof(RGB));
    color->r = color_def[value].r;
    color->g = color_def[value].g;
    color->b = color_def[value].b;
    
    return color;
}

/* ******* */
/* * End * */
/* ******* */
