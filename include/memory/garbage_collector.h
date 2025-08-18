#ifndef C_GARBAGE_COLLECTOR_H_
#define C_GARBAGE_COLLECTOR_H_

#define __gc_get_ptr(header) ((void *) ((char *) (header) + sizeof(struct __gc_t)))
#define __gc_get_header(ptr) ((struct __gc_t *) ((char *) (ptr) - sizeof(struct __gc_t)))

#include <oop/interface.h>
#include <oop/macros.h>
#include <stddef.h>

struct __gc_t {
    size_t size;
    char marked;
    struct __gc_t *next;
};

extern struct __gc_t *__gc_objects;

void __gc_cleanup(void);

#define collect_garbage __gc_cleanup();

__cplus__nodiscard void *_new(const Class *class, ...);
void _delete(void **obj_pp);

#define new(class, ...) _new(class, __VA_ARGS__)
#define delete(instance) _delete((void **) &instance);

#endif /* C_GARBAGE_COLLECTOR_H_ */
