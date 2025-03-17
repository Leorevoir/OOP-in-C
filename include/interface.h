/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** interface.h
*/

#ifndef INTERFACE_CLASS_H_
    #define INTERFACE_CLASS_H_

    #include <stdarg.h>
    #include <stddef.h>

typedef struct Class_s {
    const size_t __size__;
    const char *__name__;
    void (*__ctor__)(void *self, va_list *args);
    void (*__dtor__)(void *self);
} Class_t;

typedef void Object_t;

Object_t *create(const Class_t *class_type, ...);
void free_object(Object_t **obj);

/*
 * safer
 */
void safe_free(Object_t **ptr);
void safe_alloc(Object_t **ptr, const size_t size);

#endif /* INTERFACE_CLASS_H_ */
