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
/* * rw.c * */
/* ******** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "geometry.h"
#include "draw.h"
#include "rw.h"


extern DrawStruct DS;

char rw_error[1000];


/* Reads a dot plain file. The labels of the nodes must be 
 * integers 0, 1, 2, ... For details of the file format see 
 * dot documentation */
int ReadPlainDotGraph(const char *filename, Graph *G, GraphType GType) {
double w,h;    /* width and height from file */
double x, y;   /* Read values from file */
FILE *f;       /* File */
int v1, v2;    /* Index */
char *string;  /* String */
char *strptr;  /* aux */

    /* Opens the file */
    f = fopen(filename, "r");
    
    if (!f) {
        sprintf(rw_error, "Error openging plain dot graph file '%s'!\n",
                filename);
        return 0;
    }
    
    /* Alocs a string */
    string = (char *) malloc(MAXSTRSIZE * sizeof(char));
    strptr = string;
    
    InitGraph(G, GType);

    /* Reads the first line */
    fgets(string, MAXSTRSIZE * sizeof(char), f);
    if ((*string) != 'g') {
        sprintf(rw_error, "Invalid plain dot graph!\n");
        return 0;
    }

    while ((*string) != ' ') // ignora resto da palavra graph
        string++;
    while ((*string) == ' ') // ignora espacos
        string++;
    while ((*string) != ' ') // ignora o "scale" 
        string++;
    while ((*string) == ' ') // ignora espacos
        string++;
    sscanf (string, "%lf %lf", &w, &h); // width and height
    
    string = strptr;
    
    /* Reads the vertices and edges */
    fgets(string, MAXSTRSIZE * sizeof(char), f);
    while (!feof(f)){
        if ((*string) == 'n') {
            while ((*string) != ' ') // ignora resto da palavra nodo
                string++;
            while ((*string) == ' ') // ignora espacos
                string++;
            while ((*string) != ' ') // ignora label 
                string++;
            while ((*string) == ' ') // ignora espacos
                string++;
            sscanf (string, "%lf %lf", &x, &y);
	    G->vertex[G->size].x = (x * (WIDTH / w));
	    G->vertex[G->size].y = (y * (HEIGHT / h));

	    /* Xunchinho */
            G->vertex[G->size].y *= 0.7;
            G->vertex[G->size].y += 45;
        /* */
            G->vertex[G->size].id = G->nextid;
            G->nextid++;
	    
            G->size++;
        } else if ((*string) == 'e') {
            while ((*string) != ' ') // ignora resto da palavra edge 
                string++;
            while ((*string) == ' ') // ignora espaco
                string++;
            sscanf (string, "%d %d", &v1, &v2); // O resto da linha e' ignor.
            if (G->type == GRAPH) {
                G->edge[v1][v2] = 1;
                G->edge[v2][v1] = 1;
                G->vertex[v1].degree++;
                G->vertex[v2].degree++;
                G->nedges++;
                UpdateCtrlPoints(G, v1, v2, LINES);
            } else if (G->type == DIGRAPH) {
                G->edge[v1][v2] = 1;
                G->vertex[v1].outdegree++;
                G->vertex[v2].indegree++;
                G->narcs++;
                UpdateCtrlPoints(G, v1, v2, LINES);
            } else {
                sprintf(rw_error, "Invalid graph type\n");
            }
        } else if ((*string) == 's') {
            break; // encontrou o stop
        }

        string = strptr;
        fgets(string, MAXSTRSIZE * sizeof(char), f);
    }

    free(string);

    /* Closes the file */
    fclose (f);
    return 1;

}


