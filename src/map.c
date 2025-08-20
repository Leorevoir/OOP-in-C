#include "oop/string.h"
#include <memory/allocate.h>
#include <memory/liberate.h>
#include <oop/map.h>
#include <string.h>

/**
 * private attributes
 */

struct MapSlot {
    const void *key;
    const void *data;
    size_t hash;
    SlotState state;
};

struct MapData {
    size_t size;
    size_t capacity;
    size_t deleted_count;
};

__cplus__used static void map_ctor(void *instance, va_list *args);
__cplus__used static void map_dtor(void *instance);

static __inline size_t probe_quadratic(size_t hash, size_t attempt, size_t capacity)
{
    return (hash + attempt + (attempt * attempt)) & (capacity - 1);
}

#define PROBE(hash, attempt, capacity) probe_quadratic(hash, attempt, capacity)

static __inline void initialize_slots(MapSlot *slots, size_t capacity)
{
    for (size_t i = 0; i < capacity; i++) {
        slots[i].state = SLOT_EMPTY;
        slots[i].key = NULL;
        slots[i].data = NULL;
        slots[i].hash = 0;
    }
}

static size_t _find_slot_priv(const Map *self, const void *key, size_t hash);
static bool _map_resize_priv(Map *self, size_t new_capacity);

// clang-format off
static const Class __cplus__used map_class = {
    .__size__ = sizeof(Map),
    .__name__ = "Map",
    .__ctor__ = map_ctor,
    .__dtor__ = map_dtor,
};
// clang-format on

/**
 * public
 */

__cplus__const __cplus__used const Class *MapGetClass(void)
{
    return &map_class;
}

static void map_resize(Map *self, size_t new_size)
{
    if (new_size <= self->_priv->capacity) {
        return;
    }

    size_t nc = vectorize_size(self->_priv->capacity);
    while (nc < new_size) {
        nc = vectorize_size(nc);
    }

    _map_resize_priv(self, nc);
}

__cplus__const static size_t map_size(const Map *self)
{
    return self->_priv->size;
}

static void map_insert(Map *self, const void *key, const void *data)
{
    if (!self || !key) {
        return;
    }

    map_resize(self, self->_priv->size + 1);

    const size_t hash = self->hash_func(key);
    const size_t slot_index = _find_slot_priv(self, key, hash);
    MapSlot *slot = &self->_slots[slot_index];

    if (slot->state == SLOT_OCCUPIED) {
        slot->data = data;
    } else {
        if (slot->state == SLOT_DELETED) {
            --self->_priv->deleted_count;
        }
        slot->key = key;
        slot->data = data;
        slot->hash = hash;
        slot->state = SLOT_OCCUPIED;
        ++self->_priv->size;
    }
}

static bool map_contains(const Map *self, const void *key)
{
    if (!self || !key || self->_priv->size == 0) {
        return false;
    }

    const size_t hash = self->hash_func(key);
    const size_t slot_index = _find_slot_priv(self, key, hash);

    return self->_slots[slot_index].state == SLOT_OCCUPIED;
}

static const void *map_get(const Map *self, const void *key)
{
    if (!self || !key || self->_priv->size == 0) {
        return NULL;
    }

    const size_t hash = self->hash_func(key);
    const size_t slot_index = _find_slot_priv(self, key, hash);

    if (self->_slots[slot_index].state == SLOT_OCCUPIED) {
        return self->_slots[slot_index].data;
    }

    return NULL;
}

static bool map_remove(Map *self, const void *key)
{
    if (!self || !key || self->_priv->size == 0) {
        return false;
    }

    const size_t hash = self->hash_func(key);
    const size_t slot_index = _find_slot_priv(self, key, hash);
    MapSlot *slot = &self->_slots[slot_index];

    if (slot->state == SLOT_OCCUPIED) {
        slot->state = SLOT_DELETED;
        slot->key = NULL;
        slot->data = NULL;
        slot->hash = 0;
        --self->_priv->size;
        ++self->_priv->deleted_count;
        return true;
    }

    return false;
}

static void map_clear(Map *self)
{
    if (!self) {
        return;
    }

    initialize_slots(self->_slots, self->_priv->capacity);

    self->_priv->size = 0;
    self->_priv->deleted_count = 0;
}

/**
 * private
 */

static __inline size_t _map_hash_str(const void *key)
{
    return hash_str((const char *) key);
}

static size_t _find_slot_priv(const Map *self, const void *key, size_t hash)
{
    size_t attempt = 0;

    while (attempt < self->_priv->capacity) {
        const size_t index = PROBE(hash, attempt, self->_priv->capacity);
        const MapSlot *slot = &self->_slots[index];

        if (slot->state == SLOT_EMPTY) {
            return index;
        }

        if (slot->state == SLOT_OCCUPIED && slot->hash == hash
            && strcmp((const char *) slot->key, (const char *) key) == 0) {
            return index;
        }

        ++attempt;
    }

    return 0;
}

static bool _map_resize_priv(Map *self, size_t new_capacity)
{
    if (!self || new_capacity <= self->_priv->capacity) {
        return false;
    }

    /** save old data */
    MapSlot *old_slots = self->_slots;
    size_t old_capacity = self->_priv->capacity;

    /** allocate new slots */
    self->_priv->capacity = new_capacity;
    allocate(self->_slots, new_capacity * sizeof(MapSlot));
    self->_priv->size = 0;
    self->_priv->deleted_count = 0;

    initialize_slots(self->_slots, new_capacity);

    /** re hash all occupied slots from old table */
    if (old_slots) {
        for (size_t i = 0; i < old_capacity; i++) {
            if (old_slots[i].state == SLOT_OCCUPIED) {
                const size_t hash = old_slots[i].hash;
                const size_t slot_index = _find_slot_priv(self, old_slots[i].key, hash);
                MapSlot *slot = &self->_slots[slot_index];

                slot->key = old_slots[i].key;
                slot->data = old_slots[i].data;
                slot->hash = hash;
                slot->state = SLOT_OCCUPIED;
                ++self->_priv->size;
            }
        }

        liberate(old_slots);
    }

    return true;
}

static void map_ctor(void *instance, va_list *args)
{
    Map *self = (Map *) instance;

    self->class = MapGetClass();

    allocate(self->_priv, sizeof(MapData));

    self->_priv->size = 0;
    self->_priv->deleted_count = 0;

    self->insert = map_insert;
    self->contains = map_contains;
    self->get = map_get;
    self->remove = map_remove;
    self->resize = map_resize;
    self->clear = map_clear;
    self->size = map_size;
    self->hash_func = _map_hash_str;

    size_t capacity = va_arg(*args, size_t);
    if (capacity == 0) {
        capacity = 8;
    }

    size_t actual_capacity = 1;
    while (actual_capacity < capacity) {
        actual_capacity <<= 1;
    }

    self->_priv->capacity = actual_capacity;
    allocate(self->_slots, actual_capacity * sizeof(MapSlot));

    for (size_t i = 0; i < actual_capacity; i++) {
        self->_slots[i].state = SLOT_EMPTY;
        self->_slots[i].key = NULL;
        self->_slots[i].data = NULL;
        self->_slots[i].hash = 0;
    }
}

static void map_dtor(void *instance)
{
    Map *self = (Map *) instance;

    liberate(self->_slots);
    liberate(self->_priv);
}
