#ifndef CPLUS_OOP_H_
#define CPLUS_OOP_H_

#include <stddef.h>

typedef struct {
    const char *ptr;
    size_t len;
} StrView;

void sv_show(const StrView sv);
void sv_copy(char *out_buff, size_t buf_size, const StrView sv);

#define has_str(s)                                                                                                     \
    size_t h = 5381;                                                                                                   \
    for (const unsigned char *p = (const unsigned char *) s; *p; ++p) {                                                \
        h = ((h << 5) + h) + *p;                                                                                       \
    }                                                                                                                  \
    [h]

#endif /* CPLUS_OOP_H_ */
