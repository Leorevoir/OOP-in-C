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
void debug_print_array(Array_t *array)
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
                console_log(stdout, "Array[%zu] = (unknown type)", it->index);
                break;
        }
        it->next(it);
    }
}

/*
* showcases how array works with different types
* dynamically allocated in the same array!
*/
void example_array(Array_t *array)
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
void example_string(String_t *string)
{
    Iterator_t *it = &string->it;
    char c = 0;

    while (!it->end(it)) {
        c = (char)(size_t)it->next(it);
        console_log(stdout, "Character: %c", c);
    }
    string->from_file(string, "main.c");
    console_log(stdout, "%s\n", string->value);
}

/*
 * showcases how List works
 * (still alpha but works with every types)
 */
typedef struct Vector_s {
    float x;
    float y;
} Vector2f_t;

static void example_list(List_t *list)
{
    Iterator_t *it = &list->it;
    Vector2f_t vec1 = {.x = 1.0f, .y = 2.0f};
    Vector2f_t vec2 = {.x = 4.0f, .y = -2.0f};
    Vector2f_t vec3 = {.x = 3.0f, .y = 0.0f};
    Vector2f_t *vec = NULL;

    list->push_back(list, &vec1, sizeof(Vector2f_t));
    list->push_back(list, &vec2, sizeof(Vector2f_t));
    list->push_back(list, &vec3, sizeof(Vector2f_t));
    while (!it->end(it)) {
        vec = (Vector2f_t *)list->get(list, it->index);
        printf("x: %.2f, y: %.2f\n", vec->x, vec->y);
        it->next(it);
    }
    it->rewind(it);
    list->pop_at(list, it->index + 1);
    while (!it->end(it)) {
        vec = (Vector2f_t *)list->get(list, it->index);
        printf("x: %.2f, y: %.2f\n", vec->x, vec->y);
        it->next(it);
    }
}

/*
* no free required in main, all is handle by Garbage Collector !
*/
int main(void)
{
    ARRAY array = create(Array_Class, sizeof(Object_t *), 3);
    STRING string = create(String_Class, "Hellooooo Night City!!!!");
    LIST list = create(List_Class, sizeof(Object_t *), 16);

    example_array(array);
    example_string(string);
    example_list(list);
    return SUCCESS;
}
