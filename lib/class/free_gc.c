/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** free_gc.c
*/

#include "../../include/interface.h"
#include <stdlib.h>

/*
 * safer than a simple free bc set ptr to NULL
 */
void safe_free(Object_t **ptr)
{
    if (!ptr || !*ptr) {
        return;
    }
    free(*ptr);
    *ptr = NULL;
}

/*
* free an Object_t *ptr and call its __ctor__ if it is a class ptr.
* example:
*   free_object(&ptr);
*/
void free_object(Object_t **restrict obj)
{
    Object_t *ptr = *obj;
    const Class_t *class_ptr = (const Class_t *)ptr;

    if (!obj || !*obj) {
        return;
    }
    if (class_ptr && class_ptr->__dtor__) {
        class_ptr->__dtor__(ptr);
    }
    safe_free(obj);
}
