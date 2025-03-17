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

typedef struct Array_s {
    Class_t base;
    Object_t **tab;
    size_t length;
    size_t size;
    /* methods */
    void (*from_file)(struct Array_s *, const char *);
} Array_t;

void array_from_file(Array_t *, const char *);

extern const Class_t *Array_Class;

#endif /* ARRAY_CLASS_H_H */
