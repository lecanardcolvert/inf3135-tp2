/**
 * isomap.h
 *
 * Handle isometric maps.
 *
 * @author  Alexandre Blondin Massé
 */
#ifndef ISOMAP_H
#define ISOMAP_H

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
 * @param filename  The JSON filename
 * @return          The resulting isomap
 */
struct isomap *isomap_create_from_json_file(const char *filename);

/**
 * Draw an isomap to a PNG file
 *
 * @param isomap           The map to be drawn
 * @param output_filename  The output filename
 */
void isomap_draw_to_png(const struct isomap *isomap,
                        const char *output_filename);

/**
 * Delete an isomap
 *
 * @param isomap  The isomap
 */
void isomap_delete(struct isomap *isomap);

#endif
