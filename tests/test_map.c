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
    diag("Adding a 8x4 layer with offset (2,1,3)");
    map_add_layer(map, 8, 4, 2, 1, 3);
    diag("Adding a 4x3 layer with offset (2,3,1)");
    map_add_layer(map, 4, 3, 2, 3, 1);
    ok(map->num_layers == 3, "map now has 3 layers");
    diag("Setting several tiles");
    map_set_tile_by_location(map, 2, 2, 0, 1);
    map_set_tile_by_location(map, 3, 4, 1, 2);
    map_set_tile_by_location(map, 7, 3, 3, 3);
    diag("Printing the map's content");
    map_print(map, "# ");
    ok(map_get_tile_by_location(map, 2, 2, 0) == 1,
       "tile at location (2,2,0) is 1");
    ok(map_get_tile_by_location(map, 3, 4, 1) == 2,
       "tile at location (3,4,1) is 2");
    ok(map_get_tile_by_location(map, 7, 3, 3) == 3,
       "tile at location (7,3,3) is 3");
    ok(map_get_tile_by_location(map, 0, 0, 1) == -1,
       "tile at location (0,0,1) is -1 (does not exist)");
    ok(map_is_location_top_free(map, 2, 2, 0),
       "location (2,2,0) is top free");
    ok(map_is_location_top_free(map, 3, 4, 1),
       "location (3,4,1) is top free");
    ok(!map_is_location_top_free(map, 0, 0, 0),
       "location (0,0,0) is not top free");
    printf("# All occupied locations: ");
    unsigned int n = 0;
    for (const struct location *location = map_get_occupied_location(map, true);
         location != NULL;
         location = map_get_occupied_location(map, false)) {
        geometry_print_location(location);
        printf(" ");
        ++n;
    }
    printf("\n");
    ok(n == 3, "number of occupied locations is 3");
    struct box b = map_get_bounding_box(map);
    diag("Computing bounding box");
    ok(b.xmin == 2 && b.ymin == 2 && b.zmin == 0,
       "bounding box minimum coordinates are (2,2,0)");
    ok(b.xmax == 7 && b.ymax == 4 && b.zmax == 3,
       "bounding box maximum coordinates are (7,4,3)");
    diag("Deleting the map");
    map_delete(map);
    done_testing();
}
