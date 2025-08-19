#include <memory/allocate.h>
#include <oop/array.h>
#include <oop/map.h>

#include <stdio.h>

char *str_tmp_buff(const char *str, const size_t index)
{
    char *buff;

    allocate(buff, sizeof(char) * 20);
    sprintf(buff, "%s%zu", str, index);
    return buff;
}

void example_map(void)
{
    /** preallocate memory for 10000 elements to avoid reallocation */
    Map *map = new (MapClass, 10000);

    for (size_t i = 0; i < 10000; ++i) {
        char *key = str_tmp_buff("key", i);
        char *value = str_tmp_buff("value", i);

        map->insert(map, key, value);
    }

    __assert(map->contains(map, "key5000"), "Expected map to contain key5000");
    __assert(map->size(map) == 10000, "Expected size to be 10000, got %zu", map->size(map));
    printf("%s\n", (const char *) map->get(map, "key5000"));

    delete (map);
}

void example_array(void)
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

    __assert(array->size(array) == 3, "Expected size to be 3, got %zu", array->size(array));
}

int main(void)
{
    example_array();
    example_map();

    /** no memory leaks because every allocation is handled by our garbage collector */
    return 0;
}
