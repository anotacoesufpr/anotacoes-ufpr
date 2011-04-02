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
/* * geometry.c * */
/* ************** */

#include <stdio.h>
#include <stdlib.h> //tirar quando o system sair
#include <math.h>
#include <unistd.h>
#include "geometry.h"
#include "graph.h"
#include "rw.h"
#include "rc.h"

//extern IsSpline;
//extern int IsDigraph;


/* Configuration (gr.c) */
extern Config *config;

char call_error[1000];

/* 
 * "Redesenha" o grafo. Chama o neato para calcular a posicao
 * de cada vertice usando o esquema de "molas" (springs).
 */

int CallNeato(Graph *G) {
char *fn_in, *fn_out;
char command[2000];

    if (config->neato_path != NULL){

        /* Get file temp names */
        fn_in = tempnam("/tmp/", "grafo");
        fn_out = tempnam("/tmp/", "grafo");

        /* Salva o grafo no tmp com formato dot/neato */
        if (!WriteDotGraph(fn_in, G)){
            sprintf(call_error, "Error writing temporary graph file!\n");
            free(fn_in);
            free(fn_out);
        }
        
        /* Chama o neato */ 
        /* Depois colocar esse system num arquivo separado, q trata de 
         * interface com o neato/dot. Num script, sei la'... */
        sprintf(command, "%s -o %s -Tplain -Nheight=.3 -Nwidth=.3 "
                "-Gstart=random -Goverlap=scale -Gsplines=true -Gsep=.5 "
                "%s", config->neato_path, fn_out, fn_in);
        system(command);
        /*system("DOTNEATO/neato -o /tmp/tmpplain.dot -Tplain -Nheight=.3 -Nwidth=.3 -Gstart=random -Goverlap=scale -Gsplines=true -Gsep=.5 /tmp/out.dot");*/
            
        /* Load the result in the graph G */
        if (!ReadPlainDotGraph(fn_out, G, G->type)){
            sprintf(call_error, "Error reading neato output file!\n");
            unlink(fn_in);
            free(fn_in);
            free(fn_out);
            return 0;
        }

        unlink(fn_in);
        unlink(fn_out);

        free(fn_in);
        free(fn_out);

        return 1;
    } else
        return 0;
}

/* 
 * "Redesenha" o grafo. Chama o dot para calcular a posicao
 * de cada vertice.
 */
int CallDot(Graph *G) {
char *fn_in, *fn_out;
char command[2000];

    if (config->dot_path != NULL){
        
        /* Get file temp names */
        fn_in = tempnam("/tmp/", "grafo");
        fn_out = tempnam("/tmp/", "grafo");

        /* Salva o grafo no tmp com formato dot/neato */
        if (!WriteDotGraph(fn_in, G)){
            sprintf(call_error, "Error writing temporary graph file!\n");
            free(fn_in);
            free(fn_out);
        }
        
        /* Chama o neato */
        sprintf(command, "%s -o %s -Tplain -Nheight=.3 -Nwidth=.3 "
                "-Gstart=random -Goverlap=scale -Gsplines=true -Gsep=.5 "
                "%s", config->dot_path, fn_out, fn_in);
        system(command);
        /*system("DOTNEATO/dot -o /tmp/tmpplain.dot -Tplain -Nheight=.3 -Nwidth=.3 -Gstart=random -Goverlap=scale -Gsplines=true -Gsep=.5 /tmp/out.dot");*/
            
        /* Load the result in the graph G */
        if (!ReadPlainDotGraph(fn_out, G, G->type)){
            sprintf(call_error, "Error reading neato output file!\n");
            unlink(fn_in);
            free(fn_in);
            free(fn_out);
            return 0;
        }
        
        unlink(fn_in);
        unlink(fn_out);

        free(fn_in);
        free(fn_out);

        //system("rm /tmp/out.dot");
        //system("rm /tmp/dot.tmp");
        
        return 1;
    } else
        return 0;
}


