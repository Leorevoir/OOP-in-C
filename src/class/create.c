/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** create.c
*/

#include "../../include/Interface.h"
#include "../../include/Lib.h"
#include <string.h>
#include <stdlib.h>

void safe_alloc(Object **ptr, const size_t size)
{
    Object *obj = malloc(size);

    if (!obj) {
        raise_error("safe_alloc", "malloc failed");
    }
    *ptr = obj;
}

Object *create(const Class *restrict class_type, ...)
{
    Object *obj = NULL;
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
