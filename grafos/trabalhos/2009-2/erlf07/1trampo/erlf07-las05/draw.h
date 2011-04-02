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


/* ********** */
/* * draw.h * */
/* ********** */

#ifndef __DRAW_H__
#define __DRAW_H__


#include "graph.h"


/* Point */
typedef struct point {
    float x,y;
} Point;

/* Object to be drawn */
typedef struct drawstruct {
    int allocated_size;
    Point (**arrow)[3]; // Arrow triangle
    List *SpecEdges;
    List *SpecVerts;
} DrawStruct;


/* Functions */
void AllocDrawStruct(DrawStruct *DS);
void ReAllocDrawStruct(DrawStruct *DS, int size);
void FreeDrawStruct(DrawStruct *DS);

void InitDrawStruct(DrawStruct *DS);
void ClearDrawStruct(DrawStruct *DS);
void ClearSpecEdges(DrawStruct *DS); 
void ClearSpecVerts(DrawStruct *DS);
void SetSpecEdges(DrawStruct *DS, List *E);
void SetSpecVerts(DrawStruct *DS, List *V);
void AddSpecEdges(DrawStruct *DS, List *E);
void AddSpecVerts(DrawStruct *DS, List *V);

void DrawObjects(DrawStruct *DS, Graph *G);
DrawStruct *GetDrawStruct(void);


#endif

/* ******* */
/* * End * */
/* ******* */