void RedrawAsCircle(Graph *G, int width, int height){
double x, y;
int i;
double o[2];
double t[2];
double p[2];
double angle;
double angle_cos;
double angle_sin;

    /* Initial point: 1/6 maj_dim, 1/2 min_dim */
    if (width > height){
        x = width/2;
        y = height/6;
    } else {
        x = width/6;
        y = height/6;
    }

    /* Origin */
    o[0] = width/2;
    o[1] = height/2; 

    /* Angle */
    angle = 360.0 / G->size;
    angle_cos = cos((angle / 180.0) * M_PI);
    angle_sin = sin((angle / 180.0) * M_PI);

    /* Assign point coordinates */
    G->vertex[0].x = x;
    G->vertex[0].y = y;

    for (i = 1; i < G->size; i++){
            
        /* Origin translation */
        t[0] = x - o[0];
        t[1] = y - o[1]; 

        /* Rotation */
        p[0] = t[0] * angle_cos - t[1] * angle_sin;
        p[1] = t[0] * angle_sin + t[1] * angle_cos;

        /* Back translation */
        p[0] += o[0];
        p[1] += o[1];

        /* Assigns point */
        x = p[0];
        y = p[1];
        G->vertex[i].x = x;
        G->vertex[i].y = y;
    }
}


void RedrawAsBipartite(Graph *G, int width, int height, int n1, int n2){
int i, j, x, y;

    if (width > height){
        x = width/3;
    } else {
        y = height/3;
    }

    for (i = 0, j = 1; i < n1; i++, j++){
        if (width > height){
            G->vertex[i].x = x;
            G->vertex[i].y = ((height-20)/(n1+1))*j + 10;
        } else {
            G->vertex[i].x = ((width-20)/(n1+1))*j + 10;
            G->vertex[i].y = y;
        }
    }
    
    for (i = n1, j = 1; i < n1+n2; i++, j++){
        if (width > height){
            G->vertex[i].x = x*2;
            G->vertex[i].y = ((height-20)/(n2+1))*j + 10;
        } else {
            G->vertex[i].x = ((width-20)/(n2+1))*j + 10;
            G->vertex[i].y = y*2;
        }
    }
}


void RedrawWithCenteredVertex(Graph *G, int width, int height){
double x, y;
int i;
double o[2];
double t[2];
double p[2];
double angle;
double angle_cos;
double angle_sin;

    /* Initial point: 1/6 maj_dim, 1/2 min_dim */
    if (width > height){
        x = width/2;
        y = height/6;
    } else {
        x = width/6;
        y = height/6;
    }

    /* Origin */
    o[0] = width/2;
    o[1] = height/2; 

    /* Angle */
    angle = 360.0 / (G->size-1);
    angle_cos = cos((angle / 180.0) * M_PI);
    angle_sin = sin((angle / 180.0) * M_PI);

    /* Assign point coordinates */
    G->vertex[0].x = (width/2);
    G->vertex[0].y = (height/2);
    G->vertex[1].x = x;
    G->vertex[1].y = y;

    for (i = 2; i < G->size; i++){
            
        /* Origin translation */
        t[0] = x - o[0];
        t[1] = y - o[1]; 

        /* Rotation */
        p[0] = t[0] * angle_cos - t[1] * angle_sin;
        p[1] = t[0] * angle_sin + t[1] * angle_cos;

        /* Back translation */
        p[0] += o[0];
        p[1] += o[1];

        /* Assigns point */
        x = p[0];
        y = p[1];
        G->vertex[i].x = x;
        G->vertex[i].y = y;
    }
}


