#ifndef CPLUS_OOP_H_
#define CPLUS_OOP_H_

#include <oop/macros.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    const char *ptr;
    size_t len;
} StrView;

void sv_show(const StrView sv);
void sv_copy(char *out_buff, size_t buf_size, const StrView sv);

__cplus__const size_t hash_str(const char *s);
__cplus__const size_t sv_hash(const void *key);

#endif /* CPLUS_OOP_H_ */
