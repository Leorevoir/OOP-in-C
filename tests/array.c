#include <memory/garbage_collector.h>
#include <oop/array.h>

#include "tests.h"

#include <string.h>

Test(Array, array_new)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    cr_assert(array != NULL);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_new_zero_capacity)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    cr_assert(array != NULL);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_new_with_capacity)
{
    Array *array = new (ArrayClass, sizeof(size_t), 5);

    cr_assert(array != NULL);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_new_zero_elem_size, .exit_code = 84)
{
    remove_stderr();
    Array *array = new (ArrayClass, 0, 3);
    restore_stderr();
    delete (array);
}

Test(Array, array_delete)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    cr_assert(array != NULL);
    delete (array);
    cr_assert(array == NULL);
}

Test(Array, array_append)
{
    Array *array = new (ArrayClass, sizeof(size_t), 2);

    cr_assert(array != NULL);

    size_t value = 42;
    array->append(array, &value);

    cr_assert(array->size(array) == 1);
    cr_assert(*(size_t *) array->at(array, 0) == value);
    delete (array);
}

Test(Array, array_append_multiple)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    cr_assert(array != NULL);

    for (size_t i = 0; i < 5; ++i) {
        array->append(array, &i);
    }

    cr_assert(array->size(array) == 5);
    for (size_t i = 0; i < 5; ++i) {
        cr_assert(*(size_t *) array->at(array, i) == i);
    }
    delete (array);
}

Test(Array, array_append_resize)
{
    Array *array = new (ArrayClass, sizeof(size_t), 2);

    cr_assert(array != NULL);

    size_t vals[5] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < 5; ++i) {
        array->append(array, &vals[i]);
    }

    cr_assert(array->size(array) == 5);
    for (size_t i = 0; i < 5; ++i) {
        cr_assert(*(size_t *) array->at(array, i) == vals[i]);
    }
    delete (array);
}

Test(Array, array_insert_begin)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    size_t vals[3] = {1, 2, 3};

    array->append(array, &vals[1]);
    array->append(array, &vals[2]);
    array->insert(array, 0, &vals[0]);

    cr_assert(array->size(array) == 3);
    for (size_t i = 0; i < 3; ++i) {
        cr_assert(*(size_t *) array->at(array, i) == vals[i]);
    }
    delete (array);
}

Test(Array, array_insert_middle)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t vals[4] = {1, 2, 3, 4};

    array->append(array, &vals[0]);
    array->append(array, &vals[1]);
    array->append(array, &vals[3]);
    array->insert(array, 2, &vals[2]);

    cr_assert(array->size(array) == 4);
    for (size_t i = 0; i < 4; ++i) {
        cr_assert(*(size_t *) array->at(array, i) == vals[i]);
    }
    delete (array);
}

Test(Array, array_insert_end)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t vals[3] = {1, 2, 3};

    array->append(array, &vals[0]);
    array->append(array, &vals[1]);
    array->insert(array, 2, &vals[2]);

    cr_assert(array->size(array) == 3);
    for (size_t i = 0; i < 3; ++i) {
        cr_assert(*(size_t *) array->at(array, i) == vals[i]);
    }
    delete (array);
}

Test(Array, array_insert_invalid)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t val = 42;

    array->insert(array, 1, &val);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_remove_begin)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t vals[3] = {1, 2, 3};

    for (size_t i = 0; i < 3; ++i) {
        array->append(array, &vals[i]);
    }
    array->remove(array, 0);

    cr_assert(array->size(array) == 2);
    cr_assert(*(size_t *) array->at(array, 0) == 2);
    cr_assert(*(size_t *) array->at(array, 1) == 3);
    delete (array);
}

Test(Array, array_remove_middle)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t vals[4] = {1, 2, 3, 4};

    for (size_t i = 0; i < 4; ++i) {
        array->append(array, &vals[i]);
    }
    array->remove(array, 2);

    cr_assert(array->size(array) == 3);
    cr_assert(*(size_t *) array->at(array, 0) == 1);
    cr_assert(*(size_t *) array->at(array, 1) == 2);
    cr_assert(*(size_t *) array->at(array, 2) == 4);
    delete (array);
}

Test(Array, array_remove_end)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t vals[3] = {1, 2, 3};

    for (size_t i = 0; i < 3; ++i) {
        array->append(array, &vals[i]);
    }
    array->remove(array, 2);

    cr_assert(array->size(array) == 2);
    cr_assert(*(size_t *) array->at(array, 0) == 1);
    cr_assert(*(size_t *) array->at(array, 1) == 2);
    delete (array);
}

Test(Array, array_remove_invalid)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    array->remove(array, 0);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_clear_empty)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    array->clear(array);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_clear_filled)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t val = 42;

    for (size_t i = 0; i < 5; ++i) {
        array->append(array, &val);
    }
    array->clear(array);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_at_valid)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t val = 42;
    array->append(array, &val);
    cr_assert(*(size_t *) array->at(array, 0) == 42);
    delete (array);
}

Test(Array, array_at_invalid, .exit_code = 84)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    remove_stderr();
    array->at(array, 0);
    restore_stderr();
    delete (array);
}

