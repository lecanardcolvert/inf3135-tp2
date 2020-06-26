#include "../src/map.h"
#include <stdio.h>
#include <tap.h>

int main () {
    diag("Creating an empty map");
    struct map *map = map_create();
    ok(map->num_layers == 0, "empty map has 0 layer");
    diag("Adding a 5x6 layer");
    map_add_layer(map, 5, 6, 0, 0, 0);
    ok(map->num_layers == 1, "map now has 1 layer");
    diag("Adding a 8x4 layer with offset (3,2,1)");
    map_add_layer(map, 8, 4, 3, 2, 1);
    diag("Adding a 4x3 layer with offset (1,2,3)");
    map_add_layer(map, 4, 3, 1, 2, 3);
    printf("# map->num_layers = %d\n", map->num_layers);
    ok(map->num_layers == 3, "map now has 3 layers");
    diag("Printing the map's content");
    map_print(map, "# ");
    diag("Deleting the map");
    map_delete(map);
    return 0;
}
