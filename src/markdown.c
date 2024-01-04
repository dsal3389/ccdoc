#include <string.h>

#include "markdown.h"
#include "dynstr.h"
#include "linkedls.h"


void markdown_initilize(Markdown *m)
{
    dynstr_initilize(&m->str);
    linkedls_initilize_nodelist(&m->toc);
}

void markdown_add_toc(Markdown *m, enum MARKDOWN_HEADERS_LEVEL level, const char *title)
{
    struct MarkdownTocEntry *toc_entry = (struct MarkdownTocEntry*) malloc(sizeof(struct MarkdownTocEntry));
    char *title_cpy = (char*) malloc((strlen(title)*sizeof(char))+1);

    strcpy(title_cpy, title);
    toc_entry->level = level;
    toc_entry->title = title_cpy;

    linkedls_push_nodelist(&m->toc, toc_entry);
}

void markdown_add_title(Markdown *m, enum MARKDOWN_HEADERS_LEVEL level, const char *title, int add_to_toc)
{
    if(add_to_toc){
        markdown_add_toc(m, level, title);
    }

    dynstr_append_char(&m->str, '\n');
    
    for(int i=0; i<level; i++){
        dynstr_append_char(&m->str, MARKDOWN_HEADER_IDENTIFIER);
    }

    dynstr_append_char(&m->str, ' ');
    dynstr_append(&m->str, title);
    dynstr_append_char(&m->str, '\n');
}

void markdown_add_text(Markdown *m, const char *text)
{
    dynstr_append_char(&m->str, '\n');
    dynstr_append(&m->str, text);
}

void markdown_free(Markdown *m)
{
    struct MarkdownTocEntry *toc_entry = NULL;

    dynstr_free(&m->str);

    while(m->toc.length){
        toc_entry = linkedls_pop_nodelist(&m->toc);
        free(toc_entry);
    }
}

