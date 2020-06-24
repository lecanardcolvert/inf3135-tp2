/**
 * map.h
 *
 * Handles isometric maps.
 *
 * A map is represented as an ordered list of layers, on which there are tiles
 * that are distributed on a rectangular grid. Below is the logical
 * representation of a layer having 3 rows and 4 columns.
 *
 *           c c c c
 *           o o o o
 *           l l l l
 *           u u u u
 *           m m m m
 *           n n n n
 *                  
 *           1 2 3 4
 *                 
 *           | | | |
 *           V V V V
 *
 *          +-+-+-+-+
 * row 1 -> | | | | |
 *          +-+-+-+-+
 * row 2 -> | | | | |
 *          +-+-+-+-+
 * row 3 -> | | | | |
 *          +-+-+-+-+
 *
 * The corresponding isometric view of these tiles is then illustrated below.
 *
 *          row 1 -> /\
 *                  /  \ <- column 1
 *        row 2 -> /\  /\
 *                /  \/  \ <- column 2
 *      row 3 -> /\  /\  /\
 *              /  \/  \/  \ <- column 3
 *              \  /\  /\  /\
 *               \/  \/  \/  \ <- column 4
 *                \  /\  /\  /
 *                 \/  \/  \/ 
 *                  \  /\  /
 *                   \/  \/ 
 *                    \  /
 *                     \/ 
 *
 * Tiles are identified by a positive integer ID (the empty tile is identified
 * by 0). Since a tile might appear multiple times in a map, a precise copy is
 * called a cell and is identified uniquely by a triple (l,r,c), where l is the
 * layer number, r is the row and c is the column.
 *
 * The module provides four data structures:
 *
 * - `struct direction`: describe a move from one cell to another
 * - `struct tile`: a tile, whose image can be used as many times as needed
 * - `struct layer`: a layer in the map
 * - `struct Map`: the map itself
 *
 * @author   Alexandre Blondin Massé
 */
#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <cairo.h>
#include "map_graph.h"

// --------------- //
// Data structures //
// --------------- //

struct direction {    // A direction
    int delta_row;    // The displacement row-wise
    int delta_column; // The displacement column-wise
    int delta_layer;  // The displacement layer-wise
};

struct tile {                        // A tile
    char *name;                      // The name of the tile
    char *filename;                  // The filename of the image for the tile
    struct direction directions[12]; // The allowed directions
    unsigned int num_directions;     // The number of directions
    cairo_surface_t *image;          // The image of the tile
};

struct layer {                // A layer
    struct map *map;          // The map in which the layer is
    unsigned int **tiles;     // A matrix of the tiles in the layer
    bool **highlight;         // If true, hilight the tile
    unsigned int num_rows;    // The number of rows
    unsigned int num_columns; // The number of columns
    double offsetx;           // The x-offset
    double offsety;           // The y-offset
};

struct map {                   // A map
    struct layer *layers;      // The layers
    unsigned int num_layers;   // The current number of layers
    unsigned int max_layers;   // The maximum number of layers
    unsigned int num_rows;     // The number of rows
    unsigned int num_columns;  // The number of columns
    struct tile *tiles;        // The allowed tiles in the map
    unsigned int num_tiles;    // The number of allowed tiles in the map
    unsigned int max_tiles;    // The maximum number of allowed tiles in the map
    struct map_path *solution; // The solution of the map
};

// Functions //
// --------- //

/**
 * Create an empty map
 *
 * @param num_rows     The number of rows of the map
 * @param num_columns  The number of columns of the map
 * @param max_layers   The maximum number of layers in the map
 * @param max_tiles    The maximum number of allowed tiles in the map
 * @return             The created map
 */
struct map *map_create_map(unsigned int num_rows,
                           unsigned int num_columns,
                           unsigned int max_layers,
                           unsigned int max_tiles);

/**
 * Delete a map
 *
 * @param map  The map to be deleted
 */
void map_delete_map(struct map *map);

/**
 * Add an allowed direction to a tile
 *
 * @param tile       The tile
 * @param direction  The allowed direction
 */
void map_add_direction(struct tile *tile,
                       const struct direction *direction);

/**
 * Return true if a tile has a given direction
 *
 * @param tile       The tile
 * @param direction  The direction
 * @return           True if the tile has the given direction
 */
bool map_has_direction(const struct tile *tile,
                       const struct direction *direction);

/**
 * Add a tile to a map
 *
 * @param map       The map
 * @param name      The name of the tile
 * @param filename  The filename of the image for the tile
 * @return          The new tile
 */
struct tile *map_add_tile(struct map *map,
                          const char *name,
                          const char *filename);

/**
 * Add a layer to the given map
 *
 * @param map      The map to which the layer is added
 * @param offsetx  The x-offset of the layer
 * @param offsety  The y-offset of the layer
 * @return         The new layer
 */
struct layer *map_add_layer(struct map *map, double offsetx, double offsety);

/**
 * Add a path to a map
 *
 * @param map   The map
 * @param path  The path
 */
void map_add_solution(struct map *map, struct map_path *path);

/**
 * Return true if a tile has another tile above itself
 *
 * @param map     The map containing the tile
 * @param row     The row of the tile
 * @param column  The column of the tile
 * @param layer   The layer of the tile
 */
bool map_has_tile_above(const struct map *map,
                        unsigned int row,
                        unsigned int column,
                        unsigned int layer);
/**
 * Print a map to stdout
 *
 * @param map            The map
 * @param with_solution  If true, also print the solution
 */
void map_print_map(const struct map *map, bool with_solution);

/**
 * Generate a PNG file for the given map
 *
 * @param map             The map to be drawn
 * @param outputFilename  The output filename
 */
void map_to_png(const struct map *map, const char *output_filename);

#endif
