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
/* * algorithms.h * */
/* **************** */

#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__


#include "graph.h"
#include "list.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Algorithms that can be inserted to be called by the interface */

/* Test Algorithms */
int Chordal(Graph *G, char *mess);

/* Result Algorithms */
int SpanningTree(Graph *G, char *mess, List *arc_edges, List *verts);

/* Transformation Algorithms */
int Complement(Graph *G, char *mess);
int Line(Graph *G, char *mess);

/* Step Algorithms */
int Step_DepthSearch(Graph *G, char *mess, int x, List *arc_edges, List *verts);

/* Search Algorithms */
int DepthSearch(Graph *G, char *mess, int x, List *arc_edges, List *verts);

/* Auxiliares */
/* Coloring */
int Delete_Sink(Graph *G);

int step_refresh(List *arc_edges, List *verts);

//typedef enum {RESET, NEXT} PalOpt;
//int GetNextColor(PalOpt opt);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __ALGORITHMS_H__ */

/* ******* */
/* * End * */
/* ******* */
