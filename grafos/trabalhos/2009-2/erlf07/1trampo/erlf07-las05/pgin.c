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


/* ********** */
/* * pgin.c * */
/* ********** */


#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pgin.h"


#ifdef GTK_IFACE

#include <gtk/gtk.h>

void gtk_iface_grab_end_click(GtkWidget *widget, gpointer user_data);

int gtk_iface_grab_end = 0;


int pgin_read_int(char *name, char *label,
        int def, int min, int max, int inc){
GtkWidget *dialog;
GtkWidget *vbox;
GtkWidget *action;
GtkWidget *lbl;
GtkWidget *spin_button;
GtkWidget *ok_button;
GtkObject *adj;
int i;

    /* Dialog */
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), name);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_policy(GTK_WINDOW(dialog), TRUE, TRUE, FALSE);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_signal_connect(GTK_OBJECT(dialog), "delete_event",
            GTK_SIGNAL_FUNC(gtk_iface_grab_end_click), NULL);

    /* Vbox */
    vbox = GTK_DIALOG(dialog)->vbox;
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(vbox);

    /* Label */
    lbl = gtk_label_new(label);
    gtk_widget_show(lbl);
    gtk_container_add(GTK_CONTAINER(vbox), lbl);

    /* Spin button */
    adj = gtk_adjustment_new(def, min, max, inc, inc, inc);
    spin_button = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, 0);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spin_button), TRUE);
    gtk_widget_show(spin_button);
    gtk_container_add(GTK_CONTAINER(vbox), spin_button);

    /* Action area */
    action = GTK_DIALOG(dialog)->action_area;
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(action);
    
    /* OK button */
    ok_button = gtk_button_new_with_label("  OK  ");
    gtk_widget_show(ok_button);
    gtk_container_add(GTK_CONTAINER(action), ok_button);
    gtk_signal_connect(GTK_OBJECT(ok_button), "clicked",
            GTK_SIGNAL_FUNC(gtk_iface_grab_end_click), NULL);

    /* Get input */
    gtk_widget_show(dialog);
    gtk_iface_grab_end = 0;

    while (!gtk_iface_grab_end){
        while (gtk_events_pending())
              gtk_main_iteration();
        usleep(10000);
    }

    /* Get value */
    i = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));
    
    /* Destroy */
    gtk_widget_destroy(lbl);
    gtk_widget_destroy(spin_button);
    gtk_widget_destroy(ok_button);
    gtk_widget_destroy(vbox);
    gtk_widget_destroy(dialog);
    //gtk_object_destroy(adj);

    return i;
}


double pgin_read_double(char *name, char *label,
        double def, double min, double max, double inc, int digits){
GtkWidget *dialog;
GtkWidget *vbox;
GtkWidget *action;
GtkWidget *lbl;
GtkWidget *spin_button;
GtkWidget *ok_button;
GtkObject *adj;
double d;

    /* Dialog */
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), name);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_policy(GTK_WINDOW(dialog), TRUE, TRUE, FALSE);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_signal_connect(GTK_OBJECT(dialog), "delete_event",
            GTK_SIGNAL_FUNC(gtk_iface_grab_end_click), NULL);

    /* Vbox */
    vbox = GTK_DIALOG(dialog)->vbox;
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(vbox);

    /* Label */
    lbl = gtk_label_new(label);
    gtk_widget_show(lbl);
    gtk_container_add(GTK_CONTAINER(vbox), lbl);

    /* Spin button */
    adj = gtk_adjustment_new(def, min, max, inc, inc, inc);
    spin_button = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, digits);
    gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spin_button), TRUE);
    gtk_widget_show(spin_button);
    gtk_container_add(GTK_CONTAINER(vbox), spin_button);

    /* Action area */
    action = GTK_DIALOG(dialog)->action_area;
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(action);
    
    /* OK button */
    ok_button = gtk_button_new_with_label("  OK  ");
    gtk_widget_show(ok_button);
    gtk_container_add(GTK_CONTAINER(action), ok_button);
    gtk_signal_connect(GTK_OBJECT(ok_button), "clicked",
            GTK_SIGNAL_FUNC(gtk_iface_grab_end_click), NULL);

    /* Get input */
    gtk_widget_show(dialog);
    gtk_iface_grab_end = 0;

    while (!gtk_iface_grab_end){
        while (gtk_events_pending())
              gtk_main_iteration();
        usleep(10000);
    }

    /* Get value */
    d = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(spin_button));
    
    /* Destroy */
    gtk_widget_destroy(lbl);
    gtk_widget_destroy(spin_button);
    gtk_widget_destroy(ok_button);
    gtk_widget_destroy(vbox);
    gtk_widget_destroy(dialog);
    //gtk_object_destroy(adj);

    return d;
}


