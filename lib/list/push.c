/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** List-push.c
*/

#include "../../include/safe_list.h"
#include <string.h>

/*
 * get a new node from free_blocks or allocate a new one.
 */
static node_list_t *list_get_new_node(List_t *self)
{
    Node_list_t *new_node = NULL;

    if (self->free_blocks) {
        new_node = self->free_blocks;
        self->free_blocks = self->free_blocks->next;
    } else {
        safe_alloc((Object_t **)&new_node, sizeof(Node_list_t));
    }
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

/*
 * append a node to the end of the list.
 */
void list_push_back(List_t *self, const Object_t *data, size_t data_size)
{
    Node_list_t *new_node = list_get_new_node(self);
    Node_list_t *last = NULL;

    safe_alloc(&new_node->object, data_size);
    memcpy(new_node->object, data, data_size);
    if (self->head == NULL) {
        self->head = new_node;
    } else {
        last = self->head;
        while (last->next) {
            last = last->next;
        }
        last->next = new_node;
        new_node->prev = last;
    }
    self->length++;
}
