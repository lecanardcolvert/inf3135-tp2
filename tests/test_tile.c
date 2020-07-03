#include "../src/tile.h"
#include <stdio.h>
#include <tap.h>

int main () {
    diag("Creating an empty tileset");
    struct tileset *tileset = tile_create_tileset();
    tile_add_to_tileset(tileset, 1, "");
    tile_add_direction(tileset, 1,  1,  0, 0);
    tile_add_direction(tileset, 1, -1,  0, 0);
    tile_add_direction(tileset, 1,  0,  1, 0);
    tile_add_direction(tileset, 1,  0, -1, 0);
    tile_add_to_tileset(tileset, 2, "");
    tile_add_direction(tileset, 2,  0,  0, 1);
    diag("Printing the tileset");
    tile_print_tileset(stdout, tileset, "#");
    ok(tileset->num_tiles == 2, "tileset contains 2 tiles");
    ok(tileset->tiles[0].num_directions == 4,
       "tile at index 0 has 4 allowed directions");
    ok(tileset->tiles[1].num_directions == 1,
       "tile at index 1 has 1 allowed direction");
    struct vect v = {-1, 0, 0};
    ok(geometry_equal_vect(tileset->tiles[0].directions + 1, &v),
       "direction at index 1, of tile at index 0, is (-1,0,0)");
    diag("Deleting the tileset");
    tile_delete_tileset(tileset);
    done_testing();
}
