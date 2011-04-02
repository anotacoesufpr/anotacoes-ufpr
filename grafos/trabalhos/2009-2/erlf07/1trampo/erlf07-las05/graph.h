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
/* * graph.h * */
/* *********** */

#ifndef __GRAPH_H__
#define __GRAPH_H__


#include "list.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Maximum string size */
#define MAXSTRSIZE 1000

/* Minimum number of vertices to be allocated */
#define MAX_POINTS 100

/* Control Points */
#define X 0
#define Y 1
#define Z 2
#define ORG 0
#define DEST 3
#define CTR1 1
#define CTR2 2


/* Graph "type" */
typedef enum {GRAPH, DIGRAPH} GraphType;

/* Vertex or edge color */
typedef int Color;

/* RGB color */
typedef struct rgb {
    double r;
    double g; 
    double b;
} RGB;

/* Vertex or edge weight */
typedef float Weight;

/* Graph vertex */
typedef struct vertex {
    int id;         /* Unique incremental id */
    char *label;    /* Text label */
    Weight weight;  /* Weight */
    float x, y;     /* 2D Position */
    Color color;    /* Color index */
    int concomp;    /* Conected component */ 
    char mark;      /* Mark */
    /* Makes sense only for graphs */
    int degree;     /* Vertex degree */
	/* Makes sense only for digraphs */
    int indegree;   /* Input degree */
    int outdegree;  /* Output degree */
} Vertex;

/* Graph edge */
typedef char Edge;

/* Graph edge properties */
typedef struct edge_prop {
    char *label;             /* Text label */
    Weight weight;           /* Weight */
    Color color;             /* Color index */
    char mark;               /* Mark */
    float ctrlpoints[4][3];  /* Control points */
} Edge_prop;


/* Graph */
typedef struct graph {
    /* The graph struct. All fields here have the values automatically 
	 * updated when you change the graph (e.g. vertex insertions, edge
	 * deletion, etc). */
    GraphType type;
    int size;           /* Number of vertices */
    int nextid;         /* ID to be assigned to the next inserted vertex */
    int nedges;         /* Number of edges (graphs) */
    int narcs;          /* Number of arcs (digraphs) */
    int allocated_size; /* Allocated space size */
    Vertex *vertex;     /* Vertex list */
    Edge **edge;        /* Adjacency-Matrix */
    Edge_prop **prop;   /* Properties of each edge in the Adjacency-Matrix */
	
    /* The following fields are not initialized and do not have the
	 * correct value updated automatically. If you want to use
	 * these fields you have to fill them by yourself. */
	int ncomp;          /* Number of connected components. */
    int ncolor;         /* Number of colors used (not chromatic number) */
    int encolor;        /* Number of colors used (edges) */

} Graph;


/* Auxiliar */

/* A single vertex */
typedef int SVertex;

/* A single edge */
typedef struct {
    SVertex u;
    SVertex v;
} SEdge;


/* Functions */
void AllocGraph(Graph *G);
void ReAllocGraph(Graph *G, int size);
void FreeGraph(Graph *G);

void InitGraph(Graph *G, GraphType type);
void InitEdges(Graph *G);

void CopyGraph(Graph *H, Graph *G);

void AddPoint(Graph *G, float x, float y);
void RemovePoint(Graph *G, int p);
void AddEdge(Graph *G, int x, int y);
void RemoveEdge(Graph *G, int x, int y);
void AddArc(Graph *G, int x, int y);
void RemoveArc(Graph *G, int x, int y);
void ClearMarkedVerts(Graph *G);
void ClearMarkedEdges(Graph *G);

int IDinG(Graph *G, int ID);

void CreateRandomGraph(Graph *G, int n, float p);
void CreateKn(Graph *G, int n);
void CreateKnn(Graph *G, int n1, int n2);
void CreateRegular(Graph *G, int n, int r);
void CreateStar(Graph *G, int n);

char *DotChooseColor(int i, Graph *G);
Color Rgb2Code(RGB value);
RGB *Code2Rgb(Color value);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GRAPH_H__ */

/* ******* */
/* * End * */
/* ******* */
