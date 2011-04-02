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


/* ******** */
/* * rw.h * */
/* ******** */

#ifndef __RW_H__
#define __RW_H__


#include "graph.h"

int ReadPlainDotGraph(const char *filename, Graph *G, GraphType Gtype);
int LoadGraph(const char *filename, Graph *G);
int WriteGraph(const char *filename, Graph *G);
int WriteDotGraph(const char *filename, Graph *G);
int WritePsGraph(const char *filename, Graph *G);
char *read_label(char *s);


#endif

/* ******* */
/* * End * */
/* ******* */

