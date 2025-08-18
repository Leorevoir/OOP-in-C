#include <criterion/criterion.h>
#include <memory/garbage_collector.h>

#include <oop/array.h>

Test(Array, array_new)
{
    Array *array = new (ArrayClass, sizeof(int), 0);

    cr_assert(array != NULL);
}

Test(Array, array_delete)
{
    Array *array = new (ArrayClass, sizeof(int), 0);
    cr_assert(array != NULL);

    delete (array);
    cr_assert(array == NULL);
}

Test(Array, array_append)
{
    Array *array = new (ArrayClass, sizeof(int), 2);

    cr_assert(array != NULL);

    int value = 42;
    array->append(array, &value);

    cr_assert(array->size(array) == 1);
    cr_assert(*(int *) array->at(array, 0) == value);
}
