#ifndef C_MEMORY_ALLOCATE_H_
#define C_MEMORY_ALLOCATE_H_

#include <error/assert.h>
#include <memory/garbage_collector.h>
#include <stdlib.h>

#define __gc_get_ptr(header) ((void *) ((char *) (header) + sizeof(struct __gc_t)))
#define __gc_get_header(ptr) ((struct __gc_t *) ((char *) (ptr) - sizeof(struct __gc_t)))

__cplus__nodiscard static __inline void *__gc_allocate(const size_t size)
{
    if (size == 0) {
        return NULL;
    }

    struct __gc_t *header = malloc(sizeof(struct __gc_t) + size);

    if (!header) {
        return NULL;
    }

    header->size = size;
    header->marked = 0;
    header->next = __gc_objects;
    __gc_objects = header;
    return __gc_get_ptr(header);
}

__cplus__nodiscard static __inline void *__gc_reallocate(void *ptr, const size_t size)
{
    if (!ptr) {
        return __gc_allocate(size);
    }

    if (size == 0) {
        struct __gc_t *old_header = __gc_get_header(ptr);
        struct __gc_t **current = &__gc_objects;

        while (*current) {
            if (*current == old_header) {
                *current = old_header->next;
                break;
            }
            current = &(*current)->next;
        }

        free(old_header);
        return NULL;
    }

    struct __gc_t *old_header = __gc_get_header(ptr);
    struct __gc_t **link_to_old = NULL;
    struct __gc_t **current = &__gc_objects;

    while (*current) {
        if (*current == old_header) {
            link_to_old = current;
            break;
        }
        current = &(*current)->next;
    }

    struct __gc_t *new_header = realloc(old_header, sizeof(struct __gc_t) + size);

    if (!new_header) {
        return NULL;
    }

    if (new_header != old_header && link_to_old) {
        *link_to_old = new_header;
    }

    new_header->size = size;
    return __gc_get_ptr(new_header);
}

#define allocate(object, size) __assert((object = __gc_allocate(size)) != NULL, "allocate failed")
#define reallocate(object, size) __assert((object = __gc_reallocate(object, size)) != NULL, "reallocate failed")

#define vectorize_size(x) (x ? x * 2 : 8)

#endif /* C_MEMORY_ALLOCATE_H_ */
