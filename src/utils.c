#include <stdlib.h>
#include <string.h>

#include "utils.h"


int utils_str_endswith(const char *str, const char *suffix)
{
    size_t suffix_length = strlen(suffix);
    size_t str_length = strlen(str);

    if(suffix_length > str_length){
        return 0;
    }

    for(int i=0; i<suffix_length; i++){
        if(str[i + str_length - suffix_length] != suffix[i]) {
            return 0;
        }
    }
    return 1;
}

off_t utils_read_until_char(const char *start, char c)
{
    const char *ptr = start;
    off_t end_index = 1;

    while(*ptr && *ptr != c){
        end_index++;
        ptr++;
    }
    return end_index;
}
