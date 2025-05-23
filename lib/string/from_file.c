/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** from_file.c
*/

#include "../../include/safe_string.h"
#include "../../include/lib.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * as the name says
 */
static size_t get_file_size(FILE *file)
{
    long size = 0;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return (size_t)size;
}

/*
 * free current string ptr and creates a new one containing file content
 */
static void try_read_file(FILE *stream, String_t **self)
{
    const size_t size = get_file_size(stream);

    safe_free((Object_t **)&(*self)->value);
    safe_alloc((Object_t **)&(*self)->value, size + 1);
    (*self)->length = fread((*self)->value, 1, size, stream);
    if (size != (*self)->length) {
        raise_error("try_read_file", "fread failed");
    }
    (*self)->value[(*self)->length] = '\0';
}

/*
* create a string from a file!
*/
void string_from_file(String_t *self, const char *restrict filename)
{
    FILE *stream = fopen(filename, "rb");

    if (!self) {
        raise_error("string_from_file", "plz send a valid String pointer....");
    }
    if (!stream) {
        raise_error("string_from_file", "cannot open!");
    }
    try_read_file(stream, &self);
    fclose(stream);
}
