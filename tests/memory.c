#include <criterion/criterion.h>

#include <memory/allocate.h>
#include <memory/garbage_collector.h>
#include <memory/liberate.h>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static int stderr_fd;

static void remove_stderr(void)
{
    int devnull = open("/dev/null", O_WRONLY);
    stderr_fd = dup(STDERR_FILENO);

    dup2(devnull, STDERR_FILENO);
    close(devnull);
}

static void restore_stderr()
{
    dup2(stderr_fd, STDERR_FILENO);
    close(stderr_fd);
}

Test(__gc_t, memory_allocate)
{
    char *ptr;
    allocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);
    liberate(ptr);
}

Test(__gc_t, memory_liberate)
{
    char *ptr;
    allocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);
    liberate(ptr);
    cr_assert(ptr == NULL);
}

Test(__gc_t, memory_garbage_collector)
{
    char *ptr1, *ptr2;
    allocate(ptr1, sizeof *ptr1);
    allocate(ptr2, sizeof *ptr2);
    cr_assert(ptr1 != NULL);
    cr_assert(ptr2 != NULL);
    collect_garbage;
}

Test(__gc_t, allocate_zero_size, .exit_code = 84)
{
    void *ptr;

    remove_stderr();
    allocate(ptr, 0);
    restore_stderr();
}

Test(__gc_t, liberate_null_pointer)
{
    char *ptr = NULL;

    liberate(ptr);
    cr_assert(ptr == NULL);
}

Test(__gc_t, double_liberate)
{
    char *ptr;

    allocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);

    liberate(ptr);
    cr_assert(ptr == NULL);

    liberate(ptr);
    cr_assert(ptr == NULL);
}

Test(__gc_t, allocate_different_sizes)
{
    char *char_ptr;
    int *int_ptr;
    double *double_ptr;

    allocate(char_ptr, sizeof *char_ptr);
    allocate(int_ptr, sizeof *int_ptr);
    allocate(double_ptr, sizeof *double_ptr);

    cr_assert(char_ptr != NULL);
    cr_assert(int_ptr != NULL);
    cr_assert(double_ptr != NULL);

    liberate(char_ptr);
    liberate(int_ptr);
    liberate(double_ptr);
}

Test(__gc_t, allocate_large_block)
{
    char *large_ptr;
    const size_t large_size = 1024 * 1024;

    allocate(large_ptr, large_size);
    cr_assert(large_ptr != NULL);

    memset(large_ptr, 0x42, large_size);
    cr_assert(large_ptr[0] == 0x42);
    cr_assert(large_ptr[large_size - 1] == 0x42);

    liberate(large_ptr);
}

Test(__gc_t, allocate_array)
{
    int *array;
    const size_t count = 100;

    allocate(array, count * sizeof *array);
    cr_assert(array != NULL);

    for (size_t i = 0; i < count; i++) {
        array[i] = (int) i;
    }

    for (size_t i = 0; i < count; i++) {
        cr_assert(array[i] == (int) i);
    }

    liberate(array);
}

Test(__gc_t, memory_reallocate_grow)
{
    int *ptr;

    allocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);
    *ptr = 42;

    reallocate(ptr, 10 * sizeof *ptr);
    cr_assert(ptr != NULL);
    cr_assert(*ptr == 42);

    liberate(ptr);
}

Test(__gc_t, memory_reallocate_shrink)
{
    int *ptr;

    allocate(ptr, 10 * sizeof *ptr);
    cr_assert(ptr != NULL);

    for (int i = 0; i < 10; i++) {
        ptr[i] = i;
    }

    reallocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);
    cr_assert(*ptr == 0);

    liberate(ptr);
}

Test(__gc_t, memory_reallocate_to_zero, .exit_code = 84)
{
    int *ptr;

    allocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);

    remove_stderr();
    reallocate(ptr, 0);
    restore_stderr();

    cr_assert(ptr == NULL);
}

Test(__gc_t, memory_reallocate_null_pointer)
{
    int *ptr = NULL;

    reallocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);

    liberate(ptr);
}

Test(__gc_t, multiple_allocations)
{
    char *ptrs[10];

    for (int i = 0; i < 10; i++) {
        allocate(ptrs[i], (i + 1) * sizeof(char));
        cr_assert(ptrs[i] != NULL);
        *ptrs[i] = 'A' + i;
    }

    for (int i = 0; i < 10; i++) {
        cr_assert(*ptrs[i] == 'A' + i);
    }

    for (int i = 9; i >= 0; i--) {
        liberate(ptrs[i]);
        cr_assert(ptrs[i] == NULL);
    }
}

