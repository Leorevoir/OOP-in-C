/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** types.h
*/

#ifndef CLASS_TYPES_H_
    #define CLASS_TYPES_H_

    #include "interface.h"
    #include "safe_string.h"
    #include "safe_array.h"
    #include "safe_list.h"

    /*
     * cringe coding style forces me to DEFINE UPPERCASE!!!!!!!!!
     */
    #define STRING String_t *__attribute__((cleanup(free_string)))
    #define ARRAY Array_t *__attribute__((cleanup(free_array)))
    #define LIST List_t *__attribute__((cleanup(free_list)))

/*
 * kind of attempt to "overload" `free_object` with differents ptr types
 * but without C warning it is really hard !
 */

void free_object(Object_t **obj);

static inline void free_string(String_t **ptr)
{
    free_object((void **)ptr);
}

static inline void free_array(Array_t **ptr)
{
    free_object((void **)ptr);
}

static inline void free_list(List_t **ptr)
{
    free_object((void **)ptr);
}

#endif /* CLASS_TYPES_H_ */
