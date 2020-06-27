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
    ok(map->num_layers == 3, "map now has 3 layers");
    diag("Setting several tiles");
    map_set_tile_by_indices(map, 0, 2, 2, 1);
    map_set_tile_by_indices(map, 1, 0, 0, 2);
    map_set_tile_by_indices(map, 2, 7, 3, 3);
    diag("Printing the map's content");
    map_print(map, "# ");
    ok(map_get_tile_by_indices(map, 0, 2, 2) == 1, "map[0,2,2] == 1");
    ok(map_get_tile_by_indices(map, 1, 0, 0) == 2, "map[1,0,0] == 2");
    ok(map_get_tile_by_indices(map, 2, 7, 3) == 3, "map[2,7,3] == 3");
    ok(map_get_tile_by_indices(map, 0, 5, 0) == -1,
       "map[0,5,0] == -1 (out of bounds)");
    ok(map_get_tile_by_indices(map, 3, 0, 0) == -1,
       "map[3,0,0] == -1 (out of bounds)");
    diag("Deleting the map");
    map_delete(map);
    return 0;
}
