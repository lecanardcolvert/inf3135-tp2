/**
 * graph.h
 *
 * Handles graphs representing maps.
 *
 * A graph is a common data structure used to represent networks. It is
 * completely determined by its vertices (or nodes) and the edges (or links)
 * between the nodes.
 *
 * In our case, we represent a grid map by a graph whose nodes are exactly the
 * cells that are top-free (i.e. the tile is occupied and the tile above it is
 * not occupied), meaning that we can "move" on this cell. Also, there is an
 * edge between two tiles if it is possible to move from one to the other.
 *
 * The interest of representing a map by a graph is that one can, in
 * particular, compute a walk between two cells in the map.
 *
 * The module provides four data structures:
 *
 * - `struct graph_node`: a node in the graph
 * - `struct graph`: a graph
 * - `struct graph_walk`: a walk (directed path) from one cell to another in
 *   the graph
 *
 * @author   Alexandre Blondin Massé
 */
#ifndef GRAPH_H
#define GRAPH_H

#include "tile.h"
#include "map.h"
#include <stdbool.h>

// Types //
// ----- //

/**
 * A node in a map graph
 */
struct graph_node {
    unsigned int index;            // The index of the node in the graph
    const struct tile *tile;       // The tile stored in the node
    struct location location;      // The location of the tile
    struct graph_node **neighbors; // The neighbors of this node
    unsigned int num_neighbors;    // The number of neighbors
    unsigned int capacity;         // The neighbors capacity
};

/**
 * A graph representing a map
 */
struct graph {
    const struct map *map;         // The associated map
    const struct tileset *tileset; // The associated map
    struct graph_node *nodes;      // The nodes in the graph
    unsigned int num_nodes;        // The number of nodes
    unsigned int capacity;         // The nodes capacity
};

/**
 * A walk (directed path) in the graph
 */
struct graph_walk {
    struct graph_node **nodes; // The first node in the walk
    unsigned int num_nodes;    // The number of steps in the walk
    unsigned int capacity;     // The nodes capacity
};

// Functions //
// --------- //

/**
 * Create a graph from a map and a tileset
 *
 * In the resulting graph, each top-free tile of the map (a tile such that
 * there is no other tile on top of it) is a node, and there is an edge link)
 * between two cells if it is possible to move from one cell to the other.
 *
 * Note: `graph_delete` should be called when the graph is not needed anymore.
 *
 * @param map      The map
 * @param tileset  The tileset used in the map
 * @return         The graph induced by the map
 */
struct graph *graph_create(const struct map *map,
                           const struct tileset *tileset);

/**
 * Delete the given graph
 *
 * @param graph  The graph to delete
 */
void graph_delete(struct graph *graph);

/**
 * Print the given graph to a stream
 *
 * @param stream  The stream
 * @param graph   The graph to print
 * @param prefix  The prefix to print for each line
 */
void graph_print(FILE *stream,
                 const struct graph *graph,
                 const char *prefix);

/**
 * Print the given graph to a stream in the DOT format
 * 
 * See this page for more details about the DOT language:
 * https://graphviz.org/doc/info/lang.html
 *
 * @param stream  The stream
 * @param graph   The graph to print
 */
void graph_print_to_dot(FILE *stream,
                        const struct graph *graph);

/**
 * Return a shortest walk between two locations in a map
 *
 * If such a walk does not exist, then NULL is returned.
 *
 * Note: `graph_delete_walk` should be called when the walk is not needed
 * anymore.
 *
 * @param graph  The graph
 * @param start  The starting location
 * @param end    The ending location
 * @return       A shortest walk between two cells
 */
struct graph_walk *graph_shortest_walk(const struct graph *graph,
                                       const struct location *start,
                                       const struct location *end);

/**
 * Delete the given walk
 *
 * @param walk  The walk to delete
 */
void graph_delete_walk(struct graph_walk *walk);

/**
 * Print the given walk to a stream
 *
 * @param stream  The stream
 * @param walk    The walk to print
 * @param prefix  The prefix to print for each line
 */
void graph_print_walk(FILE *stream,
                      const struct graph_walk *walk,
                      const char *prefix);

#endif