Test(Array, array_foreach_empty)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t count = 0;

    array_foreach(array, size_t, __cplus__unused item, { count++; });
    cr_assert(count == 0);
    delete (array);
}

Test(Array, array_foreach_filled)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t vals[5] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < 5; ++i) {
        array->append(array, &vals[i]);
    }
    size_t sum = 0;
    array_foreach(array, size_t, item, { sum += *item; });
    cr_assert(sum == 15);
    delete (array);
}

Test(Array, array_with_strings)
{
    Array *array = new (ArrayClass, sizeof(char *), 0);
    const char *strs[3] = {"Hello", "World", "!"};

    for (size_t i = 0; i < 3; ++i) {
        char *dup = strdup(strs[i]);
        array->append(array, &dup);
    }

    cr_assert(array->size(array) == 3);
    for (size_t i = 0; i < 3; ++i) {
        cr_assert(strcmp(*(char **) array->at(array, i), strs[i]) == 0);
    }

    for (size_t i = 0; i < 3; ++i) {
        free(*(char **) array->at(array, i));
    }
    delete (array);
}

static void free_stored_ptr(void *elem_addr)
{
    if (elem_addr) {
        free(*(void **) elem_addr);
    }
}

Test(Array, array_with_dtor)
{
    Array *array = new (ArrayClass, sizeof(char *), 0);
    const char *strs[3] = {"Hello", "World", "!"};

    array->elem_dtor = free_stored_ptr;
    for (size_t i = 0; i < 3; ++i) {
        char *dup = strdup(strs[i]);
        array->append(array, &dup);
    }
    cr_assert(array->size(array) == 3);
    array->clear(array);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_large)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    const size_t large_size = 10000;

    for (size_t i = 0; i < large_size; ++i) {
        size_t val = (size_t) i;
        array->append(array, &val);
    }

    cr_assert(array->size(array) == large_size);
    cr_assert(*(size_t *) array->at(array, 0) == 0);
    cr_assert(*(size_t *) array->at(array, large_size - 1) == (size_t) (large_size - 1));
    delete (array);
}

Test(Array, array_resize_explicit)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    array->resize(array, 10);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_mixed_operations)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t vals[5] = {1, 2, 3, 4, 5};

    array->append(array, &vals[0]);
    array->append(array, &vals[1]);
    array->insert(array, 1, &vals[2]);
    array->remove(array, 0);
    array->append(array, &vals[3]);
    array->insert(array, 0, &vals[4]);

    cr_assert(array->size(array) == 4);
    cr_assert(*(size_t *) array->at(array, 0) == 5);
    cr_assert(*(size_t *) array->at(array, 1) == 3);
    cr_assert(*(size_t *) array->at(array, 2) == 2);
    cr_assert(*(size_t *) array->at(array, 3) == 4);
    delete (array);
}

int size_t_compare(const void *a, const void *b)
{
    return (int) (*(const size_t *) a - *(const size_t *) b);
}

Test(Array, array_sort)
{
    Array *array = new (ArrayClass, sizeof(size_t), 5);
    const size_t vals[5] = {5, 3, 1, 4, 2};

    for (size_t i = 0; i < 5; ++i) {
        array->append(array, &vals[i]);
    }

    cr_assert(array->size(array) == 5);

    array->sort(array, size_t_compare);

    cr_assert(*(size_t *) array->at(array, 0) == 1);
    cr_assert(*(size_t *) array->at(array, 1) == 2);
    cr_assert(*(size_t *) array->at(array, 2) == 3);
    cr_assert(*(size_t *) array->at(array, 3) == 4);
    cr_assert(*(size_t *) array->at(array, 4) == 5);
}

Test(Array, array_sort_empty)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    array->sort(array, size_t_compare);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_sort_single)
{
    Array *array = new (ArrayClass, sizeof(size_t), 1);
    size_t val = 42;

    array->append(array, &val);
    array->sort(array, size_t_compare);
    cr_assert(array->size(array) == 1);
    cr_assert(*(size_t *) array->at(array, 0) == 42);
    delete (array);
}

Test(Array, array_sort_invalid)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);

    array->sort(array, size_t_compare);
    cr_assert(array->size(array) == 0);
    delete (array);
}

Test(Array, array_find)
{
    Array *array = new (ArrayClass, sizeof(size_t), 5);
    const size_t vals[5] = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < 5; ++i) {
        array->append(array, &vals[i]);
    }
    size_t target = 3;

    array->sort(array, size_t_compare);
    const ssize_t index = array->find(array, &target, size_t_compare);

    cr_assert(index == 2);
    cr_assert(*(size_t *) array->at(array, (size_t) index) == target);
}

Test(Array, array_find_not_found)
{
    Array *array = new (ArrayClass, sizeof(size_t), 5);
    const size_t vals[5] = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < 5; ++i) {
        array->append(array, &vals[i]);
    }
    size_t target = 6;

    array->sort(array, size_t_compare);
    const ssize_t index = array->find(array, &target, size_t_compare);

    cr_assert(index == -1);
}

Test(Array, array_find_empty)
{
    Array *array = new (ArrayClass, sizeof(size_t), 0);
    size_t target = 42;
    const ssize_t index = array->find(array, &target, size_t_compare);

    cr_assert(index == -1);
    delete (array);
}
