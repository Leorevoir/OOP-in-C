#include "../../include/String.h"
#include "../../include/Lib.h"
#include <stdlib.h>
#include <stdio.h>

static size_t get_file_size(FILE *file)
{
    long size = 0;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return (size_t)size;
}

static void try_read_file(FILE *stream, String_t *self)
{
    const size_t size = get_file_size(stream);

    safe_free((Object **)&self->value); 
    safe_alloc((Object **)&self->value, size);
    self->length = fread(self->value, 1, size, stream);
    if (size != self->length) {
        raise_error("try_read_file", "fread failed");
    }
}

void string_from_file(String_t *self, const char *restrict filename)
{
    FILE *stream = fopen(filename, "rb");

    if (!self) {
        raise_error("string_from_file", "plz send a valid String pointer....");
    }
    if (!stream) {
        raise_error("string_from_file", "cannot open!");
}
    try_read_file(stream, self);
    fclose(stream);
}
