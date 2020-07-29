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
    graph_print_to_dot(stdout, graph);
    struct location start = {0, 9, 1};
    struct location end = {9, 0, 1};
    struct graph_walk *walk = graph_shortest_walk(graph, &start, &end);
    graph_print_walk(stdout, walk, "# ");
    graph_delete_walk(walk);
    graph_delete(graph);
    isomap_delete(isomap);
    done_testing();
}
