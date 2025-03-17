/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** types.h
*/

#ifndef CLASS_TYPES_H_
    #define CLASS_TYPES_H_

#include "Interface.h"
#include "String.h"

    #define String String_t *__attribute__((cleanup(free_string)))

void free_object(Object **obj);

static inline void free_string(String_t **ptr)
{
    free_object((void **)ptr);
}

#endif /* CLASS_TYPES_H_ */
