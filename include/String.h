/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** string.h
*/

#ifndef STRING_CLASS_H_H
    #define STRING_CLASS_H_H

#include <stddef.h>
#include "Interface.h"

typedef struct String_s {
    Class base;
    char *value;
    size_t length;
    /* methods */
    void (*from_file)(struct String_s *, const char *);
} String_t;

void string_from_file(String_t *, const char *);

extern const Class *String_Class;

#endif /* STRING_CLASS_H_H */
