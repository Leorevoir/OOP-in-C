/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** iterator.h
*/

#ifndef ITERATOR_CLASS_H_
    #define ITERATOR_CLASS_H_

    #include "interface.h"
    #include <stddef.h>
    #include <stdbool.h>

typedef struct Iterator_s Iterator_t;

/*
 * Iterator interface base class
 *
 * .next(it) -> return Object_t *
 * .prev(it) -> return Object_t *
 * .end(it) -> return bool
 * .rewind(it) -> makes index = 0
 */

struct Iterator_s {
    Class_t base;
    Object_t *object;
    size_t index;
    /* methods */
    Object_t *(*next)(Iterator_t *self);
    Object_t *(*prev)(Iterator_t *self);
    bool (*end)(Iterator_t *self);
    void (*rewind)(Iterator_t *self);
};

void iterator_rewind(Iterator_t *self);

#endif /* ITERATOR_CLASS_H_ */
