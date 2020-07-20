#include "../src/isomap.h"
#include "../src/tile.h"
#include "../src/map.h"
#include <stdio.h>
#include <tap.h>

int main () {
    const char *filename = "../data/map10x10-256x256.json";
    FILE *input = fopen(filename, "r");
    if (input != NULL) {
        pass("correctly open %s", filename);
    } else {
        BAIL_OUT("problem opening %s", filename);
    }
    struct isomap *isomap = NULL;
    lives_ok({isomap = isomap_create_from_json_file(input);},
              "create isomap from %s", filename);
    if (isomap == NULL) {
        BAIL_OUT("could not create isomap %s", filename);
    }
    isomap_print(stdout, isomap, "# ");
    lives_ok({isomap_draw_to_png(isomap, "isomap.png");},
             "create png file from isomap");
    isomap_delete(isomap);
    fclose(input);
    done_testing();
}
