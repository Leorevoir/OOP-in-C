/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** iterator.c
*/

#include "../../include/lib.h"
#include "../../include/safe_iterator.h"
#include <stdbool.h>

/*
* creates an iterator
*/
static void iterator_ctor(Iterator_t *self, va_list *args)
{
    if (!args) {
        raise_error("iterator_ctor", "no args gefunden......");
    }
    self->object = va_arg(*args, Object_t *);
    self->index = 0;
}

/*
* forced to declare a dtor to respect the Class_t interface
* but useless here !
*/
static void iterator_dtor(
    __attribute__((unused))Iterator_t *self,
    __attribute__((unused))va_list *args)
{
    return;
}

/*
* the following are just interface
*/
static Object_t *iterator_next(__attribute__((unused))Iterator_t *self)
{
    return NULL;
}

static Object_t *iterator_prev(__attribute__((unused))Iterator_t *self)
{
    return NULL;
}

static bool iterator_end(__attribute__((unused))Iterator_t *self)
{
    return true;
}

/*
* abstract ? lol
*/
static void iterator_rewind(Iterator_t *self)
{
    self->index = 0;
}

static const Iterator_t iterator_description = {
    .base = {
        .__size__ = sizeof(Iterator_t),
        .__name__ = "Iterator",
        .__ctor__ = (void (*)(void *, va_list *))iterator_ctor,
        .__dtor__ = (void (*)(void *))iterator_dtor,
    },
    .object = NULL,
    .index = 0,
    .next = &iterator_next,
    .prev = &iterator_prev,
    .end = &iterator_end,
    .rewind = &iterator_rewind
};

const Class_t *Iterator_Class = (const Class_t *)&iterator_description;
