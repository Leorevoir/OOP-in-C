#include "../include/Types.h"
#include <stdio.h>

int main(void)
{
    String str = create(String_Class, "SALUT");

    printf("%s\n", str->value);
    str->from_file(str, "Makefile");
    printf("%s\n", str->value);
    return 0;
}
