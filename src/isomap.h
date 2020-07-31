/**
 * isomap.h
 *
 * Handle isometric maps.
 *
 * @author  Alexandre Blondin Massé
 */
#ifndef ISOMAP_H
#define ISOMAP_H

#include <stdio.h>
#include "geometry.h"

// Types //
// ----- //

struct isomap {
    unsigned int tile_width;
    unsigned int z_offset;
    struct map *map;
    struct tileset *tileset;
};

// Functions //
// --------- //

/**
 * Create an isomap from a JSON file
 *
 * @param file  The input stream
 * @return      The resulting isomap
 */
struct isomap *isomap_create_from_json_file(FILE *file);

/**
 * Delete an isomap
 *
 * @param isomap  The isomap
 */
void isomap_delete(struct isomap *isomap);

/**
 * Draw an isomap to a PNG file
 * It can also highlight the tiles of a walk from start to end,
 * if both values are not NULL. No tiles will be highlighted
 * if a walk is not possible.
 *
 * @param isomap           The map to be drawn
 * @param output_filename  The output filename
 * @param start            The start of the walk
 * @param end              The end of the walk
 */
void isomap_draw_to_png(const struct isomap *isomap,
                        const char *output_filename, 
                        const struct location *start, 
                        const struct location *end);

/**
 * Print an isomap to a stream
 *
 * @param stream  The stream
 * @param isomap  The map
 * @param prefix  The prefix to print for each line
 */
void isomap_print(FILE *stream,
                  const struct isomap *isomap,
                  const char *prefix);

#endif
