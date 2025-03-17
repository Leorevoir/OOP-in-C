/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** main.c
*/

#include "include/types.h"
#include "include/macro.h"
#include <stdio.h>
#include "include/lib.h"
#include <string.h>

static void debug_print_array(Array_t *array)
{
    Object_t *data = NULL;

    for (size_t i = 0; i < array->length; ++i) {
        data = array->get(array, i);
        if (i == 0) {
            console_log(stdout, "Array[%zu] = %s", i, (char *)data);
        } if (i == 1) {
            console_log(stdout, "Array[%zu] = %d", i, *(int *)data);
        } if (i == 2) {
            console_log(stdout, "Array[%zu] = %.2f", i, *(float *)data);
        }
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
