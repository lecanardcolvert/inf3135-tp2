#include "../src/map.h"
#include <stdio.h>
#include <tap.h>

int main () {
    puts("# Creating an empty map");
    struct map *map = map_create();
    ok(map->num_layers == 0, "empty map has 0 layer");
    puts("# Adding a 5x6 layer");
    map_add_layer(map, 5, 6, 0, 0, 0);
    puts("# Adding a 8x4 layer with offset (1,2,3)");
    map_add_layer(map, 8, 4, 1, 2, 3);
    ok(map->num_layers == 2, "map now has 2 layers");
    puts("# Printing the map's content");
    map_print(map, "# ");
    puts("# Deleting the map");
    map_delete(map);
    return 0;
}
