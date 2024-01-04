#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "dynstr.h"
#include "utils.h"
#include "parser.h"
#include "markdown.h"
#include "logger.h"


char *parser_map_file(struct CFileParser *parser)
{
    struct stat sb;
    int fd = open(parser->path, O_RDONLY);

    if (fd == -1){
        fatal(FMT_ERROR("fail to open file `%s`", parser->path));
    }
    if(fstat(fd, &sb) == -1){
        fatal(FMT_ERROR("failed get file information for `%s`", parser->path));
    }
    return mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
}

void parser_parse_content(struct CFileParser *parser, Markdown *mkdn, const char *content)
{
    const char *c = content;
    size_t line_length = 0;
    dynstr buffer;

    dynstr_initilize(&buffer);

    while(*c){
        while(*c == ' '){
            c++;
        }

        if(*c == '\n'){
            c++;
            continue;
        }

        if(strncmp(c, PARSER_DOCUMENT_PREFIX, sizeof(PARSER_DOCUMENT_PREFIX) - 1) != 0) {
            line_length = dynstr_copy_until_char(&buffer, c, ';');

            if(line_length > 0){
                markdown_add_title(mkdn, MKDN_HDR_LVL_2, buffer.str, 1);
                c += line_length;
            } else {
                while(*c && *c != '\n'){
                    c++;
                }
                c++;
            }
            
        } else {
            c += sizeof(PARSER_DOCUMENT_PREFIX) - 1;
            c += dynstr_copy_until_char(&buffer, c, '\n');
            c++;

            markdown_add_text(mkdn, buffer.str);
        }
        dynstr_set(&buffer, "");
    }

    printf("markdown content\n%s\n", mkdn->str.str);
}

void parser_generate_documentation(struct CFileParser *parser)
{
    Markdown markdown;
    char *content = parser_map_file(parser);

    markdown_initilize(&markdown);
    parser_parse_content(parser, &markdown, content);
    markdown_free(&markdown);
}

