#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <alloca.h>
#include <limits.h>
#include <errno.h>
#include <strings.h>
#include <sys/stat.h>
#include <dirent.h>

#include "dynstr.h"
#include "linkedls.h"
#include "parser.h"
#include "utils.h"
#include "logger.h"


#define ARGV_ENTRY_MAX 16



void print_help() 
{
    printf("help message\n");
    exit(EXIT_SUCCESS);
}


void parse_argv(int *argc, char ***argv, char ***entries_buffer) 
{
    int entries_index = 0;

    if(*argc == 0){
        fatal("missing arguments, use `-h` for help\n");
    }

    while(**argv) {
        if(***argv == '-') {
            if(strcmp(**argv, "-h") == 0 || strcmp(**argv, "--help") == 0) {
                print_help();
            } else {
                fatal("unknown argument given `%s`\n", **argv);
            }
        } else {
            if (entries_index >= ARGV_ENTRY_MAX){
                fatal("maximum allowed entries are %d which was exceeded\n", ARGV_ENTRY_MAX);
            }

            (*entries_buffer)[entries_index] = **argv;
            entries_index++;
        }
        (*argc)--;
        (*argv)++;
    }
}


char **unfold_folders(char **entries, size_t usize)
{
    struct stat sb;
    struct dirent *readdir_ptr;

    NodeList stack;
    NodeList filepaths;

    dynstr *entry = NULL;
    dynstr *path = NULL;
    DIR *dir = NULL;
    char *p = NULL;

    linkedls_initilize_nodelist(&stack);
    linkedls_initilize_nodelist(&filepaths);

    while(stack.length <= usize && entries[stack.length] != NULL){
        path = (dynstr*) alloca(sizeof(dynstr));

        dynstr_initilize(path);
        dynstr_set(path, entries[stack.length]);
        linkedls_push_nodelist(&stack, path);
    }

    while(stack.length > 0){
        path = (dynstr *) linkedls_pop_nodelist(&stack);

        if(stat(path->str, &sb) == -1){
            fatal("stat: %s: %s\n", path->str, strerror(errno));
        }

        switch(sb.st_mode & S_IFMT) {
            case S_IFDIR:
                if((dir=opendir(path->str)) == NULL) {
                    fatal("cannot open directory `%s`\n", path);
                }
                
                while((readdir_ptr=readdir(dir)) != NULL) {
                    if(strcmp(".", readdir_ptr->d_name) == 0 || strcmp("..", readdir_ptr->d_name) == 0) {
                        continue;
                    }

                    entry = (dynstr*) alloca(sizeof(dynstr));
                    dynstr_initilize(entry);
                    dynstr_set(entry, path->str);
                    dynstr_append_char(entry, '/');
                    dynstr_append(entry, readdir_ptr->d_name);
                    linkedls_push_nodelist(&stack, entry);
                }

                closedir(dir);
                break;
            case S_IFBLK:
            case S_IFREG:
            case S_IFLNK:
                p = dynstr_deattach_str(path);
                linkedls_push_nodelist(&filepaths, p);
                break;
            default:
                fprintf(stderr, "unknown file type `%s`, ignoring...\n", path->str);
                break;
        }
        dynstr_free(path);
    }
    return (char**) linkedls_to_2d_list(&filepaths);
}


void run_on_entries(char **entries, size_t usize)
{
    struct CFileParser *parser;
    char **unfolded_entries = unfold_folders(entries, usize);
    char **ptr = unfolded_entries;

    while(*ptr != NULL){
        if(!utils_str_endswith(*ptr, ".h")){
            ptr++;
            continue;
        }

        parser = alloca(sizeof(struct CFileParser));
        parser->path = *ptr;

        parser_generate_documentation(parser);
        ptr++;
    }
}


int main(int argc, char **argv) 
{
    char **argv_entries = (char**) alloca(ARGV_ENTRY_MAX*sizeof(char*));
    argc--;
    argv++;

    memset(argv_entries, 0, ARGV_ENTRY_MAX*sizeof(char*));
    parse_argv(&argc, &argv, &argv_entries);
    run_on_entries(argv_entries, ARGV_ENTRY_MAX);
}
