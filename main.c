/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** main.c
*/

#include "include/types.h"
#include "include/macro.h"
#include <stdio.h>

void test_string(String_t *str)
{
    printf("%s\n", str->value);
    str->from_file(str, "Makefile");
    printf("%s\n", str->value);
}

void debug_print(Array_t *array)
{
    for (size_t i = 0; i < 10; ++i) {
        printf("{%ld}\t->\t%s\n", i, (char *)array->tab[i]);
    }
}

int main(void)
{
    STRING str = create(String_Class, "SALUT");
    ARRAY str_array = create(Array_Class, sizeof(char *));
    ARRAY int_array = create(Array_Class, sizeof(int *), 10);

    debug_print(int_array);
    return SUCCESS;
}
