/*
 *  grafo - graph editor
 *  Copyright (c) 2003
 *      Murilo Vicente Goncalves da Silva <murilo@pet.inf.ufpr.br>
 *      Oliver Matias van Kaick <oliver@pet.inf.ufpr.br>
 *  Copyright (c) 2007
 *  	Ulisses Cordeiro Pereira <ulisses@cordeiropereira.com.br>
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


/* ********** */
/* * draw.c * */
/* ********** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include "geometry.h"
#include "graph.h"
#include "draw.h"
#include "list.h"


DrawStruct DS;


DrawStruct *GetDrawStruct(void) {
    return &DS;
}


void InitDrawStruct(DrawStruct *DS) {

    DS->SpecEdges = CreateList();
    InitList(DS->SpecEdges);
    DS->SpecVerts = CreateList();
    InitList(DS->SpecVerts);
}


void AllocDrawStruct(DrawStruct *DS){
int i;

    /* Set allocated size */
    DS->allocated_size = MAX_POINTS;
   
    /* Alloc vertices array */
    DS->arrow = (Point(**)[3]) malloc(DS->allocated_size *
            sizeof(Point(*)[3]));
    DS->arrow[0] = (Point(*)[3]) malloc(DS->allocated_size *
            DS->allocated_size * sizeof(Point[3]));
    for (i = 1; i < DS->allocated_size; i++){
        DS->arrow[i] = DS->arrow[0] + (DS->allocated_size * i);
    }

}


void ReAllocDrawStruct(DrawStruct *DS, int size){
Point (**temp)[3];
int i, j;

    /* Check if new size is valid */
    if (size <= DS->allocated_size){
        return ;
    }

    /* Allocate new arrow buffer */
    temp = (Point(**)[3]) malloc(size * sizeof(Point(*)[3]));
    temp[0] = (Point(*)[3]) malloc(size * size * sizeof(Point[3]));
    for (i = 1; i < size; i++){
        temp[i] = temp[0] + (size * i);
    }

    /* Copy old data to new buffer */
    for (i = 0; i < DS->allocated_size; i++){
        for (j = 0; j < DS->allocated_size; j++){
            memcpy(&(temp[i][j]), &(DS->arrow[i][j]),
                    sizeof(Point[3]));
        }
    }

    /* Free old buffer */
    free(DS->arrow[0]);
    free(DS->arrow);

    /* Assign new buffer */
    DS->arrow = temp;
    DS->allocated_size = size;
}


void FreeDrawStruct(DrawStruct *DS){

    free(DS->arrow[0]);
    free(DS->arrow);
    DS->allocated_size = 0;
}


void ClearDrawStruct(DrawStruct *DS) {
    CleanList(DS->SpecEdges);
    CleanList(DS->SpecVerts);
}

void ClearSpecEdges(DrawStruct *DS) {
    CleanList(DS->SpecEdges);
}

void ClearSpecVerts(DrawStruct *DS) {
    CleanList(DS->SpecVerts);
}


/* Set the edges E in the struct DS */
void SetSpecEdges(DrawStruct *DS, List *E) {

    CopyList(DS->SpecEdges, E);

}

/* Set the vertices V in the struct DS */
void SetSpecVerts(DrawStruct *DS, List *V) {

    CopyList(DS->SpecVerts, V);

}

void AddSpecEdges(DrawStruct *DS, List *E) {

    (void) DS;
    (void) E;

}

void AddSpecVerts(DrawStruct *DS, List *V) {

    (void) DS;
    (void) V;

}


void DrawObjects(DrawStruct *DS, Graph *G) {
/*static int first=1;*/
int i,j,k;
SEdge *E;
//SVertex *V;
Node N;

    /*if (first) {
        InitDrawStruct(DS);
        first = 0;
    }*/

    if (G->type == DIGRAPH) {
        /* Draw the head of the arrows */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);
        for (i=0; i < G->size; i++) {
            for (j=0; j < G->size; j++) {
                if ((i!=j) && (G->edge[i][j] && (!G->edge[j][i]))) {
                    for (k=0; k < 3; k++) {
                        glVertex2i(DS->arrow[i][j][0].x, DS->arrow[i][j][0].y);
                        glVertex2i(DS->arrow[i][j][1].x, DS->arrow[i][j][1].y);
                        glVertex2i(DS->arrow[i][j][2].x, DS->arrow[i][j][2].y);
                    }
                } else if ((i!=j) && (G->edge[i][j] && (G->edge[j][i]))) {
                    for (k=0; k < 3; k++) {
                        glVertex2i(DS->arrow[i][j][0].x, DS->arrow[i][j][0].y);
                        glVertex2i(DS->arrow[i][j][1].x, DS->arrow[i][j][1].y);
                        glVertex2i(DS->arrow[i][j][2].x, DS->arrow[i][j][2].y);
                    }
                    for (k=0; k < 3; k++) {
                        glVertex2i(DS->arrow[j][i][0].x, DS->arrow[j][i][0].y);
                        glVertex2i(DS->arrow[j][i][1].x, DS->arrow[j][i][1].y);
                        glVertex2i(DS->arrow[j][i][2].x, DS->arrow[j][i][2].y);
                    }

                }
            }
        }
        glEnd();
    
    }

    /* Draw special edges */
    N = DS->SpecEdges->head;

    glLineWidth(4.0);

    while (N != NULL) {

        E = (SEdge *) malloc (sizeof(SEdge));
        memcpy(E, N->data, sizeof(SEdge));
        
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4,
                 &(G->prop[E->u][E->v].ctrlpoints[0][0]));
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_STRIP);
            for (i = 0; i <= 30; i++)
                glEvalCoord1f((GLfloat) i/30.0);
        glEnd();
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4,
                        &(G->prop[E->u][E->v].ctrlpoints[0][0]));
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_STRIP);
            for (i = 0; i <= 30; i++)
                glEvalCoord1f((GLfloat) i/30.0);
        glEnd();
        
        N = N->next;
        free(E);
    }


    glLineWidth(1.0);
	
//    /* Special Vertices */
//    N = DS->SpecVerts->head;
//    V = (Vertex *) malloc (sizeof(Vertex));
//
//    //glLineWidth(4.0);
//    glBegin(GL_POINTS);
//    glColor3f(1.0, 1.0, 0.0);
//    glPointSize(10.0);
//
//    while (N != NULL) {
//        memcpy(V, N->data, sizeof(Vertex));
//printf("llala\n");        
//        glVertex2d(G->point[*V].x, G->point[*V].y);
//printf("--------%d-------%d-------\n",G->point[*V].x, G->point[*V].y);
//        N = N->next;
//    }
//    glEnd();
//
//printf("AÇLSDJFÇLASDJFÇLAJSDLFK\n");        
//    free(V);
	
}

/* ******* */
/* * End * */
/* ******* */