int LoadGraph(const char *filename, Graph *G) {
FILE *f;       /* File */
char *string;  /* String */
int v1, v2;     /* Index */
float weight;
int color, r;

    /* Opens the file */
    f = fopen(filename, "r");
    if (!f) {
        sprintf(rw_error, "Error opening graph file '%s'!\n", filename);
        return 0;
    }
    
    /* Alocs a string */
    string = (char *) malloc(MAXSTRSIZE * sizeof(char));

    InitGraph(G, GRAPH);
	G->type = GRAPH;
   
    /* Reads the vertices and edges/arcs */
    
    fgets(string, MAXSTRSIZE * sizeof(char), f);
    while (!feof(f)){
        if ((*string) == 't'){
            if (!strncmp(string+2, "graph", 5))
                G->type = GRAPH;
            else if (!strncmp(string+2, "digraph", 7))
                G->type = DIGRAPH;
        } else if ((*string) == 'v') {
            sscanf(string+2, "%f %f %f %d%n",
                   &(G->vertex[G->size].x),
                   &(G->vertex[G->size].y),
                   &(G->vertex[G->size].weight),
                   &(G->vertex[G->size].color),
                   &r);
            G->vertex[G->size].label = read_label(string+2+r);
            G->vertex[G->size].id = G->nextid;
            G->nextid++;
            G->size++;
		} else if ((*string) == 'e') {
			if (G->type == DIGRAPH){
				sprintf(rw_error, "Edge entry found in a digraph!\n");
				return 0;
			}
			sscanf (string+2, "%d %d %f %d%n", &v1, &v2, &weight,
					&color, &r);
			G->prop[v1][v2].label = G->prop[v2][v1].label =
					read_label(string+2+r);
			G->edge[v1][v2] = 1;
			G->edge[v2][v1] = 1;
			G->vertex[v1].degree++;
			G->vertex[v2].degree++;
			G->nedges++;
			G->prop[v1][v2].weight = weight;
			G->prop[v2][v1].weight = weight;
			G->prop[v1][v2].color = color;
			G->prop[v2][v1].color = color;
			UpdateCtrlPoints(G, v1, v2, LINES);
		} else if ((*string) == 'a') {
			if (G->type == GRAPH){
				sprintf(rw_error, "Arc entry found in a graph!\n");
				return 0;
			}
			sscanf (string+2, "%d %d %f %d%n", &v1, &v2, &weight,
					&color, &r);
			G->prop[v1][v2].label = read_label(string+2+r);
			G->edge[v1][v2] = 1;
			G->vertex[v1].outdegree++;
			G->vertex[v2].indegree++;
			G->narcs++; 
			G->prop[v1][v2].weight = weight;
			G->prop[v1][v2].color = color;
			UpdateCtrlPoints(G, v1, v2, LINES);
        }
        
        fgets(string, MAXSTRSIZE * sizeof(char), f);
    }

    /* Closes the file */
    fclose (f);
    
    /* Clear Graph and Draw Struct */
    ClearMarkedVerts(&G);
    ClearDrawStruct(&DS);
    
    return 1;
}


