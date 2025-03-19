/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** string.h
*/

#ifndef STRING_CLASS_H_H
    #define STRING_CLASS_H_H

    #include <stddef.h>
    #include "interface.h"
    #include "safe_iterator.h"

typedef struct String_s String_t;

/*
 * leak-free String !
 *
 * .from_file(self, filename) -> make string pointer = full file content
 */

struct String_s {
    /* inherits */
    Class_t base;
    Iterator_t it;
    /* attributes */
    char *value;
    size_t length;
    /* methods */
    void (*from_file)(String_t *, const char *);
    void (*change)(String_t *, const char *);
};

void string_from_file(String_t *self, const char *filename);

extern const Class_t *String_Class;

#endif /* STRING_CLASS_H_H */
