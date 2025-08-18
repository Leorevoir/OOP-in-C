#ifndef CPLUS_OOP_MAP_H_
#define CPLUS_OOP_MAP_H_

#include <oop/interface.h>
#include <oop/macros.h>

typedef struct Map {
    const Class *class;

    char **key;
    void **data;

    size_t size;
    size_t capacity;
} Map;

__cplus__const const Class *MapGetClass(void);
#define MapClass MapGetClass()

#endif /* CPLUS_OOP_MAP_H_ */
