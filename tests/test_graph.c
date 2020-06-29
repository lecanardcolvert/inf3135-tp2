#include "../src/isomap.h"
#include "../src/graph.h"
#include <stdio.h>
#include <tap.h>

int main () {
    FILE *input = fopen("../data/map10x10-64x64.json", "r");
    struct isomap *isomap = isomap_create_from_json_file(input);
    fclose(input);
    isomap_print(stdout, isomap, "# ");
    struct graph *graph = graph_create(isomap->map, isomap->tileset);
    graph_print(stdout, graph, "# ");
    graph_delete(graph);
    isomap_delete(isomap);
    done_testing();
}
