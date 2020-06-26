#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "map_graph.h"
#include "queue.h"

// Help functions //
// -------------- //

/**
 * Print a node to stdout
 *
 * @param node  The node to print
 */
void mapgraph_print_node(const struct map_cell_node *node) {
    printf("  Node #%d of cell (%d,%d,%d) containing tile \"%s\" with %d neighbors\n",
           node->index,
           node->cell.row,
           node->cell.column,
           node->cell.layer,
           node->tile->name,
           node->num_neighbors);
}

/**
 * Add a new cell to a graph
 *
 * @param graph   The graph
 * @param tile    The tile associated with the cell
 * @param row     The row of the cell
 * @param column  The column of the cell
 * @param layer   The layer of the cell
 */
void mapgraph_add_cell(struct map_graph *graph,
                       struct tile *tile,
                       unsigned int row,
                       unsigned int column,
                       unsigned int layer) {
    if (graph->num_nodes == graph->capacity) {
        graph->capacity *= 2;
        graph->nodes = realloc(graph->nodes,
                               graph->capacity * sizeof(struct map_cell_node));
    }
    struct map_cell_node *node = graph->nodes + graph->num_nodes;
    node->index = graph->num_nodes;
    node->cell.row = row;
    node->cell.column = column;
    node->cell.layer = layer;
    node->tile = tile;
    node->neighbors = malloc(sizeof(struct map_cell_node*));
    node->num_neighbors = 0;
    node->capacity = 1;
    ++graph->num_nodes;
}

/**
 * Return the node associated with a cell in a graph
 *
 * If the cell does not exist in the graph, NULL is returned.
 *
 * @param graph  The graph
 * @param cell   A cell in the graph
 * @return       The node associated with the cell
 */
struct map_cell_node *mapgraph_get_node(const struct map_graph *graph,
                                        const struct map_cell *cell) {
    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
        if (graph->nodes[i].cell.row == cell->row &&
            graph->nodes[i].cell.column == cell->column &&
            graph->nodes[i].cell.layer == cell->layer)
            return graph->nodes + i;
    }
    return NULL;
}

/**
 * Add a neighbor to a node
 *
 * @param node      The node
 * @param neighbor  The neighbor
 */
void mapgraph_add_neighbor_to_node(struct map_cell_node *node,
                                   struct map_cell_node *neighbor) {
    if (node->num_neighbors == node->capacity) {
        node->capacity *= 2;
        node->neighbors = realloc(node->neighbors,
                                  node->capacity * sizeof(struct map_cell_node*));
    }
    node->neighbors[node->num_neighbors] = neighbor;
    ++node->num_neighbors;
}

/**
 * Add a neighbor to a cell in a graph
 *
 * The neighbor is specified by a vector (deltaRow, deltaColumn, deltaLayer),
 * whose values are in {-1, 0, 1}. If the graph does not contain the given
 * corresponding node for the neighbor, nothing happens.
 *
 * @param graph         The graph
 * @param row           The row of the cell
 * @param column        The column of the cell
 * @param layer         The layer of the cell
 * @param delta_row     The row variation for the neighbor
 * @param delta_column  The column variation for the neighbor
 * @param delta_layer   The layer variation for the neighbor
 */
void mapgraph_add_neighbor(struct map_graph *graph,
                           unsigned int row,
                           unsigned int column,
                           unsigned int layer,
                           int delta_row,
                           int delta_column,
                           int delta_layer) {
    struct map_cell cell = {row, column, layer};
    struct map_cell neighbor = {row + delta_row,
                                column + delta_column,
                                layer + delta_layer};
    struct map_cell_node *cell_node = mapgraph_get_node(graph, &cell);
    struct map_cell_node *neighbor_node = mapgraph_get_node(graph, &neighbor);
    if (cell_node != NULL && neighbor_node != NULL) {
        mapgraph_add_neighbor_to_node(cell_node, neighbor_node);
        mapgraph_add_neighbor_to_node(neighbor_node, cell_node);
    }
}

// Functions //
// --------- //

struct map_graph mapgraph_create(const struct map *map) {
    struct map_graph graph;
    graph.map = map;
    graph.nodes = malloc(sizeof(struct map_cell_node));
    graph.num_nodes = 0;
    graph.capacity = 1;
    for (unsigned int k = 0; k < map->num_layers; ++k) {
        for (unsigned int i = 0; i < map->num_rows; ++i) {
            for (unsigned int j = 0; j < map->num_columns; ++j) {
                unsigned int tile_id = map->layers[k].tiles[i][j];
                if (tile_id != 0 && !map_has_tile_above(map, i, j, k)) {
                    mapgraph_add_cell(&graph, &map->tiles[tile_id], i, j, k);
                }
            }
        }
    }
    for (unsigned int i = 0; i < graph.num_nodes; ++i) {
        const struct map_cell *cell = &graph.nodes[i].cell;
        unsigned int tile_id
            = map->layers[cell->layer].tiles[cell->row][cell->column];
        const struct tile *tile = &map->tiles[tile_id];
        for (unsigned int j = 0; j < tile->num_directions; ++j) {
            struct direction direction = tile->directions[j];
            struct direction opposite = {
                -direction.delta_row,
                -direction.delta_column,
                -direction.delta_layer
            };
            struct map_cell neighbor = {
                cell->row + direction.delta_row,
                cell->column + direction.delta_column,
                cell->layer + direction.delta_layer
            };
            struct map_cell_node *neighbor_node
                = mapgraph_get_node(&graph, &neighbor);
            if (neighbor_node != NULL) {
                struct tile *neighbor_tile = neighbor_node->tile;
                if (map_has_direction(neighbor_tile, &opposite)) {
                    mapgraph_add_neighbor_to_node(&graph.nodes[i], neighbor_node);
                    mapgraph_add_neighbor_to_node(neighbor_node, &graph.nodes[i]);
                }
            }
        }
    }
    return graph;
}

