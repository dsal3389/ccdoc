#ifndef _DYNSTR_H_
#define _DYNSTR_H_ 1

#include <stdlib.h>


#define DYNSTR_INCREASE_CAPACITY_CHUNK_SIZE 64


typedef struct {
    size_t length;
    size_t capacity;
    char *str;
} dynstr;


void dynstr_initilize(dynstr *);
void dynstr_set(dynstr *, const char *);
void dynstr_append(dynstr *, const char *);
void dynstr_append_char(dynstr *, char);

/*
dettaches the string from the `dynstr` management, so the `dynstr` will be empty, 
and the `dynstr_deattach_str` returns the pointer to the string which was which memory reside on the heap
*/
char *dynstr_deattach_str(dynstr *);
void dynstr_cat(dynstr *, dynstr *);
void dynstr_ncat(dynstr *, const char *, size_t);
size_t dynstr_copy_until_char(dynstr *, const char *, char);

void dynstr_free(dynstr *);

#endif