/* Writes an obj file */
int WriteGraph(const char *filename, Graph *G){
FILE *f;    /* File */
int i,j,k;  /* Indices */
int len;

    /* Opens the obj file */
    f = fopen(filename, "w");
    if (!f) {
        sprintf(rw_error, "Error creating graph file '%s'!\n", filename);
        return 0;
    }
   
    /* Write graph type */
    if (G->type == GRAPH)
        fprintf(f, "t graph\n");
    else if (G->type == DIGRAPH)
        fprintf(f, "t digraph\n");

    /* Writes the vertices */
    for (i = 0; i < G->size; i++){ 
        if (G->vertex[i].label != NULL){
            len = strlen(G->vertex[i].label);
            for (k = 0; k < len; k++){
                if (G->vertex[i].label[k] == '\"')
                    G->vertex[i].label[k] = '\'';
            }
            fprintf(f, "v %f %f %f %d \"%s\"\n",
                    G->vertex[i].x, G->vertex[i].y, G->vertex[i].weight,
                    G->vertex[i].color, G->vertex[i].label);
        } else
            fprintf(f, "v %f %f %f %d \"\"\n",
                    G->vertex[i].x, G->vertex[i].y, G->vertex[i].weight,
                    G->vertex[i].color);
    }
    
    /* Writes the arcs */
	if (G->type == GRAPH){
		for (i = 0; i < G->size; i++) {
			for (j = i+1; j < G->size; j++) {
				if (G->edge[i][j]) {
					if (G->prop[i][j].label != NULL){
						len = strlen(G->prop[i][j].label);
						for (k = 0; k < len; k++){
							if (G->prop[i][j].label[k] == '\"')
								G->prop[i][j].label[k] = '\'';
						}
						fprintf(f, "e %d %d %f %d \"%s\"\n", i, j,
								G->prop[i][j].weight, G->prop[i][j].color, 
								G->prop[i][j].label);
					} else
						fprintf(f, "e %d %d %f %d \"\"\n", i, j,
								G->prop[i][j].weight, G->prop[i][j].color);
				}
			}
		}
	} else {
		for (i = 0; i < G->size; i++) {
			for (j = 0; j < G->size; j++) {
				if (G->edge[i][j]) {
					if (G->prop[i][j].label != NULL){
						len = strlen(G->prop[i][j].label);
						for (k = 0; k < len; k++){
							if (G->prop[i][j].label[k] == '\"')
								G->prop[i][j].label[k] = '\'';
						}
						fprintf(f, "a %d %d %f %d \"%s\"\n", i, j,
								G->prop[i][j].weight, G->prop[i][j].color, 
								G->prop[i][j].label);
					} else
						fprintf(f, "a %d %d %f %d \"\"\n", i, j,
								G->prop[i][j].weight, G->prop[i][j].color);
				}
			}
		}
	}

    /* Closes the file */
    fclose (f);
    return 1;
}



int WriteDotGraph(const char *filename, Graph *G) {
FILE *f;
int i,j;
char *color;

    /* Opens the obj file */
    f = fopen(filename, "w");
    if (!f) {
        sprintf(rw_error, "Error creating graph file '%s'!\n", filename);
        return 0;
    }
    
    fprintf(f, "graph G {\n");

    /* Writes the edges */
    for (i = 0; i < G->size; i++) {
        for (j = 0; j < G->size; j++) {
            if (G->edge[i][j]) {
                color = DotChooseColor(i,G);
                fprintf(f, "	%d [style=filled, color=%s,fontcolor=white];\n"
                    , i, color);
                //free(color);
                if (i < j) {
                    fprintf(f, "	%d -- %d\n", i, j);
                }
            }
        }
    }

    fprintf(f, "}\n");

    /* Closes the file */
    fclose (f);
    return 1;
}


