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
/* * plugins.c * */
/* ************* */


#include "config.h"
#include "plugins.h"


#ifdef USE_DL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>
#include <unistd.h>
#include "alghandler.h"
#include "pgin.h"


#if 0
/* This is the previous load_plugins():
   it's a clean code, that's why it is saved here... */

void load_plugins(char *dirname){
DIR *dir;
struct dirent *dirent;
char *filename;
void *handle;
char *error;
Pgin *pgin;
Pgin *(*pgin_info)(void);
int (*test_func)(Graph *G, char *s);
int (*result_func)(Graph *G, char *s, List *arc_edges, List *verts);
int (*step_func)(Graph *G, char *s);
int (*transf_func)(Graph *G, char *s);

    dir = opendir(dirname);
    dirent = readdir(dir);
    while (dirent){
        if (!strcmp(dirent->d_name+strlen(dirent->d_name)-3,".so")){
            /* Create filename */
            filename = (char *) malloc(strlen(dirent->d_name)+
                    strlen(dirname)+2);
            strcpy(filename, dirname);
            strcat(filename, "/");
            strcat(filename, dirent->d_name);
            /* Load */ 
            /*printf("Loading '%s'... ", filename);*/
            /*fflush(stdout);*/
            handle = dlopen(filename, RTLD_LAZY);
            error = dlerror();
            if (error){
                /*printf("\n");*/
                printf("load_plugins(): %s\n", error);
            } else {
                /*printf("OK\n");*/
                pgin_info = dlsym(handle, "pgin_info");
                error = dlerror();
                if (error){
                    printf("load_plugins(): error loading pgin_info "
                           "function\n");
                    printf("load_plugins(): %s\n", error);
                } else {
                    pgin = pgin_info();
                    while (pgin->type != PGIN_LIST_END){

                        if (pgin->type == PGIN_TEST_ALG){
                            test_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error)
                                printf("load_plugins(): %s\n", error);
                            else
                                AddTestAlgorithm(test_func, pgin->label);
                        }
                        else if (pgin->type == PGIN_RESULT_ALG){
                            result_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error)
                                printf("load_plugins(): %s\n", error);
                            else
                                AddResultAlgorithm(result_func,
                                        pgin->label);
                        }
                        else if (pgin->type == PGIN_STEP_ALG){
                            step_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error)
                                printf("load_plugins(): %s\n", error);
                            else
                                AddStepAlgorithm(step_func, pgin->label);
                        }
                        else if (pgin->type == PGIN_TRANSF){
                            transf_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error)
                                printf("load_plugins(): %s\n", error);
                            else
                                AddTransformation(transf_func, pgin->label);
                        }

                        pgin++;
                    }
                    /* Don't close! */
                    /*dlclose(handle);*/
                }
            }
            /* End */
            free(filename);
        }
        dirent = readdir(dir);
    }
    closedir(dir);
}
#endif


/* Global var with plugins */
Plugins plugins;