void FitToWindow(Graph *G, int width, int height){
double min_x, min_y, max_x, max_y;
int i;

    /* Get graph min and max  */
    min_x = max_x = G->vertex[0].x;
    min_y = max_y = G->vertex[0].y;
    for (i = 1; i < G->size; i++){
        if (G->vertex[i].x < min_x)
            min_x = G->vertex[i].x;
        if (G->vertex[i].x > max_x)
            max_x = G->vertex[i].x;
        if (G->vertex[i].y < min_y)
            min_y = G->vertex[i].y;
        if (G->vertex[i].y > max_y)
            max_y = G->vertex[i].y;
    }

    /* Redefine vertices coordinates */
    for (i = 0; i < G->size; i++){
        G->vertex[i].x = 20 + (G->vertex[i].x - min_x)/
                (max_x - min_x)*(width-41);
        G->vertex[i].y = 20 + (G->vertex[i].y - min_y)/
            (max_y - min_y)*(height-41);
    }

}


/* Calcula pontos de controle para a spline que vai do vertice
 * x ate' o vertice y. 
 * mode: nao usado ainda 
 * A funcao verifica se precisa alterar os ctrl points simetricos
 * tambem */
void UpdateCtrlPoints(Graph *G, int x, int y, int mode) {
float x1, x2, y1, y2;
float tmpx, tmpy, oldx, oldy; // transformacao
int side = 1;
double dx, dy;

    (void) mode;

    if (y < x) {
        side = -1;
    }

    G->prop[x][y].ctrlpoints[ORG][X] = (float) G->vertex[x].x;
    G->prop[x][y].ctrlpoints[ORG][Y] = (float) G->vertex[x].y;
    G->prop[x][y].ctrlpoints[ORG][Z] = 0.0;
    
    if (G->edge[y][x]) {
        G->prop[y][x].ctrlpoints[ORG][X] = (float) G->vertex[y].x;
        G->prop[y][x].ctrlpoints[ORG][Y] = (float) G->vertex[y].y;
        G->prop[y][x].ctrlpoints[ORG][Z] = 0.0;
    }

    G->prop[x][y].ctrlpoints[DEST][X] = (float) G->vertex[y].x;
    G->prop[x][y].ctrlpoints[DEST][Y] = (float) G->vertex[y].y;
    G->prop[x][y].ctrlpoints[DEST][Z] = 0.0;

    if (G->edge[y][x]) {
        G->prop[y][x].ctrlpoints[DEST][X] = (float) G->vertex[x].x;
        G->prop[y][x].ctrlpoints[DEST][Y] = (float) G->vertex[x].y;
        G->prop[y][x].ctrlpoints[DEST][Z] = 0.0;
    }
    /* Acha os pontos "medios" */
    dx = (G->vertex[y].x - G->vertex[x].x)/16.0;
    dy = (G->vertex[y].y - G->vertex[x].y)/16.0;

    x1 = (float) G->vertex[x].x + dx;
    y1 = (float) G->vertex[x].y + dy;

    x2 = (float) G->vertex[y].x - dx;
    y2 = (float) G->vertex[y].y - dy;

    /* reta */
    G->prop[x][y].ctrlpoints[CTR1][X] = x1;
    G->prop[x][y].ctrlpoints[CTR1][Y] = y1;
    G->prop[x][y].ctrlpoints[CTR1][Z] = 0.0;

    G->prop[x][y].ctrlpoints[CTR2][X] = x2;
    G->prop[x][y].ctrlpoints[CTR2][Y] = y2;
    G->prop[x][y].ctrlpoints[CTR2][Z] = 0.0;

    if (G->edge[y][x]) {
        G->prop[y][x].ctrlpoints[CTR1][X] = x2;
        G->prop[y][x].ctrlpoints[CTR1][Y] = y2;
        G->prop[y][x].ctrlpoints[CTR1][Z] = 0.0;

        G->prop[y][x].ctrlpoints[CTR2][X] = x1;
        G->prop[y][x].ctrlpoints[CTR2][Y] = y1;
        G->prop[y][x].ctrlpoints[CTR2][Z] = 0.0;
    }

    if ((G->type == DIGRAPH) && (G->edge[y][x]) ) {
        /* spline 1 */
        /* transladando para a origem */
            oldx = G->prop[x][y].ctrlpoints[CTR1][X];
            oldy = G->prop[x][y].ctrlpoints[CTR1][Y];

            tmpx = G->prop[x][y].ctrlpoints[ORG][X] - G->prop[x][y].ctrlpoints[CTR1][X];
            tmpy = G->prop[x][y].ctrlpoints[ORG][Y] - G->prop[x][y].ctrlpoints[CTR1][Y];

            /* rotacionando 90 graus */
            G->prop[x][y].ctrlpoints[CTR1][X] = (float) tmpx * cos((side * 90.0 / 180.0) * M_PI)
                                         - tmpy * sin((side * 90.0 / 180.0) * M_PI);
            G->prop[x][y].ctrlpoints[CTR1][Y] = (float) tmpx * sin(side * 90.0 / 180.0 * M_PI)
                                         + tmpy * cos(side * 90.0 / 180.0 * M_PI);

            /* translada de volta */
            G->prop[x][y].ctrlpoints[CTR1][X] += oldx;
            G->prop[x][y].ctrlpoints[CTR1][Y] += oldy;
            G->prop[x][y].ctrlpoints[CTR1][Z] = 0.0;


            /* 2o ponto de controle */
            /* transladando para a origem */
            oldx = G->prop[x][y].ctrlpoints[CTR2][X];
            oldy = G->prop[x][y].ctrlpoints[CTR2][Y];
            tmpx = G->prop[x][y].ctrlpoints[DEST][X] - G->prop[x][y].ctrlpoints[CTR2][X];
            tmpy = G->prop[x][y].ctrlpoints[DEST][Y] - G->prop[x][y].ctrlpoints[CTR2][Y];
            /* rotacionando 90 graus */
            G->prop[x][y].ctrlpoints[CTR2][X] = (float) tmpx * cos((-side * 90.0 / 180.0) * M_PI)
                                         - tmpy * sin((-side * 90.0 / 180.0) * M_PI);
            G->prop[x][y].ctrlpoints[CTR2][Y] = (float) tmpx * sin((-side * 90.0 / 180.0) * M_PI)
                                         + tmpy * cos((-side * 90.0 / 180.0) * M_PI);

            /* translada de volta */
            G->prop[x][y].ctrlpoints[CTR2][X] += oldx;
            G->prop[x][y].ctrlpoints[CTR2][Y] += oldy;
            G->prop[x][y].ctrlpoints[CTR2][Z] = 0.0;

            /* fim da transformacao de uma spline. */
            
            /* spline 2 */
            /* transladando para a origem */
            oldx = G->prop[y][x].ctrlpoints[CTR1][X];
            oldy = G->prop[y][x].ctrlpoints[CTR1][Y];

            tmpx = G->prop[y][x].ctrlpoints[ORG][X] - G->prop[y][x].ctrlpoints[CTR1][X];
            tmpy = G->prop[y][x].ctrlpoints[ORG][Y] - G->prop[y][x].ctrlpoints[CTR1][Y];

            /* rotacionando 90 graus */
            G->prop[y][x].ctrlpoints[CTR1][X] = (float) tmpx * cos((side * 90.0 / 180.0) * M_PI)
                                         - tmpy * sin((side * 90.0 / 180.0) * M_PI);
            G->prop[y][x].ctrlpoints[CTR1][Y] = (float) tmpx * sin(side * 90.0 / 180.0 * M_PI)
                                         + tmpy * cos(side * 90.0 / 180.0 * M_PI);

            /* translada de volta */
            G->prop[y][x].ctrlpoints[CTR1][X] += oldx;
            G->prop[y][x].ctrlpoints[CTR1][Y] += oldy;
            G->prop[y][x].ctrlpoints[CTR1][Z] = 0.0;


            /* 2o ponto de controle */
            /* transladando para a origem */
            oldx = G->prop[y][x].ctrlpoints[CTR2][X];
            oldy = G->prop[y][x].ctrlpoints[CTR2][Y];
            tmpx = G->prop[y][x].ctrlpoints[DEST][X] - G->prop[y][x].ctrlpoints[CTR2][X];
            tmpy = G->prop[y][x].ctrlpoints[DEST][Y] - G->prop[y][x].ctrlpoints[CTR2][Y];
            /* rotacionando 90 graus */
            G->prop[y][x].ctrlpoints[CTR2][X] = (float) tmpx * cos((-side * 90.0 / 180.0) * M_PI)
                                         - tmpy * sin((-side * 90.0 / 180.0) * M_PI);
            G->prop[y][x].ctrlpoints[CTR2][Y] = (float) tmpx * sin((-side * 90.0 / 180.0) * M_PI)
                                         + tmpy * cos((-side * 90.0 / 180.0) * M_PI);

            /* translada de volta */
            G->prop[y][x].ctrlpoints[CTR2][X] += oldx;
            G->prop[y][x].ctrlpoints[CTR2][Y] += oldy;
            G->prop[y][x].ctrlpoints[CTR2][Z] = 0.0;
    } /* SPLINES */
    
#if 0 
    if (flag) {
        G->prop[y][x].ctrlpoints[CTR2][X] = G->prop[x][y].ctrlpoints[CTR1][X];
        G->prop[y][x].ctrlpoints[CTR2][Y] = G->prop[x][y].ctrlpoints[CTR1][Y];
        G->prop[y][x].ctrlpoints[CTR2][Z] = G->prop[x][y].ctrlpoints[CTR1][Z];

        G->prop[y][x].ctrlpoints[CTR1][X] = G->prop[x][y].ctrlpoints[CTR2][X];
        G->prop[y][x].ctrlpoints[CTR1][Y] = G->prop[x][y].ctrlpoints[CTR2][Y];
        G->prop[y][x].ctrlpoints[CTR1][Z] = G->prop[x][y].ctrlpoints[CTR2][Z];
    }
#endif 
}



