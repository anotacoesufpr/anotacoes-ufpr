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
/* * rc.h * */
/* ******** */

#ifndef __RC_H__
#define __RC_H__


#ifndef _STDIO_H
#include <stdio.h>
#endif


typedef struct config {
    char *dot_path;
    char *neato_path;
    char *plugins_path;
    char *datadir_path;
    int view_mode;
    char *toolbar_items;
} Config;


#define CONFIG_MAXSTRSIZE  2000
#define CONFIG_FILENAME    "graforc"


Config *read_config(void);
void write_config(Config *config);


FILE *config_read_open(char *filename);
int config_read_int(FILE *f, char *token, int *value);
int config_read_double(FILE *f, char *token, double *value);
int config_read_string(FILE *f, char *token, char **value);

FILE *config_write_open(char *filename);
int config_write_int(FILE *f, char *token, int value);
int config_write_double(FILE *f, char *token, double value);
int config_write_string(FILE *f, char *token, char *value);


#define STRIP_NEWLINE(string)\
    do\
    if (string[strlen(string)-1] == '\n')\
        string[strlen(string)-1] = 0;\
    while (0)


#endif

/* ******* */
/* * End * */
/* ******* */
