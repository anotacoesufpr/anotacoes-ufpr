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


/* ******** */
/* * gr.c * */
/* ******** */

#include <stdio.h>
#include "config.h"
#include "graph.h" 
#include "alghandler.h" 
#include "draw.h"
#ifdef GTK_IFACE
#include "iface/iface.h"
#endif
#include "algorithms.h"
#include "rc.h"
#include "plugins.h"
#include "pgin.h"

/* Graph */ 
Graph G;

/* Configuration */
Config *config;

/* Draw structure: draw.c */
extern DrawStruct DS;


/* The main function: Initializes the graph (that are showed on the
 * interface), add the algorithms and call the interface loop */
int main(int argc, char **argv) {

    /* Allocate memory */
    AllocGraph(&G);
    AllocDrawStruct(&DS);

    /* Initializes the graph */
    InitGraph(&G, GRAPH);
   
    /* Initializes draw struct */
    InitDrawStruct(&DS);

    /* Test algorithms */
    
    /* The algorithms inserted (Eulerian, Chordal, etc) are 
     * in algorithms.c */
    AddTestAlgorithm(Chordal, "Chordal", 0, 0);
    
    /* Result Algorithms */
    AddResultAlgorithm(SpanningTree, "Span. Tree", 0, 0);
    
    /* Transformations Algorithms */
    AddTransformation(Line, "Line", 0, 0);
    AddTransformation(Complement, "Complement", 0, PGIN_FLAG_NOREDRAW);
    
    /* Step by Step Algorithms */
	AddStepAlgorithm(Step_DepthSearch, "Depth First", 0, 0);

    /* Search Algorithms */
	AddSearchAlgorithm(DepthSearch, "Depth First", 0, 0);
	
    /* Reads configuration */
    config = read_config();

    /* Loads plugins */
    if (config->plugins_path != NULL)
        load_plugins(config->plugins_path);

    /* Loop */
    IfaceLoop(&argc, &argv);

    unload_plugins();
    
    return 0; 
}

/* ******* */
/* * End * */
/* ******* */

