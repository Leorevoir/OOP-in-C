/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** string.c
*/

#include "../../include/safe_string.h"
#include <stdlib.h>
#include <string.h>

/*
* constructor called by Class_t parent.
*/
static void string_ctor(String_t *self, va_list *args)
{
    const char *str = va_arg(*args, const char *);

    if (str) {
        self->length = strlen(str);
        safe_alloc((Object_t **)&self->value, self->length + 1);
        if (self->value) {
            strcpy(self->value, str);
        } else {
            self->length = 0;
        }
    } else {
        self->value = NULL;
        self->length = 0;
    }
    self->it.object = self;
}

/*
* destructor called by garbage collector
*/
static void string_dtor(String_t *self)
{
    if (self->value) {
        safe_free((Object_t **)&self->value);
    }
}

static void string_change(String_t *self, const char *str)
{
    if (!str) {
        return;
    }
    if (!self->value) {
        self->value = strdup(str);
        return;
    }
    safe_free((Object_t **)&self->value);
    self->value = strdup(str);
}

/*
* Iterator prev override
*/
static void *string_it_prev(Iterator_t *self)
{
    const String_t *string = (String_t *)self->object;
    Object_t *target = NULL;

    if (self->index == 0) {
        return NULL;
    }
    target = (Object_t *)(size_t)string->value[self->index];
    self->index--;
    return target;
}

/*
* Iterator next override
*/
static void *string_it_next(Iterator_t *self)
{
    const String_t *string = (String_t *)self->object;
    Object_t *target = NULL;

    if (self->index >= string->length) {
        return NULL;
    }
    target = (Object_t *)(size_t)string->value[self->index];
    self->index++;
    return target;
}

/*
* Iterator end override
*/
static bool string_it_end(Iterator_t *self)
{
    const String_t *string = (String_t *)self->object;

    return self->index >= string->length;
}

static const String_t string_description = {
    .base = {
        .__size__ = sizeof(String_t),
        .__name__ = "String",
        .__ctor__ = (void (*)(void *, va_list *))string_ctor,
        .__dtor__ = (void (*)(void *))string_dtor
    },
    .it = {
        .object = NULL,
        .prev = &string_it_prev,
        .next = &string_it_next,
        .end = &string_it_end,
        .index = 0,
    },
    .value = NULL,
    .length = 0,
    .from_file = &string_from_file,
    .change = &string_change
};

const Class_t *String_Class = (const Class_t *)&string_description;
