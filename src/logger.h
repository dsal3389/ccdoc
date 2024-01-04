#ifndef _LOGGER_H_
#define _LOGGER_H_ 1


#define FMT_ERROR(message, ...) "error::" message "\n", __VA_ARGS__


void fatal(char *, ...);


#endif 
