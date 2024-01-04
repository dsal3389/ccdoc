#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "logger.h"


void fatal(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

