/**
 * map.h
 *
 * Handle grid maps.
 *
 * A map is represented as an ordered list of layers, on which there are tiles
 * that are distributed on a rectangular grid.
 *
 * Below is the logical representation of a layer having 3 rows and 4 columns:
 *
 *           c c c c
 *           o o o o
 *           l l l l
 *           u u u u
 *           m m m m
 *           n n n n
 *                  
 *           0 1 2 3
 *                 
 *           | | | |
 *           V V V V
 *
 *          +-+-+-+-+
 * row 0 -> | | | | |
 *          +-+-+-+-+
 * row 1 -> | | | | |
 *          +-+-+-+-+
 * row 2 -> | | | | |
 *          +-+-+-+-+
 *
 * Tiles are identified by a positive integer ID (the empty tile is identified
 * by 0).
 *
 * The module provides 3 data structures:
 *
 * - `struct direction`: describe a move from one cell to another
 * - `struct layer`: a layer in the map
 * - `struct map`: the map itself
 *
 * @author   Alexandre Blondin Massé
 */
#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stdbool.h>

// Types //
// ----- //

typedef int tile_id;

/**
 * A direction
 */
struct direction {
    int dh; // The height variation
    int dr; // The row variation
    int dc; // The column variation
};

/**
 * A layer
 */
struct layer {
    tile_id **tiles;          // A matrix of the tiles in the layer
    unsigned int num_rows;    // The number of rows
    unsigned int num_columns; // The number of columns
    struct direction offset;  // The offset with respect to the origin
};

/**
 * A map
 *
 * Invariants:
 *
 * * The layers are ordered by their heights
 * * Two layers always have different height
 */
struct map {
    struct layer *layers;    // The layers
    unsigned int num_layers; // The current number of layers
    unsigned int capacity;   // The maximum number of layers
};

// Functions //
// --------- //

/**
 * Create an empty map
 *
 * @return  The created map
 */
struct map *map_create(void);

/**
 * Delete a map
 *
 * @param map  The map to delete
 */
void map_delete(struct map *map);

/**
 * Add a layer to a map
 *
 * The layer is initialized with empty tiles.
 *
 * If the map already contains a layer of the given height, then no layer is
 * added and the function returns `NULL`.
 *
 * @param map          The map
 * @param num_rows     The number of rows of the layer
 * @param num_columns  The number of columns of the layer
 * @param dh           The height of the layer
 * @param dr           The row offset of the layer
 * @param dc           The column offset of the layer
 * @return             The new layer or NULL
 */
struct layer *map_add_layer(struct map *map,
                            unsigned int num_rows,
                            unsigned int num_columns,
                            int dh, int dr, int dc);
/**
 * Set the tile associated with a triple index (l,r,c)
 *
 * @param map   The map
 * @param l     The layer index
 * @param r     The row index
 * @param c     The column index
 * @param tile  The tile id to set
 */

void map_set_tile_by_indices(struct map *map,
                             unsigned int l,
                             unsigned int r,
                             unsigned int c,
                             tile_id tile);

/**
 * Return the tile associated with a triple index (l,r,c)
 *
 * Return -1 if the location is invalid.
 *
 * @param map  The map
 * @param l    The layer index of the tile
 * @param r    The row index of the tile
 * @param c    The column index of the tile
 */
tile_id map_get_tile_by_indices(const struct map *map,
                                unsigned int l,
                                unsigned int r,
                                unsigned int c);

/**
 * Return the tile associated with a location (h,r,c)
 *
 * A location is a position in absolute coordinates
 *
 * Return -1 if the location is invalid.
 *
 * @param map  The map
 * @param h    The height
 * @param r    The row
 * @param c    The column
 */
tile_id map_tile_by_location(const struct map *map,
                             unsigned int h,
                             unsigned int r,
                             unsigned int c);

/**
 * Return true if a tile has another tile above itself
 *
 * @param map     The map containing the tile
 * @param l       The layer index of the tile
 * @param r       The row index of the tile
 * @param c       The column index of the tile
 */
bool map_has_empty_tile_above(const struct map *map,
                              unsigned int l,
                              unsigned int r,
                              unsigned int c);
/**
 * Print a map to stdout
 *
 * @param map     The map
 * @param prefix  The prefix to print for each line
 */
void map_print(const struct map *map, const char *prefix);

#endif
