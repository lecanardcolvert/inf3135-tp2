#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "queue.h"

// Help functions //
// -------------- //

/**
 * Add an isolated node to a graph
 *
 * A node corresponds with a top-free location and a tile.
 *
 * @param graph     The graph
 * @param tile      The tile
 * @param location  The location of the tile
 */
void graph_add_isolated_node(struct graph *graph,
                             const struct tile *tile,
                             const struct location *location) {
    if (graph->num_nodes == graph->capacity) {
        graph->capacity *= 2;
        graph->nodes = realloc(graph->nodes,
                               graph->capacity * sizeof(struct graph_node));
    }
    struct graph_node *node = graph->nodes + graph->num_nodes;
    node->tile = tile;
    node->location = *location;
    node->neighbors = malloc(sizeof(struct graph_node*));
    node->num_neighbors = 0;
    node->capacity = 1;
    ++graph->num_nodes;
}

/**
 * Add all nodes to a graph from the given map
 *
 * @param graph  The graph
 * @param map    The map
 */
void graph_add_nodes(struct graph *graph,
                     const struct map *map,
                     const struct tileset *tileset) {
    const struct location *location;
    for (location = map_get_top_free_location(map, true);
         location != NULL;
         location = map_get_top_free_location(map, false)) {
        tile_id id = map_get_tile_by_location(map, location->x,
                                              location->y, location->z);
        struct tile *tile = tile_by_id(tileset, id);
        graph_add_isolated_node(graph, tile, location);
    }
}

/**
 * Add a neighbor to a node
 *
 * @param node      The node
 * @param neighbor  The neighbor
 */
void graph_add_neighbor_to_node(struct graph_node *node,
                                struct graph_node *neighbor) {
    if (node->num_neighbors == node->capacity) {
        node->capacity *= 2;
        node->neighbors = realloc(node->neighbors,
                                  node->capacity * sizeof(struct map_cell_node*));
    }
    node->neighbors[node->num_neighbors] = neighbor;
    ++node->num_neighbors;
}

/**
 * Add all edges to a graph from the given map
 *
 * There is an edge between two nodes if the directions allow a move from one
 * node to the other.
 *
 * @param graph  The graph
 */
void graph_add_edges(struct graph *graph) {
    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
        for (unsigned int j = 0; j < graph->num_nodes; ++j) {
            const struct location *location1 = &graph->nodes[i].location;
            const struct location *location2 = &graph->nodes[j].location;
            const struct tile *tile = graph->nodes[i].tile;
            for (unsigned int d = 0; d < tile->num_directions; ++d) {
                const struct vect *direction = tile->directions + d;
                if (location1->x + direction->dx == location2->x &&
                    location1->y + direction->dy == location2->y &&
                    location1->z + direction->dz == location2->z) {
                    graph_add_neighbor_to_node(graph->nodes + i, graph->nodes + j);
                }
            }
        }
    }
}

/**
 * Print a node to a stream
 *
 * @param stream  The stream
 * @param node    The node to print
 */
void graph_print_node(FILE *stream, const struct graph_node *node, const char *prefix) {
    fprintf(stream, "%s  Node with tile-id=%d at ", prefix, node->tile->id);
    geometry_print_location(stream, &node->location);
    fprintf(stream, " with %d neighbor%s\n", node->num_neighbors,
            node->num_neighbors <= 1 ? "" : "s");
    for (unsigned int n = 0; n < node->num_neighbors; ++n) {
        fprintf(stream, "%s    Neighbor %d is at ", prefix, n);
        geometry_print_location(stream, &node->neighbors[n]->location);
        fprintf(stream, "\n");
    }
}

// Functions //
// --------- //

struct graph *graph_create(const struct map *map,
                           const struct tileset *tileset) {
    struct graph *graph = malloc(sizeof(struct graph));
    graph->nodes = malloc(sizeof(struct graph_node));
    graph->num_nodes = 0;
    graph->capacity = 1;
    graph_add_nodes(graph, map, tileset);
    graph_add_edges(graph);
    graph->map = map;
    graph->tileset = tileset;
    return graph;
}

void graph_delete(struct graph *graph) {
    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
        free(graph->nodes[i].neighbors);
    }
    free(graph->nodes);
    free(graph);
}

void graph_print(FILE *stream, const struct graph *graph, const char *prefix) {
    fprintf(stream, "%sGraph of %d nodes\n", prefix, graph->num_nodes);
    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
        graph_print_node(stream, graph->nodes + i, prefix);
    }
}

//struct map_path *mapgraph_retrieve_path(struct map_cell_node **predecessors,
//                                        unsigned int start_index,
//                                        unsigned int end_index,
//                                        const struct map_cell *end_cell) {
//    if (predecessors[end_index] == NULL) {
//        return NULL;
//    } else {
//        unsigned int index = end_index;
//        struct map_path *path = malloc(sizeof(struct map_path));
//        path->head = *end_cell;
//        path->tail = NULL;
//        while (index != start_index) {
//            struct map_path *tmp_path = malloc(sizeof(struct map_path));
//            tmp_path->head = predecessors[index]->cell;
//            tmp_path->tail = path;
//            path = tmp_path;
//            index = predecessors[index]->index;
//        }
//        return path;
//    }
//}
//
//struct map_path *mapgraph_shortest_path(const struct map_graph *graph,
//                                        const struct map_cell *start,
//                                        const struct map_cell *end) {
//    assert(start->row    < graph->map->num_rows);
//    assert(start->column < graph->map->num_columns);
//    assert(start->layer  < graph->map->num_layers);
//    assert(end->row      < graph->map->num_rows);
//    assert(end->column   < graph->map->num_columns);
//    assert(end->layer    < graph->map->num_layers);
//    struct map_cell_node *predecessors[graph->num_nodes];
//    int distance[graph->num_nodes];
//    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
//        predecessors[i] = NULL;
//        distance[i] = -1;
//    }
//    struct map_cell_node *start_node = mapgraph_get_node(graph, start);
//    queue q;
//    queue_initialize(&q);
//    queue_push(&q, start_node);
//    distance[start_node->index] = 0;
//    predecessors[start_node->index] = start_node;
//    while (!queue_is_empty(&q)) {
//        struct map_cell_node *node = queue_pop(&q);
//        for (unsigned int i = 0; i < node->num_neighbors; ++i) {
//            struct map_cell_node *neighbor = node->neighbors[i];
//            unsigned int index = neighbor->index;
//            if (distance[index] == -1) {
//                distance[index] = distance[node->index] + 1;
//                predecessors[index] = node;
//                queue_push(&q, neighbor);
//            }
//        }
//    }
//    struct map_path *path
//        = mapgraph_retrieve_path(predecessors, start_node->index,
//                                 mapgraph_get_node(graph, end)->index, end);
//    return path;
//}
//
//void mapgraph_print_path(const struct map_path *path) {
//    printf("[ ");
//    while (path != NULL) {
//        printf("(%d,%d,%d) ", path->head.row,
//                              path->head.column,
//                              path->head.layer);
//        path = path->tail;
//    }
//    printf("]");
//}
//
//void mapgraph_delete_path(struct map_path *path) {
//    if (path != NULL) {
//        mapgraph_delete_path(path->tail);
//        free(path);
//    }
//}
