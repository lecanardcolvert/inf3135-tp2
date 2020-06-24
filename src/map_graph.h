/**
 * map_graph.h
 *
 * Handles graphs representing maps.
 *
 * A graph is a common data structure used to represent networks. It is
 * completely determined by its vertices (or nodes) and the edges (or links)
 * between the nodes.
 *
 * In our case, we represent an isometric map by a graph whose nodes are
 * exactly the cells that are free (i.e. there is no cell above the tile),
 * meaning that we can "move" on this cell. Also, there is an edge (a link)
 * between two cells if it is possible to move from one cell to the other. The
 * interest of representing a map by a graph is that one can, in particular,
 * compute a path between two cells in the map.
 *
 * The module provides four data structures:
 *
 * - `struct map_cell`: a cell in the map
 * - `struct map_cell_node`: a node in the graph
 * - `struct map_graph`: a graph
 * - `struct map_path`: a path from one cell to another in the graph
 *
 * @author   Alexandre Blondin Massé
 */
#ifndef MAP_GRAPH_H
#define MAP_GRAPH_H

#include <stdbool.h>
#include "map.h"

// Types //
// ----- //

struct map_cell {        // A cell (position) on a map
    unsigned int row;    // The row of the cell
    unsigned int column; // The column of the cell
    unsigned int layer;  // The layer on which the cell is
};

struct map_cell_node {                // A node in the map graph
    unsigned int index;               // The index of this node
    struct map_cell cell;             // The cell for this node
    struct tile *tile;                // The tile for this node
    struct map_cell_node **neighbors; // The neighbors of the node
    unsigned int num_neighbors;       // The number of neighbors of the node
    unsigned int capacity;            // The capacity of the node
};

struct map_graph {               // A map graph
    const struct map *map;       // The associated map
    struct map_cell_node *nodes; // The nodes in the graph
    unsigned int num_nodes;      // The number of nodes
    unsigned int capacity;       // The capacity of the graph
};

struct map_path {          // A path in a map graph
    struct map_cell head;  // The first cell in the path
    struct map_path *tail; // The rest of the path
};

// Functions //
// --------- //

/**
 * Create a graph from a map
 *
 * In the resulting graph, each cell of the map that is free (i.e. there is no
 * other tile on top of it) is a node, and there is an edge (i.e. a link)
 * between two cells if it is possible to move from one cell to the other.
 *
 * Note: the function `mapgraph_delete` should be called when the graph is not
 * needed anymore.
 *
 * @param map  The map
 * @return     The graph induced by the map
 */
struct map_graph mapgraph_create(const struct map *map);

/**
 * Delete the given graph
 *
 * @param graph  The graph to delete
 */
void mapgraph_delete(struct map_graph *graph);

/**
 * Print the given graph to stdout
 *
 * @param graph  The graph to print
 */
void mapgraph_print(const struct map_graph *graph);

/**
 * Write the given graph to a dot file
 *
 * The dot format is the format recognized by Graphviz, a software that allows
 * graph display. See http://www.graphviz.org/ for more details.
 *
 * @param graph            The graph to write
 * @param output_filename  The name of the file
 */
void mapgraph_to_dot(const struct map_graph *graph,
                     const char *output_filename);

/**
 * Return a shortest path between two cells in the given graph
 *
 * If such a path does not exist, then NULL is returned.
 *
 * Note: the function `mapgraph_delete_path` should be called when the path is
 * not needed anymore.
 *
 * @param graph  The graph
 * @param start  The starting cell
 * @param end    The ending cell
 * @return       A shortest path between two cells
 */
struct map_path *mapgraph_shortest_path(const struct map_graph *graph,
                                        const struct map_cell *start,
                                        const struct map_cell *end);

/**
 * Delete the given path
 *
 * @param path  The path to delete
 */
void mapgraph_delete_path(struct map_path *path);

/**
 * Print the given path to stdout
 *
 * @param path  The path to be printed
 */
void mapgraph_print_path(const struct map_path *path);

#endif
