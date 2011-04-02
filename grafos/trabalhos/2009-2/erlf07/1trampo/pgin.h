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


/* ********** */
/* * pgin.h * */
/* ********** */

#ifndef __PGIN_H__
#define __PGIN_H__


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define PGIN_LIST_END    0
#define PGIN_TEST_ALG    1
#define PGIN_RESULT_ALG  2
#define PGIN_STEP_ALG    3
#define PGIN_TRANSF_ALG  4
#define PGIN_SEARCH_ALG  5

#define PGIN_FLAG_REDRAWASCIRCLE 0
#define PGIN_FLAG_NOREDRAW 1
#define PGIN_FLAG_REDRAWWITHCENTEREDVERTEX 2



typedef struct pgin {
    int type;
    char *label;
    char *name;
    int flags;
} Pgin;


int pgin_read_int(char *name, char *label,
        int def, int min, int max, int inc);
double pgin_read_double(char *name, char *label,
        double def, double min, double max, double inc, int digits);
char *pgin_read_string(char *name, char *label, char *def, int max_len);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __PGIN_H__ */

/* ******* */
/* * End * */
/* ******* */