void load_plugins(char *dirname){
DIR *dir;
struct dirent *dirent;
char *filename;
void *handle;
char *error;
Pgin *pgin;
Pgin *(*pgin_info)(void);
int (*test_func)(Graph *G, char *s);
int (*result_func)(Graph *G, char *s, List *arc_edges, List *verts);
int (*step_func)(Graph *G, char *s);
int (*transf_func)(Graph *G, char *s);
int (*search_func)(Graph *G, char *s, int x, List *arc_edges, List *verts);
//int i;

    /* Alocs plugins struct */
    plugins.file_count = 0;
    plugins.file_size = PGIN_MIN_COUNT;
    plugins.file = (PginFile *) malloc(plugins.file_size *
                    sizeof(PginFile));
    plugins.func_count = 0;
    plugins.func_size = PGIN_MIN_COUNT;
    plugins.func = (PginFunc *) malloc(plugins.func_size *
                    sizeof(PginFunc));

    /* Read plugins dir */
    dir = opendir(dirname);
    if (access(dirname, F_OK))
        return ;
    dirent = readdir(dir);
    while (dirent){
        if (!strcmp(dirent->d_name+strlen(dirent->d_name)-3,".so")){
            /* Create filename */
            filename = (char *) malloc(strlen(dirent->d_name)+
                    strlen(dirname)+2);
            strcpy(filename, dirname);
            strcat(filename, "/");
            strcat(filename, dirent->d_name);
            
            /* Put plugin file information */
            if (plugins.file_count >= plugins.file_size){
                plugins.file_size *= 2;
                plugins.file = (PginFile *) realloc(plugins.file,
                                plugins.file_size * sizeof(PginFile));
            }
            plugins.file[plugins.file_count].name = (char *)
                    malloc(strlen(filename)+1);
            strcpy(plugins.file[plugins.file_count].name, filename);
                
            /* Load */ 
            handle = dlopen(filename, RTLD_LAZY);
            error = dlerror();
            if (error){
                printf("load_plugins(): %s\n", error);
                plugins.file[plugins.file_count].status =
                        PGIN_STATUS_ERROR_OPEN;
                plugins.file[plugins.file_count].handle = 0;
                plugins.file_count++;
            } else {
                plugins.file[plugins.file_count].status =
                        PGIN_STATUS_LOADED;
                plugins.file[plugins.file_count].handle = handle;
                
                pgin_info = dlsym(handle, "pgin_info");
                error = dlerror();
                if (error){
                    printf("load_plugins(): error loading pgin_info "
                           "function\n");
                    printf("load_plugins(): %s\n", error);
                    plugins.file[plugins.file_count].status =
                            PGIN_STATUS_ERROR_INFO;
                    plugins.file_count++;
                    dlclose(handle);
                } else {
                    pgin = pgin_info();
                    while (pgin->type != PGIN_LIST_END){
                    
                        /* Put func information */
                        if (plugins.func_count >= plugins.func_size){
                            plugins.func_size *= 2;
                            plugins.func = (PginFunc *)
                                realloc(plugins.func,
                                        plugins.func_size *
                                        sizeof(PginFunc));
                        }
                        plugins.func[plugins.func_count].name = (char *)
                                malloc(strlen(pgin->name)+1);
                        plugins.func[plugins.func_count].file =
                            plugins.file[plugins.file_count].name;
                        strcpy(plugins.func[plugins.func_count].name,
                                pgin->name);
                        
                        /* Add func to algorithm list */
                        if (pgin->type == PGIN_TEST_ALG){
                            test_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error){
                                printf("load_plugins(): %s\n", error);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_ERROR_SYMBOL;
                            } else {
                                AddTestAlgorithm(test_func, pgin->label, 1,
                                        pgin->flags);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_LOADED;
                            }
                            plugins.func_count++;
                        }
                        else if (pgin->type == PGIN_RESULT_ALG){
                            result_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error) {
                                printf("load_plugins(): %s\n", error);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_ERROR_SYMBOL;
                            } else {
                                AddResultAlgorithm(result_func,
                                        pgin->label, 1, pgin->flags);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_LOADED;
                            }
                            plugins.func_count++;
                        }
                        else if (pgin->type == PGIN_STEP_ALG){
                            step_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error) {
                                printf("load_plugins(): %s\n", error);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_ERROR_SYMBOL;
                            }
                            else {
                                AddStepAlgorithm(step_func, pgin->label,
                                        1, pgin->flags);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_LOADED;
                            }
                            plugins.func_count++;
                        }
                        else if (pgin->type == PGIN_TRANSF_ALG){
                            transf_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error) {
                                printf("load_plugins(): %s\n", error);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_ERROR_SYMBOL;
                            } else {
                                AddTransformation(transf_func,
                                        pgin->label, 1, pgin->flags);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_LOADED;
                            }
                            plugins.func_count++;
                        }
                        else if (pgin->type == PGIN_SEARCH_ALG){
                            search_func = dlsym(handle, pgin->name);
                            error = dlerror();
                            if (error) {
                                printf("load_plugins(): %s\n", error);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_ERROR_SYMBOL;
                            } else {
                                AddSearchAlgorithm(search_func,
                                        pgin->label, 1, pgin->flags);
                                plugins.func[plugins.func_count].status =
                                        PGIN_STATUS_LOADED;
                            }
                            plugins.func_count++;
                        }

						

                        pgin++;
                    }

                    plugins.file_count++;
                    /* Don't close! */
                    /*dlclose(handle);*/
                }
            }
            /* End */
            free(filename);
        }
        dirent = readdir(dir);
    }
    closedir(dir);

    /* Debug */
    /* for (i = 0; i < plugins.file_count; i++)
        printf("%s: %d\n", plugins.file[i].name, plugins.file[i].status);

    for (i = 0; i < plugins.func_count; i++)
        printf("%s: %s: %d\n", plugins.func[i].name, plugins.func[i].file,
                plugins.func[i].status);*/
}


void unload_plugins(void){
int i;

    for (i = 0; i < plugins.file_count; i++)
        if (plugins.file[i].status == PGIN_STATUS_LOADED)
            dlclose(plugins.file[i].handle);
}

#else

void load_plugins(char *dirname){

    (void) dirname;

    /* Do nothing if dl library not avaliable */
}

void unload_plugins(void){
}

#endif


/* ******* */
/* * End * */
/* ******* */
