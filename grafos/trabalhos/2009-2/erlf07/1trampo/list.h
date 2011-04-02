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
/* * list.h * */
/* ********** */

#ifndef __LIST_H__
#define __LIST_H__


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Node */
typedef struct node {
    void *data;
    int size; /* data size */
    struct node *next;
    struct node *prev;
} *Node;


/* List */
typedef struct list {
    int size;
    Node head;
    Node tail;
} List;


typedef struct stack {
    int size;
    Node top;
} Stack;


/* Functions */
List *CreateList(void);
void InitList(List *list);
Node MakeNode(void *data, int size);
void DestroyNode(Node n);
void InsertNode(List *list, Node node);
Node RemoveNode(List *list, Node node);
Node ListSearch(List *list, void *query, int size);
void MoveList(List *l1, List *l2);
void CleanList(List *list);
void CopyList(List *l1, List *l2);


/* Stack */
Stack *CreateStack(void); 
void InitStack(Stack *stk); 
void PushNode(Stack *stk, Node node); 
Node PopNode(Stack *stk);
void CleanStack(Stack *stk);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __LIST_H__ */

/* ******* */
/* * End * */
/* ******* */

