#ifndef _LINKEDLS_H_
#define _LINKEDLS_H_ 1

#include <stdlib.h>


typedef struct Node{
    void *value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t length;
} NodeList;


void linkedls_initilize_nodelist(NodeList *);
void linkedls_push_nodelist(NodeList *, void *);
void *linkedls_pop_nodelist(NodeList *);
void **linkedls_to_2d_list(NodeList *);


#endif