void mapgraph_delete(struct map_graph *graph) {
    free(graph->nodes);
}

void mapgraph_print(const struct map_graph *graph) {
    printf("Graph of %d nodes\n", graph->num_nodes);
    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
        mapgraph_print_node(&graph->nodes[i]);
    }
}

void mapgraph_to_dot(const struct map_graph *graph,
                     const char *output_filename) {
    FILE *output_file;
    if (strcmp(output_filename, "stdout") == 0) {
        output_file = stdout;
    } else {
        output_file = fopen(output_filename, "w");
    }
    fprintf(output_file, "strict graph {\n");
    for (unsigned int k = 0; k < graph->map->num_layers; ++k) {
        for (unsigned int i = 0; i < graph->num_nodes; ++i) {
            if (graph->nodes[i].cell.layer == k) {
                fprintf(output_file, "  \"%d,%d,%d\" [label=\"(%d,%d,%d)\"];\n",
                        graph->nodes[i].cell.layer,
                        graph->nodes[i].cell.row,
                        graph->nodes[i].cell.column,
                        graph->nodes[i].cell.layer,
                        graph->nodes[i].cell.row,
                        graph->nodes[i].cell.column);
            }
        }
    }
    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
        for (unsigned int j = 0; j < graph->nodes[i].num_neighbors; ++j) {
            struct map_cell *cell = &graph->nodes[i].cell;
            struct map_cell *neighbor = &graph->nodes[i].neighbors[j]->cell;
            fprintf(output_file, "  \"%d,%d,%d\" -- \"%d,%d,%d\";\n",
                    cell->layer, cell->row, cell->column,
                    neighbor->layer, neighbor->row, neighbor->column);
        }
    }
    fprintf(output_file, "}\n\n");
    if (strcmp(output_filename, "stdout") != 0) {
        fclose(output_file);
    }
}

struct map_path *mapgraph_retrieve_path(struct map_cell_node **predecessors,
                                        unsigned int start_index,
                                        unsigned int end_index,
                                        const struct map_cell *end_cell) {
    if (predecessors[end_index] == NULL) {
        return NULL;
    } else {
        unsigned int index = end_index;
        struct map_path *path = malloc(sizeof(struct map_path));
        path->head = *end_cell;
        path->tail = NULL;
        while (index != start_index) {
            struct map_path *tmp_path = malloc(sizeof(struct map_path));
            tmp_path->head = predecessors[index]->cell;
            tmp_path->tail = path;
            path = tmp_path;
            index = predecessors[index]->index;
        }
        return path;
    }
}

struct map_path *mapgraph_shortest_path(const struct map_graph *graph,
                                        const struct map_cell *start,
                                        const struct map_cell *end) {
    assert(start->row    < graph->map->num_rows);
    assert(start->column < graph->map->num_columns);
    assert(start->layer  < graph->map->num_layers);
    assert(end->row      < graph->map->num_rows);
    assert(end->column   < graph->map->num_columns);
    assert(end->layer    < graph->map->num_layers);
    struct map_cell_node *predecessors[graph->num_nodes];
    int distance[graph->num_nodes];
    for (unsigned int i = 0; i < graph->num_nodes; ++i) {
        predecessors[i] = NULL;
        distance[i] = -1;
    }
    struct map_cell_node *start_node = mapgraph_get_node(graph, start);
    queue q;
    queue_initialize(&q);
    queue_push(&q, start_node);
    distance[start_node->index] = 0;
    predecessors[start_node->index] = start_node;
    while (!queue_is_empty(&q)) {
        struct map_cell_node *node = queue_pop(&q);
        for (unsigned int i = 0; i < node->num_neighbors; ++i) {
            struct map_cell_node *neighbor = node->neighbors[i];
            unsigned int index = neighbor->index;
            if (distance[index] == -1) {
                distance[index] = distance[node->index] + 1;
                predecessors[index] = node;
                queue_push(&q, neighbor);
            }
        }
    }
    struct map_path *path
        = mapgraph_retrieve_path(predecessors, start_node->index,
                                 mapgraph_get_node(graph, end)->index, end);
    return path;
}

void mapgraph_print_path(const struct map_path *path) {
    printf("[ ");
    while (path != NULL) {
        printf("(%d,%d,%d) ", path->head.row,
                              path->head.column,
                              path->head.layer);
        path = path->tail;
    }
    printf("]");
}

void mapgraph_delete_path(struct map_path *path) {
    if (path != NULL) {
        mapgraph_delete_path(path->tail);
        free(path);
    }
}
