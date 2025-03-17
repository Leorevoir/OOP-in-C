/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** main.c
*/

#include "include/safe_iterator.h"
#include "include/types.h"
#include "include/macro.h"
#include <stdio.h>
#include "include/lib.h"
#include <string.h>

static void debug_print_array(Array_t *array)
{
    Object_t *data = NULL;
    Iterator_t *it = &array->it;

    while (!it->end(it)) {
        data = array->get(array, it->index);
        switch (it->index) {
            case 0:
                console_log(stdout, "Array[%zu] = %s", it->index, (char *)data);
                break;
            case 1:
                console_log(stdout, "Array[%zu] = %d", it->index, *(int *)data);
                break;
            case 2:
                console_log(stdout, "Array[%zu] = %.2f", it->index, *(float *)data);
                break;
            default:
                break;
        }
        it->next(it);
    }
}

static void example_array(Array_t *array)
{
    const char *str_literal = "salut";
    float pi = 3.14f;
    int num = 42;

    array->append(array, (char *)str_literal, strlen(str_literal) + 1);
    array->append(array, &num, sizeof(int));
    array->append(array, NULL, 0);
    array->set(array, &pi, sizeof(float), 2);
    debug_print_array(array);
}

int main(void)
{
    ARRAY array = create(Array_Class, sizeof(Object_t *), 0);

    example_array(array);
    return SUCCESS;
}