/* Writes a ps file */
int WritePsGraph(const char *filename, Graph *G){
FILE *f;  /* File */
int i,j;  /* Indices */
int width, height;
int maxwidth, minwidth, maxheight, minheight;
RGB *color;

    width  = 0;
    height = 0;
#if 0
    for (i = 0; i < G->size; i++){
        width  = MAX(width,  G->vertex[i].x);
        height = MAX(height, G->vertex[i].y);
    }
#endif

    if (G->size > 0) {
        maxwidth  = G->vertex[0].x;
        maxheight = G->vertex[0].y;
        minwidth  = G->vertex[0].x;
        minheight = G->vertex[0].y;
    } else {
        maxwidth  = 0;
        maxheight = 0;
        minwidth  = 0;
        minheight = 0;
       
    }
    
    for (i = 0; i < G->size; i++){
        maxwidth  = __MAX(maxwidth,  G->vertex[i].x);
        minwidth  = __MIN(minwidth,  G->vertex[i].x);
        maxheight = __MAX(maxheight, G->vertex[i].y);
        minheight = __MIN(minheight, G->vertex[i].y);
    }
    
    //width = 2 * maxwidth - minwidth; 
    width = maxwidth + minwidth; 
    //height = 2 * maxheight - minheight; 
    height = maxheight + minheight; 
    
    /* Opens the ps file */
    f = fopen(filename, "w");
    
    if (!f) {
        sprintf(rw_error, "Error creating graph file '%s'!\n", filename);
        return 0;
    }
 
    fprintf(f, "%%!PS-Adobe-2.0 EPSF-2.0\n");
    fprintf(f, "%%%%Creator: WritePsGraph()\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", width, height);
    fprintf(f, "%%%%EndComments\n");
    fprintf(f, "%%1 -1 scale\n");
    //fprintf(f, "%%0 -%d translate\n", height);

    fprintf(f, "/T {\n");
    fprintf(f, "    /y3 exch def\n");
    fprintf(f, "    /x3 exch def\n");
    fprintf(f, "    /y2 exch def\n");
    fprintf(f, "    /x2 exch def\n");
    fprintf(f, "    /y1 exch def\n");
    fprintf(f, "    /x1 exch def\n");
    fprintf(f, "    /b exch def\n");
    fprintf(f, "    /g exch def\n");
    fprintf(f, "    /r exch def\n");
    fprintf(f, "    r g b setrgbcolor\n");
    fprintf(f, "    newpath\n");
    fprintf(f, "    x1 y1 moveto\n");
    fprintf(f, "    x2 y2 lineto\n");
    fprintf(f, "    x3 y3 lineto\n");
    fprintf(f, "    x1 y1 lineto\n");
    fprintf(f, "    closepath\n");
    fprintf(f, "    fill\n");
    fprintf(f, "} bind def\n");

    fprintf(f, "/ellipsedict 8 dict def\n");
    fprintf(f, "ellipsedict /mtrx matrix put\n");
    fprintf(f, "/ellipse\n");
    fprintf(f, "    { ellipsedict begin\n");
    fprintf(f, "      /endangle exch def\n");
    fprintf(f, "      /startangle exch def\n");
    fprintf(f, "      /yrad exch def\n");
    fprintf(f, "      /xrad exch def\n");
    fprintf(f, "      /y exch def\n");
    fprintf(f, "      /x exch def\n");

    fprintf(f, "      /savematrix mtrx currentmatrix def\n");
    fprintf(f, "      x y translate\n");
    fprintf(f, "      xrad yrad scale\n");
    fprintf(f, "      0 0 1 startangle endangle arc\n");
    fprintf(f, "      savematrix setmatrix\n");
    fprintf(f, "      end\n");
    fprintf(f, "    } def\n");
 

    
    fprintf(f, "/L {\n");
    fprintf(f, "    0 0 0 setrgbcolor\n");
    fprintf(f, " moveto lineto stroke\n");
    fprintf(f, "} bind def\n");


    // outra coisa: ja' q se definiu o /L , nao precisa desenha
    // do jeito q esta' sendo desenhado.
    
    if (G->type == DIGRAPH) { 
        /* Writes the arcs */
        for (i = 0; i < G->size; i++) {
            for (j = 0; j < G->size; j++) {
                if (G->edge[i][j]) {
                    fprintf(f, "newpath %d %d moveto\n",
                                  (int) G->vertex[i].x, (int) G->vertex[i].y);
                    fprintf(f, "%d %d %d %d %d %d curveto\n",
                                  (int) G->prop[i][j].ctrlpoints[CTR1][X],
                                  (int) G->prop[i][j].ctrlpoints[CTR1][Y],
                                  (int) G->prop[i][j].ctrlpoints[CTR2][X],
                                  (int) G->prop[i][j].ctrlpoints[CTR2][Y],
                                  (int) G->vertex[j].x, (int) G->vertex[j].y);
                    fprintf(f, "stroke\n");

                    // Desenhando a ponta da flecha. 
		    if ((i!=j) && (G->edge[i][j] && (!G->edge[j][i]))) {
                            fprintf(f, ".0 .0 .0 %d %d %d %d %d %d T\n",
                                             (int) DS.arrow[i][j][0].x,
                                             (int) DS.arrow[i][j][0].y,
                                             (int) DS.arrow[i][j][1].x,
                                             (int) DS.arrow[i][j][1].y,
                                             (int) DS.arrow[i][j][2].x,
                                             (int) DS.arrow[i][j][2].y);
                    } else if ((i!=j) && (G->edge[i][j] && (G->edge[j][i]))) {
                            // aresta indo
                            fprintf(f, ".0 .0 .0 %d %d %d %d %d %d T\n",
                                             (int) DS.arrow[i][j][0].x,
                                             (int) DS.arrow[i][j][0].y,
                                             (int) DS.arrow[i][j][1].x,
                                             (int) DS.arrow[i][j][1].y,
                                             (int) DS.arrow[i][j][2].x,
                                             (int) DS.arrow[i][j][2].y);

			    // aresta voltando
                             fprintf(f, ".0 .0 .0 %d %d %d %d %d %d T\n",
                                             (int) DS.arrow[j][i][0].x,
                                             (int) DS.arrow[j][i][0].y,
                                             (int) DS.arrow[j][i][1].x,
                                             (int) DS.arrow[j][i][1].y,
                                             (int) DS.arrow[j][i][2].x,
                                             (int) DS.arrow[j][i][2].y);  
                    } // Desenha flecha
                }// se tem aresta
            }//for j
        }//for i
    } else if (G->type == GRAPH) {
        /* Writes the edges */
        for (i = 0; i < G->size; i++) {
            for (j = i; j < G->size; j++) {
                if (G->edge[i][j]) {
                    fprintf(f, "newpath %d %d moveto\n",
                                  (int) G->vertex[i].x, (int) G->vertex[i].y);
                    fprintf(f, "%d %d %d %d %d %d curveto\n",
                                  (int) G->prop[i][j].ctrlpoints[CTR1][X],
                                  (int) G->prop[i][j].ctrlpoints[CTR1][Y],
                                  (int) G->prop[i][j].ctrlpoints[CTR2][X],
                                  (int) G->prop[i][j].ctrlpoints[CTR2][Y],
                                  (int) G->vertex[j].x, (int) G->vertex[j].y);
                    fprintf(f, "stroke\n");

                }// se tem aresta
            }//for j
        }//for i

    } else {
        fprintf(stderr, "Tipo inválido de grafo\n");
    }

    /* Write the vertices */
    for (i = 0; i < G->size; i++) {
        fprintf(f, "newpath\n");
        color = Code2Rgb(G->vertex[i].color);
        fprintf(f, "%g %g %g setrgbcolor\n", color->r/255.0, 
                                             color->g/255.0, 
                                             color->b/255.0);
        fprintf(f, "%d %d 5 5 0 360 ellipse\n", 
                         (int) G->vertex[i].x, (int) G->vertex[i].y);
        fprintf(f, "fill\n");
        free(color);
    }

    /* Closes the file */
    fprintf(f, "showpage\n");

    fclose (f);
    return 1;
}


char *read_label(char *s){
int p;    /* Position */
int i;    /* Output size and index */
char *r;  /* Result string */

	/* Calculate result string size */
    p = 0;
    while (s[p] != '\"')
        p++;
    i = 0;
    p++;
    while (s[p] != '\"'){
        p++;
        i++;
    }

    if (i == 0)
        return NULL;

	/* Return result string */
    r = (char *) malloc((p+1) * sizeof(char));
    p = 0;
    while (s[p] != '\"')
        p++;
    p++;
    i = 0;
    while (s[p] != '\"'){
        r[i] = s[p];
        p++;
        i++;
    }
    r[i] = 0;

    return r;
}


/* ******* */
/* * End * */
/* ******* */
