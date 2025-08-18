#include <memory/allocate.h>
#include <memory/garbage_collector.h>
#include <memory/liberate.h>

struct __gc_t *__gc_objects = NULL;

void _delete(void **obj_pp)
{
    if (!obj_pp || !*obj_pp) {
        return;
    }

    const Class *class = *(const Class **) *obj_pp;

    if (class && class->__dtor__) {
        class->__dtor__(*obj_pp);
    }

    __gc_free_ptr(obj_pp);
}

void *_new(const Class *class, ...)
{
    void *obj;
    va_list args;

    allocate(obj, class->__size__);
    va_start(args, class);
    class->__ctor__(obj, &args);
    va_end(args);
    return obj;
}

void __gc_cleanup(void)
{
    struct __gc_t *current = __gc_objects;

    while (current) {
        struct __gc_t *next = current->next;
        free(current);
        current = next;
    }
    __gc_objects = NULL;
}

__cplus__ctor static __cplus__used void __gc_initialize(void)
{
    __gc_objects = NULL;
}

__cplus__dtor static __cplus__used void __gc_finalize(void)
{
    __gc_cleanup();
}
