#ifndef _PARSER_H_
#define _PARSER_H_ 1


#define PARSER_DOCUMENT_PREFIX "///"


struct CFunctions{
    const char *function_name;
    const char *function_prototype;
    const char *description;
};

struct CFileParser {
    char *path;
};


//
void parser_generate_documentation(struct CFileParser *);


#endif
