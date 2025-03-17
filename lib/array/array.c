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

/*
 * constructor called by Class_t parent.
 */
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
    for (size_t i = 0; i < self->length; ++i) {
        self->tab[i] = NULL;
    }
    self->it.object = (Object_t *)self;
}

/*
 * destructor called by garbage collector
 */
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

/*
 * append value at the end of the array
 *
 * example:
 *  .append(array, "SALUT", strlen("SALUT"));
 *  .append(array, &num, sizeof(int));
 *  .append(array, &float, sizeof(float));
 */
static _Bool array_append_value(
    Array_t *self, const Object_t *data, const size_t data_size)
{
    Object_t **new_tab = NULL;
    size_t new_size = 0;

    if (self->length >= self->size / sizeof(Object_t *)) {
        new_size = self->size == 0 ? sizeof(Object_t *) : self->size * 2;
        new_tab = realloc(self->tab, new_size);
        if (new_tab == NULL) {
            raise_error("array_append_value", "realloc failed");
        }
        self->tab = new_tab;
        self->size = new_size;
    }
    self->tab[self->length] = malloc(data_size);
    if (self->tab[self->length] == NULL) {
        raise_error("array_append_value", "malloc failed");
    }
    memcpy(self->tab[self->length], data, data_size);
    self->length++;
    return true;
}

/*
 * set value at index!
 *
 * example:
 *  .set(array, "SALUT", strlen("SALUT"), 3);
 *  .set(array, &num, sizeof(int), 4);
 *  .set(array, &float, sizeof(float), 2);
 */
static _Bool array_set_value(
    Array_t *self, const Object_t *data,
    const size_t data_size, const size_t i)
{
    if (i >= self->length) {
        console_log(stderr, ARRAY_OOB, i, self->length);
        return false;
    }
    if (self->tab[i] != NULL) {
        safe_free((void **)&(self->tab[i]));
    }
    self->tab[i] = malloc(data_size);
    if (self->tab[i] == NULL) {
        raise_error("array_set_value", "malloc failed");
    }
    memcpy(self->tab[i], data, data_size);
    return true;
}

/*
* get value at index !
*
* example:
*   .get(array, 2);
*/
static void *array_get_value(Array_t *self, const size_t i)
{
    if (i >= self->length) {
        console_log(stderr, ARRAY_OOB, i, self->length);
        return NULL;
    }
    return self->tab[i];
}

/*
* Iterator prev override
*/
static void *array_it_prev(Iterator_t *self)
{
    const Array_t *array = (Array_t *)self->object;
    Object_t *target = NULL;

    if (self->index == 0) {
        return NULL;
    }
    target = array->tab[self->index];
    self->index--;
    return target;
}

/*
* Iterator next override
*/
static void *array_it_next(Iterator_t *self)
{
    const Array_t *array = (Array_t *)self->object;
    Object_t *target = NULL;

    if (self->index >= array->length) {
        return NULL;
    }
    target = array->tab[self->index];
    self->index++;
    return target;
}

static bool array_it_end(Iterator_t *self)
{
    const Array_t *array = (Array_t *)self->object;

    return self->index >= array->length;
}

static const Array_t array_description = {
    .base = {
        .__size__ = sizeof(Array_t),
        .__name__ = "Array",
        .__ctor__ = (void (*)(void *, va_list *))array_ctor,
        .__dtor__ = (void (*)(void *))array_dtor,
    },
    .it = {
        .object = NULL,
        .prev = &array_it_prev,
        .next = &array_it_next,
        .end = &array_it_end,
        .index = 0,
    },
    .tab = NULL,
    .length = 0,
    .size = 0,
    .from_file = &array_from_file,
    .set = &array_set_value,
    .get = &array_get_value,
    .append = &array_append_value
};

const Class_t *Array_Class = (const Class_t *)&array_description;
