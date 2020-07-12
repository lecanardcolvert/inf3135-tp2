#include "../src/tile.h"
#include <stdio.h>
#include <tap.h>

int main () {
    diag("Creating an empty tileset");
    struct tileset *tileset = tile_create_tileset();
    tile_add_to_tileset(tileset, 1, "");
    tile_add_direction(tileset, 1,  1,  0, 0, true);
    tile_add_direction(tileset, 1, -1,  0, 0, false);
    tile_add_direction(tileset, 1,  0,  1, 0, false);
    tile_add_direction(tileset, 1,  0, -1, 0, false);
    tile_add_to_tileset(tileset, 2, "");
    tile_add_direction(tileset, 2,  0,  0, 1, true);
    diag("Printing the tileset");
    tile_print_tileset(stdout, tileset, "#");
    ok(tileset->num_tiles == 2, "tileset contains 2 tiles");
    ok(tileset->tiles[0].num_directions[0] == 1,
       "tile at index 0 has 1 incoming allowed direction");
    ok(tileset->tiles[0].num_directions[1] == 3,
       "tile at index 0 has 3 outgoing allowed directions");
    ok(tileset->tiles[1].num_directions[0] == 1,
       "tile at index 1 has 1 incoming allowed direction");
    ok(tileset->tiles[1].num_directions[1] == 0,
       "tile at index 1 has 0 outgoing allowed direction");
    struct vect v = {0, 1, 0};
    ok(geometry_equal_vect(tileset->tiles[0].directions[1] + 1, &v),
       "outgoing direction at index 1, of tile at index 0, is (0,1,0)");
    diag("Deleting the tileset");
    tile_delete_tileset(tileset);
    done_testing();
}
