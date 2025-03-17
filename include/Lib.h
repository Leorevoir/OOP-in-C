#ifndef MY_AMAZING_LIB_H
    #define MY_AMAZING_LIB_H

#include <stdio.h>

void raise_error(const char *where, const char *why);
void console_log(FILE *stream, const char *format, ...);

#endif /* MY_AMAZING_LIB_H */
