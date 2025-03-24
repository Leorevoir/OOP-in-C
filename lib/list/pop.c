/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** list-pop.c
*/

#include "../../include/safe_list.h"
#include "../../include/lib.h"
#include <stdlib.h>

void list_pop_at(List_t *self, const size_t i)
{
    Node_list_t *current = self->head;

    if (i >= self->length) {
        console_log(stderr, LIST_OOB, self->length, i);
        return;
    }
    if (!current) {
        return;
    }
    for (size_t j = 0; j < i; ++j) {
        current = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    }
    if (current->prev) {
        current->prev->next = current->next;
    }
    self->length--;
}
