#ifndef CPLUS_OOP_MAP_H_
#define CPLUS_OOP_MAP_H_

#include <oop/interface.h>
#include <oop/macros.h>
#include <stdbool.h>

typedef enum { SLOT_EMPTY = 0, SLOT_OCCUPIED = 1, SLOT_DELETED = 2 } SlotState;

typedef struct MapSlot MapSlot;
typedef struct MapData MapData;

typedef size_t (*MapHash)(const void *key);

typedef struct Map {
    const Class *class;

    void (*insert)(struct Map *self, const void *key, const void *data);
    const void *(*get)(const struct Map *self, const void *key);
    bool (*remove)(struct Map *self, const void *key);
    void (*resize)(struct Map *self, const size_t new_size);
    bool (*contains)(const struct Map *self, const void *key);
    void (*clear)(struct Map *self);
    size_t (*size)(const struct Map *self);

    MapData *_priv;
    MapSlot *_slots;
    MapHash hash_func;
} Map;

__cplus__const const Class *MapGetClass(void);
#define MapClass MapGetClass()

#endif /* CPLUS_OOP_MAP_H_ */
