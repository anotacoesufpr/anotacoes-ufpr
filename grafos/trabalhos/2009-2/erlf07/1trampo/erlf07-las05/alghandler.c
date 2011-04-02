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
/* * alghandler.c * */
/* **************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "alghandler.h"
#include "geometry.h"
#include "color.h"


AlgList L;    /* List of Algorithms */
AlgList TL;	  /* List of Transformation Algorithms */
AlgListR RL;  /* List of Result Algorithms */
AlgListS SL;  /* List of Search Algorithms */
AlgListSS SSL;/* List of Step by Step Algorithms */
	
/* iface.c */
extern int menu_test;


void AddTestAlgorithm(int (*func)(Graph *G, char *s), char *menu_item,
        int plugin, int flags) {
static int first=1;
Algor *node;

    //printf("%s: OK.\n", menu_item);

    if (first) {
        //menu_test = glutCreateMenu(MenuTestCall);
        InitializeAlgList(&L);
        node = (Algor *) malloc (sizeof (struct algor));
        node->prev = NULL;
        node->next = NULL;
        L.first = node;
        L.last = node;
        node->alg = func;
        node->string = (char *) malloc (80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        first = 0;
        L.size++;
	
        ////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);
	
    } else {
        node = (Algor *) malloc (sizeof (struct algor));
	node->prev = L.last;
        L.last->next = node;
        L.last = node;
	L.last->next = NULL;
        node->alg = func;
	node->string = (char *) malloc (80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        L.size++;
	
	////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);

    }
    
}

void AddResultAlgorithm(
          int (*func)(Graph *G, char *s, List *arc_edges, List *verts), 
	  char *menu_item, int plugin, int flags) {
static int first=1;
AlgorR *node;


    //printf("%s: OK.\n", menu_item);

    if (first) {
        //menu_test = glutCreateMenu(MenuTestCall);
        InitializeAlgListR(&RL);
        node = (AlgorR *) malloc (sizeof (struct algorr));
        node->prev = NULL;
        node->next = NULL;
        RL.first = node;
        RL.last = node;
        node->alg = func;
        node->string = (char *) malloc(80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        first = 0;
        RL.size++;
	
        ////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);
	
    } else {
        node = (AlgorR *) malloc (sizeof (struct algorr));
	node->prev = RL.last;
        RL.last->next = node;
        RL.last = node;
	RL.last->next = NULL;
        node->alg = func;
	node->string = (char *) malloc(80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        RL.size++;
	
	////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);

    }

}

void AddStepAlgorithm(
          int (*func)(Graph *G, char *s, int indx, List *arc_edges, List *verts), 
	  char *menu_item, int plugin, int flags) {
static int first=1;
AlgorSS *node;

    if (first) {
        InitializeAlgListSS(&SSL);
        node = (AlgorSS *) malloc (sizeof (struct algorss));
        node->prev = NULL;
        node->next = NULL;
        SSL.first = node;
        SSL.last = node;
        node->alg = func;
        node->string = (char *) malloc(80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
        first = 0;
        SSL.size++;
    } else {
        node = (AlgorSS *) malloc (sizeof (struct algorss));
        node->prev = SSL.last;
        SSL.last->next = node;
        SSL.last = node;
        SSL.last->next = NULL;
        node->alg = func;
        node->string = (char *) malloc(80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
        SSL.size++;
    }
	
}

void AddTransformation(int (*func)(Graph *G, char *s), char *menu_item,
        int plugin, int flags) {
static int first=1;
Algor *node;


    if (first) {
        //menu_test = glutCreateMenu(MenuTestCall);
        InitializeAlgList(&TL);
        node = (Algor *) malloc (sizeof (struct algor));
        node->prev = NULL;
        node->next = NULL;
        TL.first = node;
        TL.last = node;
        node->alg = func;
        node->string = (char *) malloc (80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        first = 0;
        TL.size++;
	
        ////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);
	
    } else {
        node = (Algor *) malloc (sizeof (struct algor));
	node->prev = TL.last;
        TL.last->next = node;
        TL.last = node;
	TL.last->next = NULL;
        node->alg = func;
	node->string = (char *) malloc (80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        TL.size++;
	
	////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);

    }
	
}

void AddSearchAlgorithm(
          int (*func)(Graph *G, char *s, int indx, List *arc_edges, List *verts), 
	  char *menu_item, int plugin, int flags) {
static int first=1;
AlgorS *node;


    //printf("%s: OK.\n", menu_item);

    if (first) {
        //menu_test = glutCreateMenu(MenuTestCall);
        InitializeAlgListS(&SL);
        node = (AlgorS *) malloc (sizeof (struct algors));
        node->prev = NULL;
        node->next = NULL;
        SL.first = node;
        SL.last = node;
        node->alg = func;
        node->string = (char *) malloc(80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        first = 0;
        SL.size++;
	
        ////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);
	
    } else {
        node = (AlgorS *) malloc (sizeof (struct algors));
	node->prev = SL.last;
        SL.last->next = node;
        SL.last = node;
	SL.last->next = NULL;
        node->alg = func;
	node->string = (char *) malloc(80);
        strcpy(node->string, menu_item);
        node->plugin = plugin;
        node->flags = flags;
	//node.type = ;
        SL.size++;
	
	////glutSetMenu(menu_test);
        //glutAddMenuEntry(menu_item, list.size);

    }

}


/* Runs Algorithm */
int RunAlgorithm(char *name, Graph *G, char *s, int x, List *arc_edges, List *verts){
Algor *node;
AlgorR *noder;
AlgorS *nodes;
int r;

    if (L.size > 0) {
        node = L.first;
        while (node) {
            if (!strcmp(node->string, name)) {
                r = node->alg(G, s);
                return r;
            }
            node = node->next;
        }
    }

    if (RL.size > 0) {
        noder = RL.first;
        while (noder) {
            if (!strcmp(noder->string, name)) {
                r = noder->alg(G, s, arc_edges, verts);
                return r;
            }
            noder = noder->next;
        }
    }

    if (TL.size > 0) {
        node = TL.first;
        while (node) {
            if (!strcmp(node->string, name)) {
                r = node->alg(G, s);
                return r;
            }
            node = node->next;
        }
    }

    if (SL.size > 0) {
        nodes = SL.first;
        while (nodes) {
            if (!strcmp(nodes->string, name)) {
                r = nodes->alg(G, s, x, arc_edges, verts);
                return r;
            }
            nodes = nodes->next;
        }
    }

    if (SSL.size > 0) {
        nodes = SSL.first;
        while (nodes) {
            if (!strcmp(nodes->string, name)) {
                r = nodes->alg(G, s, x, arc_edges, verts);
                return r;
            }
            nodes = nodes->next;
        }
    }

    return 0;
}

void InitializeAlgList(AlgList *list) {
    
    list->size = 0;	    
    list->first = NULL;
    list->last = NULL;
}

void InitializeAlgListR(AlgListR *list) {
    
    list->size = 0;	    
    list->first = NULL;
    list->last = NULL;
}

void InitializeAlgListS(AlgListS *list) {
    
    list->size = 0;	    
    list->first = NULL;
    list->last = NULL;
}

void InitializeAlgListSS(AlgListSS *list) {
    
    list->size = 0;	    
    list->first = NULL;
    list->last = NULL;
}

/* ******* */
/* * End * */
/* ******* */

