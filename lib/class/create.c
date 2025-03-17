/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** create.c
*/

#include "../../include/interface.h"
#include "../../include/lib.h"
#include <string.h>
#include <stdlib.h>

/*
 * safe allocates a pointer. example:
 * void *ptr = NULL;
 * const size_t size = 16;
 *
 * safe_alloc(&ptr, size);
*/
void safe_alloc(Object_t **ptr, const size_t size)
{
    *ptr = malloc(size * sizeof(Object_t *));
    if (!*ptr) {
        raise_error("safe_alloc", "malloc failed!");
    }
}

/*
 * abstract create for all Class that inherit from Class_t.
 * call its interface __ctor__
 *
 * example:
 * create(String_Class, "Hello, World");
 * create(Array_Class, sizeof(int *), 10);
 */
Object_t *create(const Class_t *restrict class_type, ...)
{
    Object_t *obj = NULL;
    va_list args;

    if (!class_type) {
        raise_error("create", "invalid class type!");
    }
    safe_alloc(&obj, class_type->__size__);
    memcpy(obj, class_type, class_type->__size__);
    if (class_type->__ctor__) {
        va_start(args, class_type);
        class_type->__ctor__(obj, &args);
        va_end(args);
    }
    return obj;
}
