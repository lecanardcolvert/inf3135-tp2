#include "../src/isomap.h"
#include "../src/tile.h"
#include "../src/map.h"
#include "../src/geometry.h"
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
    struct isomap *isomap = isomap_create_from_json_file(input);
    pass("create isomap from %s", filename);
    isomap_print(stdout, isomap, "# ");
    isomap_draw_to_png(isomap, "isomap-nowalk.png", NULL, NULL);
    pass("create png file from isomap without walk");
    struct location start = {9, 0, 1};
    printf("test");
    struct location end = {0, 9, 1};
    isomap_print(stdout, isomap, "# ");
    isomap_draw_to_png(isomap, "isomap-walk.png", &start, &end);
    pass("create png file from isomap with walk from 9,0,1 to 0,9,1");
    isomap_delete(isomap);
    fclose(input);
    done_testing();
}
