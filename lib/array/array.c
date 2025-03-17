/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** array.c
*/

#include "../../include/safe_array.h"
#include "../../include/lib.h"
#include <stdlib.h>
#include <string.h>

static void array_ctor_allocation(Array_t **self)
{
    if ((*self)->length != 0) {
        (*self)->tab = malloc(sizeof(Object_t *) * (*self)->size * (*self)->length);
        return;
    }
    (*self)->tab = malloc(sizeof(Object_t *) * (*self)->size);
}

static void array_ctor(Array_t *self, va_list *args)
{
    if (!args) {
        raise_error("array_ctor", "ich habe no arguments gefunden....");
    }
    self->size = va_arg(*args, size_t);
    self->length = va_arg(*args, size_t);
    array_ctor_allocation(&self);
}

static void array_dtor(Array_t *self)
{
    if (self->tab) {
    }
}

void array_from_file(Array_t *array, const char *restrict filename)
{
    (void)array;
    (void)filename;
    return;
}

static const Array_t array_description = {
    .base = {
        .__size__ = sizeof(Array_t),
        .__name__ = "Array",
        .__ctor__ = (void (*)(void *, va_list *))array_ctor,
        .__dtor__ = (void (*)(void *))array_dtor,
    },
    .tab = NULL,
    .length = 0,
    .size = 0,
    .from_file = &array_from_file
};

const Class_t *Array_Class = (const Class_t *)&array_description;
