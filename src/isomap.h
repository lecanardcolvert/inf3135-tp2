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
 * Delete an isomap
 *
 * @param isomap  The isomap
 */
void isomap_delete(struct isomap *isomap);

#endif