char *pgin_read_string(char *name, char *label, char *def, int max_len){
GtkWidget *dialog;
GtkWidget *vbox;
GtkWidget *action;
GtkWidget *lbl;
GtkWidget *entry;
GtkWidget *ok_button;
char *s;
const char *z;

    /* Dialog */
    dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), name);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_policy(GTK_WINDOW(dialog), TRUE, TRUE, FALSE);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_signal_connect(GTK_OBJECT(dialog), "delete_event",
            GTK_SIGNAL_FUNC(gtk_iface_grab_end_click), NULL);

    /* Vbox */
    vbox = GTK_DIALOG(dialog)->vbox;
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(vbox);

    /* Label */
    lbl = gtk_label_new(label);
    gtk_widget_show(lbl);
    gtk_container_add(GTK_CONTAINER(vbox), lbl);

    /* Entry */
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), max_len);
    gtk_entry_set_text(GTK_ENTRY(entry), def);
    gtk_widget_show(entry);
    gtk_container_add(GTK_CONTAINER(vbox), entry);

    /* Action area */
    action = GTK_DIALOG(dialog)->action_area;
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(action);
    
    /* OK button */
    ok_button = gtk_button_new_with_label("  OK  ");
    gtk_widget_show(ok_button);
    gtk_container_add(GTK_CONTAINER(action), ok_button);
    gtk_signal_connect(GTK_OBJECT(ok_button), "clicked",
            GTK_SIGNAL_FUNC(gtk_iface_grab_end_click), NULL);

    /* Get input */
    gtk_widget_show(dialog);
    gtk_iface_grab_end = 0;

    while (!gtk_iface_grab_end){
        while (gtk_events_pending())
              gtk_main_iteration();
        usleep(10000);
    }

    /* Get value */
    z = gtk_entry_get_text(GTK_ENTRY(entry));
    s = (char *) malloc(strlen(z)+1);
    strcpy(s, z);
    
    /* Destroy */
    gtk_widget_destroy(lbl);
    gtk_widget_destroy(entry);
    gtk_widget_destroy(ok_button);
    gtk_widget_destroy(vbox);
    gtk_widget_destroy(dialog);
    
    return s;
}


void gtk_iface_grab_end_click(GtkWidget *widget, gpointer user_data){

    (void) widget;
    (void) user_data;

    gtk_iface_grab_end = 1;
}

#else

int pgin_read_int(char *name, char *label,
        int def, int min, int max, int inc){
int i;

    (void) def;
    (void) min;
    (void) max;
    (void) inc;

    printf("%s: %s\n", name, label);
    scanf("%d", &i);
    return i;
}


double pgin_read_double(char *name, char *label,
        double def, double min, double max, double inc, int digits){
double d;

    (void) def;
    (void) min;
    (void) max;
    (void) inc;
    (void) digits;
    
    printf("%s: %s\n", name, label);
    scanf("%lf", &d);
    return d;
}


char *pgin_read_string(char *name, char *label, char *def, int max_len){
char *s;

    (void) def;
    (void) max_len;
    
    s = (char *) malloc(max_len);
    printf("%s: %s\n", name, label);
    scanf("%s", s);
    return s;
}


#endif


/* ******* */
/* * End * */
/* ******* */
