/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** list.h
*/

#ifndef LIST_CLASS_H_
    #define LIST_CLASS_H_

    #include "interface.h"
    #include "safe_iterator.h"
    #include <stddef.h>
    #include <stdbool.h>

    #define LIST_OOB "Warning: Index %zu out of bound (length: %zu)"

typedef struct List_s List_t;

/* coding style doesnt like uppercase return value */
typedef struct Node_list_s node_list_t;

/*
 * TODO: documentation
 */

typedef struct Node_list_s {
    Object_t *object;
    struct Node_list_s *next;
    struct Node_list_s *prev;
} Node_list_t;

struct List_s {
    /* inherits */
    Class_t base;
    Node_list_t *head;
    Node_list_t *free_blocks;
    Iterator_t it;
    /* attributes */
    size_t size;
    size_t length;
    size_t capacity;
    /* methods */
    void (*push_back)(List_t *self, const Object_t *data, const size_t size);
    void (*pop_at)(List_t *self, const size_t index);
    Object_t *(*get)(List_t *self, const size_t index);
};

void list_push_back(List_t *self, const Object_t *data, size_t data_size);
void list_pop_at(List_t *self, const size_t i);

extern const Class_t *List_Class;

#endif /* LIST_CLASS_H_ */