void CalculateArrows(Graph *G, DrawStruct *DS) {
int i,j,k, x,y;
Point p1,p2,p,tmp;
int cx[4], cy[4];
	
    if (DS->allocated_size < G->allocated_size){
        ReAllocDrawStruct(DS, G->allocated_size);
    }

    for (i = 0; i < G->size; i++) {
        for (j = i+1; j < G->size; j++) {
            if ((G->edge[i][j])) {
                if (G->edge[j][i]) {
                    /* ida */
                    p.x = p2.x = G->vertex[j].x; 
                    p.y = p2.y = G->vertex[j].y; 
                   
                    //p1.x = G->vertex[i].x;
                    //p1.y = G->vertex[i].y;
                    //RotatePoint(&p1, p2, -16);
	
					//p1.x = G->ctrlpoints[i][j][CTR2][X];
                    //p1.y = G->ctrlpoints[i][j][CTR2][Y];
			    
                    for (k = 0; k < 4; k++){
                        cx[k] = G->prop[i][j].ctrlpoints[k][X];
                        cy[k] = 600 - G->prop[i][j].ctrlpoints[k][Y];
                    }
 
                    spline_point(3, cx, cy, &x, &y, 15);
					
					p1.x = x;// =100;
                    p1.y = y;// =100;

					
                    /* Primeiro ponto do triangulo fica a 3 pixels do 
                     * vertice de destino */
                    PointInLine(p1, p2, &tmp, 3, 1);
                    DS->arrow[i][j][0].x = tmp.x;
                    DS->arrow[i][j][0].y = tmp.y;
		    
                    PointInLine(p1, p2, &tmp, 10, 1);
                    RotatePoint(&p, tmp, 150);
                    DS->arrow[i][j][1].x = p.x;
                    DS->arrow[i][j][1].y = p.y;
                   
                    p.x = p2.x;
                    p.y = p2.y;
                    RotatePoint(&p, tmp, -150);
                    DS->arrow[i][j][2].x = p.x;
                    DS->arrow[i][j][2].y = p.y;
                    /* volta */
                    p.x = p2.x = G->vertex[i].x; 
                    p.y = p2.y = G->vertex[i].y; 
                    
                    //p1.x = G->vertex[j].x;
                    //p1.y = G->vertex[j].y;
                    //RotatePoint(&p1, p2, -16);
                  
                    //p1.x = G->ctrlpoints[j][i][CTR2][X];
                    //p1.y = G->ctrlpoints[j][i][CTR2][Y];

                    for (k = 0; k < 4; k++){
                        cx[k] = G->prop[j][i].ctrlpoints[k][X];
                        cy[k] = G->prop[j][i].ctrlpoints[k][Y];
                    }
 
                    spline_point(3, cx, cy, &x, &y, 15);

					p1.x = x;//=100;
                    p1.y = y;//=100;

					
                    /* Primeiro ponto do triangulo fica a 3 pixels do 
                     * vertice de destino */
                    PointInLine(p1, p2, &tmp, 3, 1);
                    DS->arrow[j][i][0].x = tmp.x;
                    DS->arrow[j][i][0].y = tmp.y;
		    
                    PointInLine(p1, p2, &tmp, 10, 1);
                    RotatePoint(&p, tmp, 150);
                    DS->arrow[j][i][1].x = p.x;
                    DS->arrow[j][i][1].y = p.y;
                   
                    p.x = p2.x;
                    p.y = p2.y;
                    RotatePoint(&p, tmp, -150);
                    DS->arrow[j][i][2].x = p.x;
                    DS->arrow[j][i][2].y = p.y; 
		    
                } else {
                    // so' ij
                    p.x = p2.x = G->vertex[j].x; 
                    p.y = p2.y = G->vertex[j].y; 
                    
                    //p1.x = G->vertex[i].x;
                    //p1.y = G->vertex[i].y;
    
					//p1.x = G->ctrlpoints[i][j][CTR2][X];
                    //p1.y = G->ctrlpoints[i][j][CTR2][Y];
              

                    for (k = 0; k < 4; k++){
                        cx[k] = G->prop[i][j].ctrlpoints[k][X];
                        cy[k] = G->prop[i][j].ctrlpoints[k][Y];
                    }
 
                    spline_point(3, cx, cy, &x, &y, 15);

					p1.x = x;//=100;
                    p1.y = y;//=100;


					
                    /* Primeiro ponto do triangulo fica a 3 pixels do 
                     * vertice de destino */
                    PointInLine(p1, p2, &tmp, 3, 1);
                    DS->arrow[i][j][0].x = tmp.x;
                    DS->arrow[i][j][0].y = tmp.y;
		    
                    PointInLine(p1, p2, &tmp, 10, 1);
                    RotatePoint(&p, tmp, 150);
                    DS->arrow[i][j][1].x = p.x;
                    DS->arrow[i][j][1].y = p.y;
                   
                    p.x = p2.x;
                    p.y = p2.y;
                    RotatePoint(&p, tmp, -150);
                    DS->arrow[i][j][2].x = p.x;
                    DS->arrow[i][j][2].y = p.y; 
 
                }
            } else if ((i!=j) && G->edge[j][i]) {
                p.x = p2.x = G->vertex[i].x; 
                p.y = p2.y = G->vertex[i].y; 
                    
                //p1.x = G->vertex[j].x;
                //p1.y = G->vertex[j].y;
                   
				//p1.x = G->ctrlpoints[j][i][CTR2][X];
                //p1.y = G->ctrlpoints[j][i][CTR2][Y];



                for (k = 0; k < 4; k++){
                    cx[k] = G->prop[j][i].ctrlpoints[k][X];
                    cy[k] = G->prop[j][i].ctrlpoints[k][Y];
                }
 
                spline_point(3, cx, cy, &x, &y, 15);

                p1.x = x;//=100;
                p1.y = y;//=100;

				
                /* Primeiro ponto do triangulo fica a 3 pixels do 
                 * vertice de destino */
                PointInLine(p1, p2, &tmp, 3, 1);
                DS->arrow[j][i][0].x = tmp.x;
                DS->arrow[j][i][0].y = tmp.y;
		    
                PointInLine(p1, p2, &tmp, 10, 1);
                RotatePoint(&p, tmp, 150);
                DS->arrow[j][i][1].x = p.x;
                DS->arrow[j][i][1].y = p.y;
                   
                p.x = p2.x;
                p.y = p2.y;
                RotatePoint(&p, tmp, -150);
                DS->arrow[j][i][2].x = p.x;
                DS->arrow[j][i][2].y = p.y; 
            }
        }
    }

}



