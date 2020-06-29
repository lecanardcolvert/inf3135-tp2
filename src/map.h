/**
 * map.h
 *
 * Handle grid maps.
 *
 * A map is represented as an ordered list of layers, on which there are tiles
 * that are distributed on a rectangular grid.
 *
 * Each layer has a height, given by its z coordinate. The indices for the rows
 * and for the columns are consistent with the x and y coordinates in 3D space.
 * Below is the logical representation of a layer having 3 rows and 4 columns:
 *
 *           y y y y
 *           = = = =
 *           0 1 2 3
 *                 
 *           | | | |
 *           V V V V
 *
 *          +-+-+-+-+
 * x = 0 -> | | | | |
 *          +-+-+-+-+
 * x = 1 -> | | | | |
 *          +-+-+-+-+
 * x = 2 -> | | | | |
 *          +-+-+-+-+
 *
 * Tiles are identified by a positive integer ID (the empty tile is identified
 * by 0). An invalid tile is identified by the value -1.
 *
 * The module provides the following data structures:
 *
 * - `struct layer`: a layer in the map
 * - `struct map`: the map itself
 *
 * @author   Alexandre Blondin Massé
 */
#ifndef MAP_H
#define MAP_H

#include "geometry.h"

#include <stdlib.h>
#include <stdbool.h>

// Types //
// ----- //

typedef int tile_id;

/**
 * A layer
 */
struct layer {
    tile_id **tiles;          // A matrix of the tiles in the layer
    unsigned int num_rows;    // The number of rows
    unsigned int num_columns; // The number of columns
    struct vect offset;       // The offset with respect to the origin
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
 * Print a map to a stream
 *
 * @param stream  The stream
 * @param map     The map
 * @param prefix  The prefix to print for each line
 */
void map_print(FILE *stream, const struct map *map, const char *prefix);

/**
 * Add a layer to a map
 *
 * The layer is initialized with empty tiles.
 *
 * Layers of the same height are forbidden, therefore, if the map already
 * contains a layer of the given height, then nothing happens and the function
 * returns `NULL`.
 *
 * @param map          The map
 * @param num_rows     The number of rows of the layer
 * @param num_columns  The number of columns of the layer
 * @param dx           The x-offset of the layer
 * @param dy           The y-offset of the layer
 * @param dz           The z-offset (height) of the layer
 * @return             The new layer or NULL
 */
struct layer *map_add_layer(struct map *map,
                            unsigned int num_rows,
                            unsigned int num_columns,
                            int dx, int dy, int dz);

/**
 * Return the tile associated with a location
 *
 * Return -1 if the location is invalid.
 *
 * @param map  The map
 * @param x    The x-coordinate of the location
 * @param y    The y-coordinate of the location
 * @param z    The z-coordinate of the location
 */
tile_id map_get_tile_by_location(const struct map *map,
                                 int x, int y, int z);

/**
 * Set the tile associated with a location
 *
 * If there is no tile at the given location, then nothing happens.
 *
 * @param map   The map
 * @param x     The x-coordinate of the location
 * @param y     The y-coordinate of the location
 * @param z     The z-coordinate of the location
 * @param tile  The tile
 */
void map_set_tile_by_location(const struct map *map,
                              int x, int y, int z,
                              tile_id tile);

/**
 * Return true if a location has a top-free tile
 *
 * A location has a top-free if is is occupied by a tile and the location just
 * above is not occupied by a tile.
 *
 * @param map   The map
 * @param x     The x-coordinate of the location
 * @param y     The y-coordinate of the location
 * @param z     The z-coordinate of the location
 * @return      True if the location has a top-free tile
 */
bool map_is_location_top_free(const struct map *map,
                              int x, int y, int z);

/**
 * Allow iteration over all locations of a map
 *
 * The function should be used as follows:
 *
 * * The first call should be done with `from_start` set to `true`
 * * The next calls with `from_start` set to `false`
 * * When the returned value is `NULL`, it means that all locations have been
 *   iterated over
 *
 * @param map   The map
 * @param next  If true, starts from the first location
 *              If false, returns the next available location or NULL
 */
const struct location *map_get_occupied_location(const struct map *map,
                                                 bool from_start);

/**
 * Return the bounding box dimensions of a map
 *
 * The bounding box of the map is the smallest 3D rectangle that contains all
 * its nonempty tiles.
 *
 * If all tiles are empty, return a dummy box.
 *
 * @param map  The map
 * @return     The bounding box dimensions
 */
struct box map_get_bounding_box(const struct map *map);

#endif
