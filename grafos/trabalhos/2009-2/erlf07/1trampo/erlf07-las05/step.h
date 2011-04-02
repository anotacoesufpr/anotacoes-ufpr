/*
 *  grafo - graph editor
 *  Copyright (c) 2008
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
/* * step.h * */
/* **************** */

#ifndef __STEP_H__
#define __STEP_H__


#include "graph.h"
#include "list.h"
#include "draw.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Minimum number of steps to be allocated */
#define MAX_STEPS 1000
#define START_EXEC_STEPS 1
#define STOP_EXEC_STEPS 0
#define EXECUTING_STEPS 1
#define NOT_EXECUTING_STEPS 0

/* Step */
typedef struct step {
    int id;
    Graph G;
    List *SpecEdges;
    List *SpecVerts;
} Step;

/* StepStruct */
typedef struct stepstruct {
    int size;
    int index;
    Step steps[MAX_STEPS];
    char status_string[1000];
    char exec_state;
} StepStruct;

void InitStepStruct(void);
void AddStep(Graph *G, List *arc_edges, List *verts);
void ShowStep(Graph *G, List *arc_edges, List *verts, int step);
void FirstStep(Graph *G, List *arc_edges, List *verts);
void PreviousStep(Graph *G, List *arc_edges, List *verts);
void NextStep(Graph *G, List *arc_edges, List *verts);
void LastStep(Graph *G, List *arc_edges, List *verts);
int GetLastStep(void);
char GetExecStateStep(void);
void SetExecStateStep(char state);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __STEP_H__ */

/* ******* */
/* * End * */
/* ******* */
