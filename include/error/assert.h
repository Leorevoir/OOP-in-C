#ifndef C_PLUS_ERROR_ASSERT_H_
#define C_PLUS_ERROR_ASSERT_H_

#include <memory/garbage_collector.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static const char *CPLUS_LOG_RED = "\033[1;31m";
static const char *CPLUS_LOG_YELLOW = "\033[0;33m";
static const char *CPLUS_LOG_MAGENTA = "\033[0;35m";
static const char *CPLUS_LOG_RESET = "\033[0m";

static __inline void __cplus__assert(const char *file, int line, const char *func, const char *fmt, ...)
{
    va_list args;

    fprintf(stderr, "%s", CPLUS_LOG_RED);
    fprintf(stderr, "ERROR:%s\n", CPLUS_LOG_RESET);
    fprintf(stderr, "\tASSERTION FAILED");
    fprintf(stderr, " in %s:%d\n", file, line);
    fprintf(stderr, "%sFUNCTION:%s\n\t(%s)\n", CPLUS_LOG_MAGENTA, CPLUS_LOG_RESET, func);

    fprintf(stderr, "%sTRACE_LOG:%s\n\t", CPLUS_LOG_YELLOW, CPLUS_LOG_RESET);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");

    collect_garbage;
    exit(84);
}

#define __assert(condition, ...)                                                                                       \
    do {                                                                                                               \
        if (!(condition)) {                                                                                            \
            __cplus__assert(__FILE__, __LINE__, __func__, __VA_ARGS__);                                                \
        }                                                                                                              \
    } while (0)

#endif /* C_PLUS_ERROR_ASSERT_H_ */
