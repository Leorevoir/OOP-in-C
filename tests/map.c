#include <memory/garbage_collector.h>
#include <oop/map.h>

#include "tests.h"

Test(Map, create_map)
{
    Map *map = new (MapClass, 0);

    delete (map);
}
