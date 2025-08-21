#include <oop/string.h>

#include <stdio.h>
#include <string.h>

void sv_show(const StrView sv)
{
    for (size_t i = 0; i < sv.len; ++i) {
        putchar(sv.ptr[i]);
    }
}

void sv_copy(char *out_buff, size_t buf_size, const StrView sv)
{
    const size_t n = sv.len < (buf_size - 1) ? sv.len : (buf_size - 1);

    memcpy(out_buff, sv.ptr, n);
    out_buff[n] = '\0';
}

__cplus__const size_t hash_str(const char *s)
{
    size_t h = 5381;

    for (const unsigned char *p = (const unsigned char *) s; *p; ++p) {
        h = ((h << 5) + h) + *p;
    }
    return h;
}

__cplus__const size_t sv_hash(const void *key)
{
    const StrView *sv = key;
    size_t hash = 5381;

    for (size_t i = 0; i < sv->len; ++i) {
        hash = ((hash << 5) + hash) + (const size_t) sv->ptr[i];
    }
    return hash;
}
