#include "../../include/Macro.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void console_log(FILE *stream, const char *restrict format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stream, format, args);
    fprintf(stream, "\n");
    va_end(args);
    fflush(stream);
}

void raise_error(const char *restrict where, const char *restrict why)
{
    console_log(stderr, "ERROR:\t%s\n\t%s\n", where, why);
    exit(ERROR);
}
