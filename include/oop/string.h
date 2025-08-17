#ifndef CPLUS_OOP_H_
#define CPLUS_OOP_H_

#include <oop/macros.h>
#include <stddef.h>

typedef struct {
    const char *ptr;
    size_t len;
} StrView;

void sv_show(const StrView sv);
void sv_copy(char *out_buff, size_t buf_size, const StrView sv);

__cplus__const static __inline size_t hash_str(const char *s)
{
    size_t h = 5381;

    for (const unsigned char *p = (const unsigned char *) s; *p; ++p) {
        h = ((h << 5) + h) + *p;
    }
    return h;
}

#endif /* CPLUS_OOP_H_ */
