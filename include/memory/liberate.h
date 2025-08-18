#ifndef C_MEMORY_LIBERATE_H_
#define C_MEMORY_LIBERATE_H_

#include <memory/garbage_collector.h>
#include <oop/macros.h>
#include <stdlib.h>

static __inline void __gc_free_ptr(void **ptr_ref)
{
    if (!ptr_ref || !*ptr_ref) {
        return;
    }

    void *ptr = *ptr_ref;

    struct __gc_t *header = __gc_get_header(ptr);
    struct __gc_t **current = &__gc_objects;

    while (*current) {
        if (*current == header) {
            *current = header->next;
            break;
        }
        current = &(*current)->next;
    }

    free(header);
    *ptr_ref = NULL;
}

#define liberate(ptr) __gc_free_ptr((void **) &ptr)

#endif /* C_MEMORY_LIBERATE_H_ */
