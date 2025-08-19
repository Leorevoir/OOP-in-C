#include <memory/allocate.h>
#include <memory/liberate.h>

#include <oop/map.h>

#include "tests.h"

Test(Map, create_map)
{
    Map *map = new (MapClass, 0);

    delete (map);
}

Test(Map, insert_and_get)
{
    Map *map = new (MapClass, 0);

    map->insert(map, "key1", "value1");

    cr_expect(map->size(map) == 1, "Size should be 1 after insertion");
    cr_expect(map->get(map, "key1") == "value1", "Get should return the inserted value");
    cr_expect(map->contains(map, "key1") == true, "Contains should return true for inserted key");

    delete (map);
}

Test(Map, insert_overwrite)
{
    Map *map = new (MapClass, 0);

    map->insert(map, "key1", "value1");
    map->insert(map, "key1", "value2");

    cr_expect(map->size(map) == 1, "Size should remain 1 after overwriting");
    cr_expect(map->get(map, "key1") == "value2", "Get should return the overwritten value");

    delete (map);
}

Test(Map, remove_existing)
{
    Map *map = new (MapClass, 0);

    map->insert(map, "key1", "value1");
    bool removed = map->remove(map, "key1");

    cr_expect(removed == true, "Remove should return true for existing key");
    cr_expect(map->size(map) == 0, "Size should be 0 after removal");
    cr_expect(map->get(map, "key1") == NULL, "Get should return NULL after removal");
    cr_expect(map->contains(map, "key1") == false, "Contains should return false after removal");

    delete (map);
}

Test(Map, remove_nonexisting)
{
    Map *map = new (MapClass, 0);

    bool removed = map->remove(map, "nonkey");

    cr_expect(removed == false, "Remove should return false for non-existing key");
    cr_expect(map->size(map) == 0, "Size should remain 0");

    delete (map);
}

Test(Map, contains_nonexisting)
{
    Map *map = new (MapClass, 0);

    cr_expect(map->contains(map, "nonkey") == false, "Contains should return false for non-existing key");

    delete (map);
}

Test(Map, clear)
{
    Map *map = new (MapClass, 0);

    map->insert(map, "key1", "value1");
    map->insert(map, "key2", "value2");
    map->clear(map);

    cr_expect(map->size(map) == 0, "Size should be 0 after clear");
    cr_expect(map->get(map, "key1") == NULL, "Get should return NULL after clear");
    cr_expect(map->get(map, "key2") == NULL, "Get should return NULL after clear");
    cr_expect(map->contains(map, "key1") == false, "Contains should return false after clear");

    delete (map);
}

Test(Map, resize)
{
    Map *map = new (MapClass, 4);

    map->insert(map, "key1", "value1");
    map->insert(map, "key2", "value2");

    map->resize(map, 16);

    cr_expect(map->size(map) == 2, "Size should remain unchanged after resize");
    cr_expect(map->get(map, "key1") == "value1", "Items should be preserved after resize");
    cr_expect(map->get(map, "key2") == "value2", "Items should be preserved after resize");

    delete (map);
}

Test(Map, insert_after_remove)
{
    Map *map = new (MapClass, 0);

    map->insert(map, "key1", "value1");
    map->remove(map, "key1");
    map->insert(map, "key1", "value2");

    cr_expect(map->size(map) == 1, "Size should be 1 after re-insertion");
    cr_expect(map->get(map, "key1") == "value2", "Get should return the re-inserted value");

    delete (map);
}

Test(Map, multiple_inserts)
{
    Map *map = new (MapClass, 0);

    map->insert(map, "key1", "value1");
    map->insert(map, "key2", "value2");
    map->insert(map, "key3", "value3");

    cr_expect(map->size(map) == 3, "Size should be 3 after multiple insertions");
    cr_expect(map->get(map, "key1") == "value1");
    cr_expect(map->get(map, "key2") == "value2");
    cr_expect(map->get(map, "key3") == "value3");

    delete (map);
}

Test(Map, insert_null_data)
{
    Map *map = new (MapClass, 0);

    map->insert(map, "key1", NULL);

    cr_expect(map->size(map) == 1, "Size should be 1 after inserting NULL data");
    cr_expect(map->get(map, "key1") == NULL, "Get should return NULL");

    delete (map);
}
