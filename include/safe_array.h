/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** array.h
*/

#ifndef ARRAY_CLASS_H_H
    #define ARRAY_CLASS_H_H

    #include <stddef.h>
    #include "interface.h"
    #include "safe_iterator.h"
    #include <stdbool.h>

    #define ARRAY_OOB "Warning: Index %zu out of bound (length: %zu)"

typedef struct Array_s Array_t;

/*
 * .get(array, position) -> Object_t *;
 * .set(array, value, sizeof(value), position) -> bool;
 * .append(array, value, sizeof(value)) -> bool;
 */

struct Array_s {
    /* inherits */
    Class_t base;
    Object_t **tab;
    Iterator_t it;
    /* attributes */
    size_t length;
    size_t size;
    /* methods */
    void (*from_file)(Array_t *, const char *);
    Object_t *(*get)(Array_t *, const size_t);
    bool (*set)(Array_t *, const Object_t *, const size_t sz, const size_t i);
    bool (*append)(Array_t *, const Object_t *, const size_t);
};

void array_from_file(Array_t *, const char *);

extern const Class_t *Array_Class;

#endif /* ARRAY_CLASS_H_H */
