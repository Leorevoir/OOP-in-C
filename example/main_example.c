#include <memory/allocate.h>
#include <oop/array.h>

int main(void)
{
    /** create an array of any type (can also be specific-only like const char*, int, struct...) */
    /** preallocate memory for 3 elements to avoid reallocation */
    Array *array = new (ArrayClass, sizeof(any), 3);

    /** append elements to the array */
    array->append(array, "Hello");
    array->append(array, "World");
    array->append(array, "!");

    /** for item in array do printf(item) */
    array_foreach(array, any, str, { printf("%s ", (const char *) str); });

    /** no memory leaks because every allocation is handled by our garbage collector */
    return 0;
}
