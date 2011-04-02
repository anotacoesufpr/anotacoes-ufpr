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
/* * alghandler.h * */
/* **************** */

#ifndef __ALGHANDLER_H__
#define __ALGHANDLER_H__


//#include <GL/glut.h>
#include "graph.h"
#include "list.h"

//#define MAXSTRSIZE 200

/* The node of the algorithms list */
typedef struct algor {
    int type;                      /* test alg., result alg., etc. */
    int (*alg)(Graph *G, char *s); /* Comments below (*) */
    char *string;                  /* Algorithm name */
    int plugin;
    int flags;
    struct algor *next;
    struct algor *prev;
} Algor;
/* (*) Ptr to a function that takes (a graph and a string) and returns a int */

/* The node of the result algorithms list */
typedef struct algorr {
    int type;                      /* test alg., result alg., etc. */
    int (*alg) (Graph *G, char *s, List *arc_edges, List *verts);
    char *string;                  /* Algorithm name */
    int plugin;
    int flags;
    struct algorr *next;
    struct algorr *prev;
} AlgorR;

/* The node of the search algorithms list */
typedef struct algors {
    int type;                      /* test alg., result alg., etc. */
    int (*alg) (Graph *G, char *s, int indx, List *arc_edges, List *verts);
    char *string;                  /* Algorithm name */
    int plugin;
    int flags;
    struct algors *next;
    struct algors *prev;
} AlgorS;

/* The node of the step by step algorithms list */
typedef struct algorss {
    int type;                      /* test alg., result alg., etc. */
    int (*alg) (Graph *G, char *s, int indx, List *arc_edges, List *verts);
    char *string;                  /* Algorithm name */
    int plugin;
    int flags;
    struct algorss *next;
    struct algorss *prev;
} AlgorSS;

/* Algorithms list */
typedef struct alglist {
    int size;
    Algor *first;
    Algor *last;
} AlgList;

/* Result Algorithms list */
typedef struct alglistr {
    int size;
    AlgorR *first;
    AlgorR *last;
} AlgListR;

/* Search Algorithms list */
typedef struct alglists {
    int size;
    AlgorS *first;
    AlgorS *last;
} AlgListS;

/* Search Algorithms list */
typedef struct alglistss {
    int size;
    AlgorSS *first;
    AlgorSS *last;
} AlgListSS;

/* Functions */

void AddTestAlgorithm(int (*func)(Graph *G, char *s), char *menu_item,
        int plugin, int flags);
void AddResultAlgorithm(
             int (*func)(Graph *G, char *s, List *arc_edges, List *verts),
             char *menu_item, int plugin, int flags); 
void AddStepAlgorithm(
             int (*func)(Graph *G, char *s, int indx, List *arc_edges, 
			 List *verts), char *menu_item, int plugin,
             int flags); 
void AddTransformation(int (*func)(Graph *G, char *s), char *menu_item,
        int plugin, int flags);
void AddSearchAlgorithm(
             int (*func)(Graph *G, char *s, int indx, List *arc_edges, 
			 List *verts), char *menu_item, int plugin,
             int flags); 


int RunAlgorithm(char *name, Graph *G, char *s, int x, List *arc_edges, List *verts);

void InitializeAlgList(AlgList *list);
void InitializeAlgListR(AlgListR *list);
void InitializeAlgListS(AlgListS *list);
void InitializeAlgListSS(AlgListSS *list);
	

#endif

/* ******* */
/* * End * */
/* ******* */

