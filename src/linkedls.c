#include <stdlib.h>
#include <stdio.h>

#include "linkedls.h"


void linkedls_initilize_nodelist(NodeList *nls)
{
    nls -> head = NULL;
    nls -> tail = NULL;
    nls -> length = 0;
}

void linkedls_push_nodelist(NodeList *nls, void *value)
{
    Node *node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->prev = nls->tail;
    node->next = NULL;
    
    nls->tail = node;
    nls->length++;

    if(node->prev != NULL){
        node->prev->next = node;
    } else {
        nls->head = node;
    }
}

void *linkedls_pop_nodelist(NodeList *nls)
{
    Node *tail = nls->tail;
    void *p = NULL;

    if(tail == NULL){
        return NULL;
    }

    if(tail->prev != NULL){
        tail->prev->next = NULL;
        nls->tail = tail->prev;
    } else {
        nls->tail = NULL;
    }

    p = tail->value;
    nls->length--;

    free(tail);
    return p;
}

void **linkedls_to_2d_list(NodeList *nls)
{
    size_t index = 0;
    Node *node = nls->head;
    void **ls = (void**) malloc(sizeof(void*)*(nls->length+1));

    while(node != NULL){
        ls[index] = node->value;
        node = node->next;
        index++;
    }
    ls[index] = NULL;
    return ls;
}


