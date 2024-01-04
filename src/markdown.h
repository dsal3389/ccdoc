#ifndef _MARKDOWN_H_
#define _MARKDOWN_H_ 1


#include "linkedls.h"
#include "dynstr.h"


#define MARKDOWN_HEADER_IDENTIFIER '#'


/// defines the header level to use for the markdown, 
/// level1 = #
/// level2 = ## etc...
enum MARKDOWN_HEADERS_LEVEL {
    MKDN_HDR_LVL_1 = 1,
    MKDN_HDR_LVL_2 = 2,
    MKDN_HDR_LVL_3 = 3,
    MKDN_HDR_LVL_4 = 4,
};

struct MarkdownTocEntry {
    enum MARKDOWN_HEADERS_LEVEL level;
    const char *title;
};

typedef struct {
    NodeList toc;
    dynstr str;
} Markdown;


void markdown_initilize(Markdown *);
void markdown_add_title(Markdown *,  enum MARKDOWN_HEADERS_LEVEL, const char *, int);
void markdown_add_text(Markdown *, const char *);
void markdown_free(Markdown *);

#endif
