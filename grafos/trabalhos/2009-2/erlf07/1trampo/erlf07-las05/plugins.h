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


/* ************* */
/* * plugins.h * */
/* ************* */

#ifndef __PLUGINS_H__
#define __PLUGINS_H__


#define PGIN_STATUS_UNKNOWN       0
#define PGIN_STATUS_LOADED        1
#define PGIN_STATUS_ERROR_OPEN    2
#define PGIN_STATUS_ERROR_INFO    3
#define PGIN_STATUS_ERROR_SYMBOL  4


#define PGIN_MIN_COUNT  20


typedef struct pgin_file {
    int status;
    void *handle;
    char *name;
} PginFile;


typedef struct pgin_func {
    int status;
    char *name;
    char *file;
} PginFunc;


typedef struct plugins {
    int file_count;
    int file_size;
    PginFile *file;
    int func_count;
    int func_size;
    PginFunc *func;
} Plugins;


void load_plugins(char *dirname);
void unload_plugins(void);


#endif

/* ******* */
/* * End * */
/* ******* */
