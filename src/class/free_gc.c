/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** free_gc.c
*/

#include "../../include/Interface.h"
#include <stdlib.h>

void safe_free(Object **ptr)
{
    if (!ptr || !*ptr) {
        return;
    }
    free(*ptr);
    *ptr = NULL;
}

void free_object(Object **restrict obj)
{
    Object *ptr = *obj;
    const Class *class_ptr = (const Class *)ptr;

    if (!obj || !*obj) {
        return;
    }
    if (class_ptr && class_ptr->__dtor__) {
        class_ptr->__dtor__(ptr);
    }
    safe_free(obj);
}
