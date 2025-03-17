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

static void array_ctor(Array_t *self, va_list *args)
{
    const size_t element_size = va_arg(*args, size_t);
    const size_t count = va_arg(*args, size_t);

    self->length = count;
    self->size = element_size * count;
    self->tab = malloc(sizeof(Object_t *) * count);
    if (self->tab == NULL) {
        raise_error("array_ctor", "malloc failed");
    }
    console_log(stdout, "size: %ld\n", self->size);
    for (size_t i = 0; i < self->length; ++i) {
        self->tab[i] = NULL;
    }
}

static void array_dtor(Array_t *self)
{
    if (!self->tab) {
        return;
    }
    for (size_t i = 0; i < self->length; ++i) {
        if (!self->tab[i]) {
            break;
        }
        safe_free((void **)&(self->tab[i]));
    }
    safe_free((void **)&self->tab);
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
