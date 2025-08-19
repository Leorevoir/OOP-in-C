#ifndef C_PLUS_ARRAY_H_
#define C_PLUS_ARRAY_H_

#include <oop/interface.h>
#include <oop/macros.h>

#include <unistd.h>

typedef struct ArrayData ArrayData;

typedef struct Array {
    const Class *class;

    void (*append)(struct Array *self, const void *elem);
    void (*insert)(struct Array *self, size_t index, const void *elem);
    void (*remove)(struct Array *self, size_t index);
    void (*clear)(struct Array *self);
    void (*resize)(struct Array *self, size_t new_size);
    void (*sort)(struct Array *self, int (*cmp)(const void *a, const void *b));

    void *(*at)(const struct Array *self, size_t index);

    size_t (*size)(const struct Array *self);
    ssize_t (*find)(const struct Array *self, const void *key, int (*cmp)(const void *a, const void *b));

    ClassDtor elem_dtor;
    ArrayData *_priv;
} Array;

__cplus__nodiscard __cplus__const const Class *ArrayGetClass(void);
#define ArrayClass ArrayGetClass()

#define array_foreach(array, type, var, code)                                                                          \
    for (size_t __i = 0; __i < (array)->size(array); ++__i) {                                                          \
        type *var = (type *) array->at(array, __i);                                                                    \
        code;                                                                                                          \
    }

#endif /* C_PLUS_ARRAY_H_ */
