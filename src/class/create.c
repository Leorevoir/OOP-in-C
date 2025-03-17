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

void safe_alloc(Object_t **ptr, const size_t size)
{
    Object_t *obj = malloc(size);

    if (!obj) {
        raise_error("safe_alloc", "malloc failed");
    }
    *ptr = obj;
}

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