/* Retorna um ponto na reta p1 p2. dist diz a distancia que o ponto
 * esta' de p1. Por exemplo: se dist e' 16, a reta e' dividida em
 * 16 segmentos e p vai ser o ponto inicial do ultimo segmento. ou
 * seja a reta p p2 tem 1/16 do tamanho de p1 p2.
 * Caso a flag seja ativada, a distancia passa a ser absoluta em
 * pixels e nao relativa. Se dist e' 16 p vai estar a distancia
 * 16 de p2.
 */
void PointInLine(Point p1, Point p2, Point *p, int dist, int flag) {
double dx, dy, size;

    dx = (p2.x - p1.x);
    dy = (p2.y - p1.y);
    
    if (!flag) {
        dx = dx/(double) dist;
        dy = dy/(double) dist;
        p->x = p2.x - dx;
        p->y = p2.y - dy;
    } else {
        /* tamanho da reta */
        size = sqrt(dx*dx + dy*dy);

        /* tipo uma regra de tres */
        dx = dist * dx/size;
        dy = dist * dy/size;
	
        p->x = p2.x - dx;
        p->y = p2.y - dy;
    }
} 

/* A famosa transformacao linear rotacao */
void RotatePoint(Point *p, Point o, int degree) {
Point old, tmp;

    /* transladando para a origem */
    old.x = o.x;
    old.y = o.y; 
    tmp.x = p->x - o.x;
    tmp.y = p->y - o.y; 

    /* rotaciona */
    p->x = tmp.x * cos((degree / 180.0) * M_PI)
         - tmp.y * sin((degree / 180.0) * M_PI);
    p->y = tmp.x * sin((degree / 180.0) * M_PI)
         + tmp.y * cos((degree / 180.0) * M_PI);

    /* translada de volta */
    p->x += old.x;
    p->y += old.y;

}

