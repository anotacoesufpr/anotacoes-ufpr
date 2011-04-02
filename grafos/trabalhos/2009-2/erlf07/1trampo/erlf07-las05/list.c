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
/* * list.c * */
/* ********** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define UNEFFICIENT_TESTS

/* 
 * Returns a noninitialized pointer to a list.
 * In other words: front end to malloc.
 */
List *CreateList(void) {
List *l;

    l = (List *) malloc (sizeof(List));
    return l;
}

/* Initialize a list */
void InitList(List *list) {

    list->size = 0;
    list->head = NULL;    
    list->tail = NULL;    
}

/* Pack data in a node */
Node MakeNode(void *data, int size) {
Node n;
void *tmp;

    n = (Node) malloc (sizeof(struct node));
    tmp = (void *) malloc (sizeof(size));
    memcpy(tmp, data, size);
    n->data = (void *) tmp;
    
    n->size = size;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/* Free node */
void DestroyNode(Node n) {

    free(n->data);
    n->size = 0;
    n->prev = NULL;
    n->next = NULL;
}

/* Insert node in list*/
void InsertNode(List *list, Node node) {

#ifdef UNEFFICIENT_TESTS
    if ((list->head == NULL) && (list->size != 0)) {
        printf("Inconsistent List: list->head == NULL in non empty list\n");
        exit(1);
    } else if ((list->tail == NULL) && (list->size != 0)) {
        printf("Inconsistent List: list->tail == NULL in non empty list\n");
        exit(1);
    } else if ((list->head == NULL) && (list->tail != NULL)) {
        printf("Inconsistent List: non empty list without head!\n");
        exit(1);
    } else if ((list->tail == NULL) && (list->head != NULL)) {
        printf("Inconsistent List: non empty list without tail!\n");
        exit(1);
   }
#endif
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        list->head->prev = NULL;
        list->head->next = NULL;
        
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = NULL;
        list->tail = node;
    }

    list->size++;
    
}

/* Remove a node and returns a pointer to node->next. 
 * Precondition: node is in list */
Node RemoveNode(List *list, Node node) {
Node NextNode;

    if (node == NULL) {
        printf("Warning: Trying to remove NULL node in list\n");
        return NULL;
    }
    
    if ((list->head == list->tail) && (list->head == node)) {
        list->head = NULL;   
        list->tail = NULL;
                
    } else if (node == list->head) {
        list->head = node->next;
        node->next->prev = NULL;
    
    } else if (node == list->tail) {
        list->tail = node->prev;
        list->tail->next = NULL;
    
    } else {
#ifdef UNEFFICIENT_TESTS
        if (node->prev == NULL) {
            printf("Inconsistent List: no head node and (node->prev==NULL)\n");
            printf("Node not removed!\n");
            return NULL;
        }
        if ((node->prev == NULL) || (node->prev->next != node)) {
            printf("Inconsistent List: (node->prev->next != node)\n");
            printf("Node not removed!\n");
            return NULL;
        }
        if (node->next == NULL) {
            printf("Inconsistent List: no tail node and (node->next==NULL)\n");
            printf("Node not removed!\n");
            return NULL;
        }
        if ((node->next == NULL) || (node->next->prev != node)) {
            printf("Inconsistent List: (node->next->prev != node)\n");
            printf("Node not removed!\n");
            return NULL;
        }

#endif
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
   
    list->size--;
    NextNode = node->next;
    
    free(node);

    return NextNode;
}

/* */
Node ListSearch(List *list, void *query, int size) {
Node tmp;

    tmp = list->head;
    while (tmp != NULL) {
        if (!memcmp(tmp->data, query, size)) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


#if 0
// tem q ver pra deixar igual a copy e a move...
/*  l2 in l1. l1 must be initialized. (l1 = l1 + l2) */
void AppendList(List *l1, List *l2) {
Node tmp, tmp_next;

    tmp = l2->head;

    while (l2->size != 0) {
        InsertNode(l1, tmp);
        tmp_next = tmp->next;
        RemoveNode(l2, tmp)
		tmp = tmp_next;
    }

}

/*  l2 in l1. l1 must be initialized. (l1 = l1 + l2) */
void AppendAndDestroyList(List *l1, List *l2) {
Node tmp, tmp_next;

    tmp = l2->head;

    while (l2->size != 0) {
        InsertNode(l1, tmp);
        tmp_next = tmp->next;
        RemoveNode(l2, tmp)
		tmp = tmp_next;
    }

}

#endif

/* Copy l2 in l1. l1 must be initialized. (l1 = l2) 
 * After this operation you can modify the two list
 * without worry about interference between them.
 * Of course, if the contend of the node->data is a
 * pointer you should be aware of the consequences */ 
void CopyList(List *l1, List *l2) {
Node tmp, node;
void *data;

    /* Clear l1 if necessary */
    CleanList(l1);
    
    tmp = l2->head;
    while (tmp != NULL) {
        data = (void*) malloc (sizeof(tmp->size));
        memcpy(data, tmp->data, tmp->size);
        node = MakeNode(data, tmp->size);
        InsertNode(l1, node);
        tmp = tmp->next;
    }

}

/* Copy l2 in l1 and destroy l2. l1 must be initialized. (l1 = l2) */
void MoveList(List *l1, List *l2) {
Node tmp;

    /* Clear l1 if necessary */
    tmp = l1->head;
    while (tmp != NULL) {
        RemoveNode(l1, tmp);
    }

    /* Copy */
    tmp = l2->head;
    while (tmp != NULL) {
        InsertNode(l1, tmp);
        tmp = tmp->next;
    }
   
    l2->size = 0;
    l2->head = NULL;
    l2->tail = NULL;

}

void CleanList(List *list) {
Node tmp;

    tmp = list->head;
    while (tmp != NULL) {
        /* Remember, RemoveNode() will remove tmp and 
           return a point to next node */
        tmp = RemoveNode(list, tmp);
    }

}


Stack *CreateStack(void) {
Stack *stk;

    stk = (Stack *) malloc (sizeof(Stack));
    return stk;
}


void InitStack(Stack *stk) {
   
    stk->size = 0;
    stk->top = NULL;    
}

void PushNode(Stack *stk, Node node) {
   
    if (stk->size == 0) {
        stk->top = node;
        stk->top->prev = NULL;
        stk->top->next = NULL;
        
    } else {
        stk->top->prev = node;
        node->next = stk->top;
        node->prev = NULL;
        stk->top = node;
    }

    stk->size++;
    
}


Node PopNode(Stack *stk) {
Node node;

    if (stk->top == NULL) {
        //printf("Warning (tam = %d)\n", stk->size);
        return NULL;
    }

    node = stk->top;

    if (stk->size == 1) {
        stk->top = NULL;
    } else { 
        stk->top = node->next;
        stk->top->prev = NULL;
    }
	
    stk->size--;
    return node;
}


void CleanStack(Stack *stk) {
Node tmp;

    while (stk->size > 0) {
        tmp = PopNode(stk);
        free(tmp);
    }

}


/* ******* */
/* * End * */
/* ******* */

