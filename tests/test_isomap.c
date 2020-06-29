#include "../src/isomap.h"
#include "../src/tile.h"
#include "../src/map.h"
#include <stdio.h>
#include <tap.h>

int main () {
    lives_ok({FILE *input = fopen("../data/map10x10-256x256.json", "r");
              isomap_create_from_json_file(input);
              fclose(input);},
              "loading an isomap from a json file does not crash");
    lives_ok({FILE *input = fopen("../data/map10x10-256x256.json", "r");
              struct isomap *isomap = isomap_create_from_json_file(input);
              fclose(input);isomap_print(stdout, isomap, "# ");
              isomap_draw_to_png(isomap, "isomap.png");
              isomap_delete(isomap);},
              "and saving it to png neither");
    done_testing();
}
