/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** main.c
*/

#include "include/types.h"
#include "include/macro.h"
#include <stdio.h>

static void test_string(String_t *str)
{
    printf("%s\n", str->value);
    str->from_file(str, "Makefile");
    printf("%s\n", str->value);
}

int main(void)
{
    STRING str = create(String_Class, "SALUT");

    return SUCCESS; 
}
