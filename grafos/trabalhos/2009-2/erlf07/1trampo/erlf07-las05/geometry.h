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


/* ************** */
/* * geometry.h * */
/* ************** */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__


#include "graph.h"
#include "draw.h"

#define HEIGHT 600
#define WIDTH 800

#define LINES 0
#define SPLINES 1

/* Macros */
#define __MIN(a, b) (a < b) ? a : b;
#define __MAX(a, b) (a > b) ? a : b;

int CallNeato(Graph *G);
int CallDot(Graph *G);
void RedrawAsCircle(Graph *G, int width, int height);
void RedrawAsBipartite(Graph *G, int width, int height, int n1, int n2);
void RedrawWithCenteredVertex(Graph *G, int width, int height);
void FitToWindow(Graph *G, int width, int height);
void UpdateCtrlPoints(Graph *G, int x, int y, int mode);
void CalculateArrows(Graph *G, DrawStruct *DS);
void PointInLine(Point p1, Point p2, Point *p, int dist, int flag);
void RotatePoint(Point *p, Point o, int degree);
void spline_point(int degree,
        int *ctrl_x, int *ctrl_y, int *x, int *y, int n);
double hornbez(int degree, int *coeff, double t);

#endif

/* ******* */
/* * End * */
/* ******* */

