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
/* * step.c * */
/* **************** */

#include <stdlib.h>
#include "graph.h"
#include "list.h"
#include "draw.h"
#include "step.h"

StepStruct S;

/* Initialize Step Structure */
void InitStepStruct(void){

    S.index = 0;
    S.size = 0;
}

/* Save new step in step Structure */
void AddStep(Graph *G, List *arc_edges, List *verts) {
static int step_id;

	if (S.size < MAX_STEPS) {
	
		S.index = S.size;
		step_id++;
		/* Copiando Grafo para o Passo */
		CopyGraph(&(S.steps[S.index].G), G);
		
		/* Inicializando Lista de Vertices e Arestas do Passo */
		S.steps[S.index].id = step_id;
	   	S.steps[S.index].SpecEdges = CreateList();
		InitList(S.steps[S.index].SpecEdges);
		S.steps[S.index].SpecVerts = CreateList();
		InitList(S.steps[S.index].SpecVerts);    	
	    
	    /* Copiando Lista de Vertices e Arestas para o Passo */
	    CopyList(S.steps[S.index].SpecEdges, arc_edges);
	    CopyList(S.steps[S.index].SpecVerts, verts);    
	    
		S.size++;
	}
}

/* Copy saved step into a Graph, vertex and edges */
void ShowStep(Graph *G, List *arc_edges, List *verts, int step) {

	if (S.size > 0) {
		if (step < 0)
			S.index = 0;
		else if (step >= S.size)
			S.index = S.size -1;
		else
			S.index = step;
		/* Copiando Grafo para o Passo */
		CopyGraph(G, &(S.steps[S.index].G));
	    
	    /* Copiando Lista de Vertices e Arestas do Passo */    
	    CopyList(arc_edges, S.steps[S.index].SpecEdges);
	    CopyList(verts, S.steps[S.index].SpecVerts);       
	}
}

/* Goto first step */
void FirstStep(Graph *G, List *arc_edges, List *verts) {

	ShowStep(G, arc_edges, verts, 0);
}

/* Goto previous step */
void PreviousStep(Graph *G, List *arc_edges, List *verts) {

	ShowStep(G, arc_edges, verts, S.index-1);
}

/* Goto next step */
void NextStep(Graph *G, List *arc_edges, List *verts) {

	ShowStep(G, arc_edges, verts, S.index+1);
}

/* Goto last step */
void LastStep(Graph *G, List *arc_edges, List *verts) {

	ShowStep(G, arc_edges, verts, S.size -1);
}

/* Return number of last step */
int GetLastStep(void) {

	return S.size;
}

/* Return if step by step is running */
char GetExecStateStep(void) {

	return S.exec_state;
}

/* Set step by step running state */
void SetExecStateStep(char state) {

	S.exec_state = state;
}

/* ******* */
/* * End * */
/* ******* */

