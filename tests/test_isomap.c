#include "../src/isomap.h"
#include "../src/tile.h"
#include "../src/map.h"
#include <stdio.h>
#include <tap.h>

int main () {
    diag("Loading an isomap from a JSON file");
    struct isomap *isomap = isomap_create_from_json_file("../data/map10x10-64x64.json");
    tile_print_tileset(isomap->tileset, "# ");
    map_print(isomap->map, "# ");
    isomap_delete(isomap);
    done_testing();
}
