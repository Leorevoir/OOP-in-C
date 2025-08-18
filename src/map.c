#include "error/assert.h"
#include "memory/allocate.h"
#include <oop/map.h>

__cplus__used static void map_ctor(void *instance, va_list *args);
__cplus__used static void map_dtor(void *instance);

// clang-format off
static const Class __cplus__used map_class = {
    .__size__ = sizeof(Map),
    .__name__ = "Map",
    .__ctor__ = map_ctor,
    .__dtor__ = map_dtor,
};
// clang-format on

/**
* public
*/

__cplus__const __cplus__used const Class *MapGetClass(void)
{
    return &map_class;
}

/**
 * private
 */

static void map_ctor(void *instance, va_list *args)
{
    Map *self = (Map *) instance;

    self->class = MapClass;
    self->key = NULL;
    self->data = NULL;
    self->size = 0;
    self->capacity = 0;

    const size_t capacity = va_arg(*args, size_t);
    if (capacity > 0) {
        self->capacity = capacity;
        allocate(self->key, capacity);
        allocate(self->data, capacity);
    }
}

static void map_dtor(void __cplus__unused *instance)
{
    /* dtor */
}
