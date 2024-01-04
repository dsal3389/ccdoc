#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dynstr.h"


static void dynstr_increase_capacity(dynstr *buffer, size_t minimun_size)
{
    size_t new_capacity = 0;

    // return because there is enough capacity for the string
    if(minimun_size == 0 || minimun_size < buffer->capacity) {
        return;
    }

    while(new_capacity < minimun_size){
        new_capacity += DYNSTR_INCREASE_CAPACITY_CHUNK_SIZE;
    }

    buffer->capacity = new_capacity;
    buffer->str = realloc(buffer->str, new_capacity);
}

void dynstr_initilize(dynstr *buffer)
{
    buffer->length = 0;
    buffer->capacity = 0;
    buffer->str = NULL;
}

void dynstr_set(dynstr *buffer, const char *s) 
{
    size_t slength = strlen(s);
    dynstr_increase_capacity(buffer, slength);
    strncpy(buffer->str, s, slength+1);
    buffer->length = slength;
}

void dynstr_append(dynstr *buffer, const char *s)
{
    size_t slength = strlen(s);
    size_t new_length = buffer->length + slength;

    dynstr_increase_capacity(buffer, new_length);
    strcat(buffer->str, s);
    buffer->length = new_length;
}

void dynstr_cat(dynstr *buffer, dynstr *buffer2)
{
    if(buffer2 == NULL || buffer2->length == 0) {
        return;
    }

    size_t new_length = buffer->length + buffer2->length;
    dynstr_increase_capacity(buffer, new_length);
    strcat(buffer->str, buffer2->str);
    buffer->length = new_length;
}

void dynstr_ncat(dynstr *buffer, const char *s, size_t count)
{
    size_t new_length = buffer->length + count + 1;

    dynstr_increase_capacity(buffer, new_length);
    strncat(buffer->str, s, count);
    buffer->str[new_length] = 0;
    buffer->length = new_length;
}

void dynstr_ncpy(dynstr *buffer, const char *s, size_t count)
{
    size_t new_length = buffer->length + count + 1;

    dynstr_increase_capacity(buffer, new_length);
    strncpy(buffer->str, s, count);
    buffer->str[new_length] = 0;
    buffer->length = new_length;
}

void dynstr_append_char(dynstr *buffer, char c)
{
    dynstr_increase_capacity(buffer, buffer->length + 1);
    buffer->str[buffer->length] = c;
    buffer->str[buffer->length+1] = 0;  // better safe then sorry
    buffer->length++;
}

size_t dynstr_copy_until_char(dynstr *buffer, const char *str, char c)
{
    const char *ptr = str;
    size_t copy_length = 0;

    while(*ptr && *ptr != c) {
        ptr++;
        copy_length++;
    }

    if(*ptr != c){
        return 0;
    }
    
    dynstr_increase_capacity(buffer, buffer->length + copy_length);
    strncat(buffer->str, str, copy_length);
    buffer->length += copy_length;
    buffer->str[buffer->length] = 0;
    return copy_length;
}

char *dynstr_deattach_str(dynstr *buffer)
{
    char *p = buffer->str;

    buffer->length = 0;
    buffer->capacity = 0;
    buffer->str = NULL;
    return p;
}

void dynstr_free(dynstr *buffer) 
{
    buffer->length = 0;
    buffer->capacity = 0;
    if(buffer->str != NULL) {
        free(buffer->str);
    }
}
