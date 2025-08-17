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
