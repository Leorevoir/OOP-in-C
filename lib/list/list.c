/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** List.c
*/

#include "../../include/safe_list.h"
#include "../../include/lib.h"
#include <string.h>

static void list_create_blocks(Node_list_t **blocks)
{
    Node_list_t *node = NULL;

    safe_alloc((Object_t **)&node, sizeof(Node_list_t));
    node->object = NULL;
    node->next = *blocks;
    node->prev = NULL;
    *blocks = node;
}

static void list_ctor(List_t *self, va_list *args)
{
    const size_t element_size = va_arg(*args, size_t);
    const size_t count = va_arg(*args, size_t);

    self->size = element_size * count;
    self->length = 0;
    self->capacity = count;
    self->head = NULL;
    self->free_blocks = NULL;
    for (size_t i = 0; i < count; ++i) {
        list_create_blocks(&self->free_blocks);
    }
    self->it.object = (Object_t *)self;
}

static void list_dtor(List_t *self)
{
    Node_list_t *current = self->head;
    Node_list_t *next = NULL;

    while (current) {
        next = current->next;
        if (current->object) {
            safe_free(&current->object);
        }
        safe_free((Object_t **)&current);
        current = next;
    }
    current = self->free_blocks;
    while (current) {
        next = current->next;
        safe_free(&current->object);
        safe_free((Object_t **)&current);
        current = next;
    }
}

static void *list_get(List_t *self, const size_t i)
{
    Node_list_t *current = self->head;

    if (i >= self->length) {
        console_log(stderr, LIST_OOB, self->length, i);
        return NULL;
    }
    for (size_t j = 0; j < i; ++j) {
        current = current->next;
    }
    return current->object;
}

/*
* Iterator next override
*/
static void *list_it_next(Iterator_t *self)
{
    List_t *list = (List_t *)self->object;
    Node_list_t *current = list->head;

    if (self->index >= list->length) {
        return NULL;
    }
    for (size_t i = 0; i < self->index && current != NULL; ++i) {
        current = current->next;
    }
    self->index++;
    return current->object;
}

/*
* Iterator prev override
*/
static void *list_it_prev(Iterator_t *self)
{
    Node_list_t *current = (Node_list_t *)((List_t *)self->object)->head;

    if (self->index == 0) {
        return NULL;
    }
    for (size_t i = 0; i < self->index && current != NULL; ++i) {
        current = current->prev;
    }
    self->index--;
    return current->object;
}

/*
* Iterator end override
*/
static _Bool list_it_end(Iterator_t *self)
{
    const List_t *list = (List_t *)self->object;

    return self->index >= list->length;
}

static const List_t list_description = {
    .base = {
        .__size__ = sizeof(List_t),
        .__name__ = "List",
        .__ctor__ = (void (*)(void *, va_list *))list_ctor,
        .__dtor__ = (void (*)(void *))list_dtor,
    },
    .it = {
        .object = NULL,
        .prev = &list_it_prev,
        .next = &list_it_next,
        .end = &list_it_end,
        .index = 0,
    },
    .head = NULL,
    .free_blocks = NULL,
    .length = 0,
    .size = 0,
    .capacity = 0,
    .push_back = &list_push_back,
    .get = &list_get,
};

const Class_t *List_Class = (const Class_t *)&list_description;
