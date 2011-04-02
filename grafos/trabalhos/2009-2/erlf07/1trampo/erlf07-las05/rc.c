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
/* * rc.c * */
/* ******** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rc.h"


Config *read_config(void){
FILE *f;
Config *config;

    f = config_read_open(CONFIG_FILENAME);
    config = (Config *) malloc(sizeof(Config));        

    if (!f){
        config->dot_path = NULL;
        config->neato_path = NULL;
        config->plugins_path = NULL;
        config->datadir_path = NULL;
        config->view_mode = 0;
        config->toolbar_items = NULL;
    } else {
        if (!config_read_string(f, "dot_path", &(config->dot_path)))
            config->dot_path = NULL;
        else
            STRIP_NEWLINE(config->dot_path);
        if (!config_read_string(f, "neato_path", &(config->neato_path)))
            config->neato_path = NULL;
        else
            STRIP_NEWLINE(config->neato_path);
        if (!config_read_string(f, "plugins_path", &(config->plugins_path)))
            config->plugins_path = NULL;
        else
            STRIP_NEWLINE(config->plugins_path);
        if (!config_read_string(f, "datadir_path", &(config->datadir_path)))
            config->datadir_path = NULL;
        else
            STRIP_NEWLINE(config->datadir_path);
        if (!config_read_int(f, "default_view_mode", &(config->view_mode)))
            config->view_mode = 0;
        if (!config_read_string(f, "toolbar_items",
                    &(config->toolbar_items)))
            config->toolbar_items = NULL;
        else
            STRIP_NEWLINE(config->toolbar_items);
        fclose(f);
    }

    return config;
}


void write_config(Config *config){
FILE *f;

    f = config_write_open(CONFIG_FILENAME);
    if (f){
        if (config->dot_path)
            config_write_string(f, "dot_path", config->dot_path);
        if (config->neato_path)
            config_write_string(f, "neato_path", config->neato_path);
        if (config->plugins_path)
            config_write_string(f, "plugins_path", config->plugins_path);
        if (config->datadir_path)
            config_write_string(f, "datadir_path", config->datadir_path);
        config_write_int(f, "default_view_mode", config->view_mode);
        if (config->toolbar_items)
            config_write_string(f, "toolbar_items", config->toolbar_items);
        fclose(f);
    }
}


FILE *config_read_open(char *filename){
FILE *f;
char *home, *s;

    f = fopen(filename, "r");
    if (!f){
        home = getenv("HOME");
        s = (char *) malloc(strlen(home)+strlen(filename)+3);
        sprintf(s, "%s/.%s", home, filename);
        f = fopen(s, "r");
        if (!f){
            return NULL;
        }
    }

    return f;
}


int config_read_int(FILE *f, char *token, int *value){
char *string;
    
    if (config_read_string(f, token, &string)){
        (*value) = atoi(string);
        free(string);
        return 1;
    }

    return 0;
}


int config_read_double(FILE *f, char *token, double *value){
char *string;
    
    if (config_read_string(f, token, &string)){
        (*value) = atof(string);
        free(string);
        return 1;
    }

    return 0;
}


int config_read_string(FILE *f, char *token, char **value){
char *string, *res;
int i, found;

    string = (char *) malloc(CONFIG_MAXSTRSIZE * sizeof(char));
    res    = (char *) malloc(CONFIG_MAXSTRSIZE * sizeof(char));
    fseek(f, 0, SEEK_SET);
    
    found = 0;
    fgets(string, CONFIG_MAXSTRSIZE, f);
    while ((!feof(f)) && (!found)){
        if ((*string) != '#'){
            if (!strncmp(string, token, strlen(token))){
                i = strlen(token);
                while (string[i] != '=')
                    i++;
                strcpy(res, string+i+1);
                found = 1;
            }
        }
        fgets(string, CONFIG_MAXSTRSIZE, f);
    }

    if (!found){
        return 0;
    }
    
    (*value) = res;
    return 1;
}


FILE *config_write_open(char *filename){
FILE *f;
char *home, *s;

    f = fopen(filename, "r");
    if (!f){
        home = getenv("HOME");
        s = (char *) malloc(strlen(home)+strlen(filename)+3);
        sprintf(s, "%s/.%s", home, filename);
        f = fopen(s, "w");
        if (!f){
            return NULL;
        }
    } else {
        fclose(f);
        f = fopen(filename, "w");
        if (!f){
            return NULL;
        }
    }

    return f;
}


int config_write_int(FILE *f, char *token, int value){

    fprintf(f, "%s=%d\n", token, value);
    return 1;
}


int config_write_double(FILE *f, char *token, double value){

    fprintf(f, "%s=%g\n", token, value);
    return 1;
}


int config_write_string(FILE *f, char *token, char *value){

    fprintf(f, "%s=%s\n", token, value);
    return 1;
}


/* ******* */
/* * End * */
/* ******* */