/* Returns nth point of a spline */
void spline_point(int degree,
        int *ctrl_x, int *ctrl_y, int *x, int *y, int n){
double t, delt;
int i, dx, dy, npoints;

    dx = abs(ctrl_x[degree] - ctrl_x[0])+1;
    dy = abs(ctrl_y[degree] - ctrl_y[0])+1;
    if (dx > dy)
        npoints = dx;
    else
        npoints = dy;

    delt = 1.0/npoints;
    t = 0.0;
    
    for (i = 0; i < n; i++){
        (*x) = hornbez(degree, ctrl_x, t);
        (*y) = hornbez(degree, ctrl_y, t);
        t = t + delt;
    }
}


/* Splines points */
double hornbez(int degree, int *coeff, double t){
int i, n_choose_i;
double fact, t1, aux;

    t1 = 1.0 - t;
    fact = 1.0;
    n_choose_i = 1;
    aux = ((double)coeff[0])*t1;

    for (i = 1; i < degree; i++){
        fact = fact*t;
        n_choose_i = n_choose_i * (degree-i+1)/i;
        aux = (aux + fact*n_choose_i*((double)coeff[i]))*t1;
    }

    aux = aux + fact*t*((double)coeff[degree]);

    return aux;
}





/* ******* */
/* * End * */
/* ******* */

