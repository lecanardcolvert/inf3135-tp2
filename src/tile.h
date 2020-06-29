#ifndef TILE_H
#define TILE_H

#include "map.h"
#include <cairo.h>

// Types //
// ----- //

/**
 * A tile in a map
 */
struct tile {
    tile_id id;                  // The tile id
    const char *filename;        // The filename of the image for the tile
    cairo_surface_t *surface;    // The cairo surface
    struct vect *directions;     // The allowed directions
    unsigned int num_directions; // The number of allowed directions
    unsigned int capacity;       // The directions capacity
};

/**
 * A set of tiles
 */
struct tileset {
    struct tile *tiles;     // The tiles
    unsigned int num_tiles; // The number of tiles in the tileset
    unsigned int capacity;  // The capacity of the tileset
};

// Functions //
// --------- //

/**
 * Create an empty tileset
 *
 * @return  The tileset
 */
struct tileset *tile_create_tileset(void);

/**
 * Delete a tileset
 *
 * @param tileset  The tileset to delete
 */
void tile_delete_tileset(struct tileset *tileset);

/**
 * Print a tileset to stdout
 *
 * @param tileset  The tileset to print
 * @param prefix   The prefix to print for each line
 */
void tile_print_tileset(const struct tileset *tileset,
                        const char *prefix);

/**
 * Add a tile to a tileset
 *
 * @param tileset   The tileset
 * @param id        The id of the added tile
 * @param filename  The image filename of the tile
 * @return          The tile or NULL
 */
struct tile *tile_add_to_tileset(struct tileset *tileset,
                                 tile_id id,
                                 const char *filename);

/**
 * Add an allowed direction to a tile in a tileset
 *
 * If the id of the tile is invalid, nothing happens.
 *
 * @param tileset  The tileset
 * @param tile_id  The id of the tile
 * @param dx       The x-coordinate of the direction
 * @param dy       The y-coordinate of the direction
 * @param dz       The z-coordinate of the direction
 */
void tile_add_direction(struct tileset *tileset, tile_id id,
                        int dx, int dy, int dz);

/**
 * Return the tile by its id in a tileset
 *
 * If the id does not exist, return NULL.
 *
 * @param tileset  The tileset
 * @param id       The id of the tile
 * @return         The associated tile or NULL
 */
struct tile *tile_by_id(const struct tileset *tileset,
                        tile_id id);

#endif
