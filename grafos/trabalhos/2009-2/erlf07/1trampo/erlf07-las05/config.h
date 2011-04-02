/* config.h.  Generated from config.h.in by configure.  */
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


/* ************ */
/* * config.h * */
/* ************ */

#ifndef _CONFIG_H_
#define _CONFIG_H_


#define GTK_IFACE


#define HAVE_LIBGL 1
#define HAVE_LIBGLU 1
/* #undef HAVE_LIBGTKGL_2_0 */

#define HAVE_GL_GL_H 1
#define HAVE_GL_GLU_H 1
/* #undef HAVE_GTKGL_2_0_GTKGL_GTKGLAREA_H */

#if HAVE_LIBGTKGL_2_0 /* && HAVE_GTKGL_H */
#define USE_GTKGL
#endif 


#define HAVE_LIBDL 1
#define HAVE_DLFCN_H 1

#if HAVE_LIBDL && HAVE_DLFCN_H
#define USE_DL
#endif


#endif

/* ******* */
/* * End * */
/* ******* */
