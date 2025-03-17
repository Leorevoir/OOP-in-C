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

int main(void)
{
    STRING str = create(String_Class, "SALUT");
    ARRAY str_array = create(Array_Class, sizeof(char *));
    ARRAY int_array = create(Array_Class, sizeof(int *), 10);

    /*test_string(str);*/
    (void)str;
    (void)str_array;
    return SUCCESS; 
}
