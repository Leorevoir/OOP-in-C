/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** main.c
*/

#include "../include/types.h"
#include <stdio.h>

int main(void)
{
    STRING str = create(String_Class, "SALUT");

    printf("%s\n", str->value);
    str->from_file(str, "Makefile");
    printf("%s\n", str->value);
    return 0;
}