Test(__gc_t, mixed_allocation_and_liberation)
{
    char *ptr1, *ptr2, *ptr3;

    allocate(ptr1, sizeof *ptr1);
    allocate(ptr2, sizeof *ptr2);
    allocate(ptr3, sizeof *ptr3);

    cr_assert(ptr1 != NULL);
    cr_assert(ptr2 != NULL);
    cr_assert(ptr3 != NULL);

    liberate(ptr2);
    cr_assert(ptr2 == NULL);

    char *ptr4;
    allocate(ptr4, sizeof *ptr4);
    cr_assert(ptr4 != NULL);

    liberate(ptr1);
    liberate(ptr3);
    liberate(ptr4);
}

Test(__gc_t, garbage_collector_with_many_objects)
{
    char *ptrs[100];

    for (int i = 0; i < 100; i++) {
        allocate(ptrs[i], sizeof *ptrs[i]);
        cr_assert(ptrs[i] != NULL);
    }

    collect_garbage;

    char *new_ptr;
    allocate(new_ptr, sizeof *new_ptr);
    cr_assert(new_ptr != NULL);
    liberate(new_ptr);
}

Test(__gc_t, partial_cleanup_then_gc)
{
    char *ptr1, *ptr2, *ptr3, *ptr4;

    allocate(ptr1, sizeof *ptr1);
    allocate(ptr2, sizeof *ptr2);
    allocate(ptr3, sizeof *ptr3);
    allocate(ptr4, sizeof *ptr4);

    liberate(ptr2);
    liberate(ptr4);

    collect_garbage;

    char *new_ptr;
    allocate(new_ptr, sizeof *new_ptr);
    cr_assert(new_ptr != NULL);
    liberate(new_ptr);
}

Test(__gc_t, memory_write_read_integrity)
{
    struct test_struct {
        int a;
        char b;
        double c;
    } *ptr;

    allocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);

    ptr->a = 12345;
    ptr->b = 'X';
    ptr->c = 3.14159;

    cr_assert(ptr->a == 12345);
    cr_assert(ptr->b == 'X');
    cr_assert(ptr->c == 3.14159);

    liberate(ptr);
}

Test(__gc_t, memory_boundary_test)
{
    char *ptr;
    const size_t size = 50;

    allocate(ptr, size);
    cr_assert(ptr != NULL);

    ptr[0] = 'F';
    ptr[size - 1] = 'L';

    cr_assert(ptr[0] == 'F');
    cr_assert(ptr[size - 1] == 'L');

    liberate(ptr);
}

Test(__gc_t, allocation_deallocation_cycle)
{
    for (int cycle = 0; cycle < 100; cycle++) {
        char *ptr;
        allocate(ptr, 1000);
        cr_assert(ptr != NULL);

        memset(ptr, cycle % 256, 1000);

        liberate(ptr);
        cr_assert(ptr == NULL);
    }
}

Test(__gc_t, fragmentation_test)
{
    char *ptrs[20];

    for (int i = 0; i < 20; i++) {
        allocate(ptrs[i], (i + 1) * 100);
        cr_assert(ptrs[i] != NULL);
    }

    for (int i = 1; i < 20; i += 2) {
        liberate(ptrs[i]);
    }

    for (int i = 1; i < 20; i += 2) {
        allocate(ptrs[i], 50);
        cr_assert(ptrs[i] != NULL);
    }

    for (int i = 0; i < 20; i++) {
        if (ptrs[i] != NULL) {
            liberate(ptrs[i]);
        }
    }
}

Test(__gc_t, allocate_after_gc_cleanup)
{
    char *ptr1;
    char *ptr2;

    allocate(ptr1, sizeof *ptr1);
    cr_assert(ptr1 != NULL);

    collect_garbage;

    allocate(ptr2, sizeof *ptr2);
    cr_assert(ptr2 != NULL);

    liberate(ptr2);
}

Test(__gc_t, gc_empty_list)
{
    collect_garbage;

    char *ptr;

    allocate(ptr, sizeof *ptr);
    cr_assert(ptr != NULL);
    liberate(ptr);
}
