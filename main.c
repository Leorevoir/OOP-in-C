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

/*
* showcases how array works with different types
* using Iterator for safe loop and printf
*/
static void debug_print_array(Array_t *array)
{
    Object_t *data = NULL;
    Iterator_t *it = &array->it;

    while (!it->end(it)) {
        data = array->get(array, it->index);
        switch (it->index) {
            case 0:
                console_log(stdout, "Array[%zu] = %s\n", it->index, (char *)data);
                break;
            case 1:
                console_log(stdout, "Array[%zu] = %d\n", it->index, *(int *)data);
                break;
            case 2:
                console_log(stdout, "Array[%zu] = %.2f\n", it->index, *(float *)data);
                break;
            default:
                console_log(stdout, "Array[%zu] = (unknown type)\n", it->index);
                break;
        }
        it->next(it);
    }
}

/*
* showcases how array works with different types
* dynamically allocated in the same array!
*/
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

/*
* showcases on how you iterate through String using Iterator
*/
static void example_string(String_t *string)
{
    Iterator_t *it = &string->it;
    char c = 0;

    while (!it->end(it)) {
        c = (char)(size_t)it->next(it);
        console_log(stdout, "Character: %c", c);
    }
    string->from_file(string, "main.c");
}

/*
* no free required in main, all is handle by Garbage Collector !
*/
int main(void)
{
    ARRAY array = create(Array_Class, sizeof(Object_t *), 3);
    STRING string = create(String_Class, "Hellooooo Night City!!!!");

    example_string(string);
    example_array(array);
    return SUCCESS;
}

