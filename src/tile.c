#include "tile.h"
#include <stdio.h>
#include <string.h>

#define PATH_LENGTH2 (PATH_LENGTH + 1 - sizeof(ROOT_DIR))

// Implementation //
// -------------- //

/**
 * Print a tile to a stream
 *
 * @param stream  The stream
 * @param tile    The tile to print
 * @param prefix  The prefix to print for each line
 */
void tile_print(FILE *stream,
                const struct tile *tile,
                const char *prefix) {
    fprintf(stream, "%s   Tile id=%d with directions ", prefix, tile->id);
    for (unsigned int d = 0; d < tile->num_directions; ++d) {
        if (d > 0) fprintf(stream, ",");
        geometry_print_vect(stream, tile->directions + d);
    }
    fprintf(stream, "\n");
}

// Implementation //
// -------------- //

struct tileset *tile_create_tileset(void) {
    struct tileset *tileset = malloc(sizeof(struct tileset));
    tileset->tiles = malloc(sizeof(struct tile));
    tileset->num_tiles = 0;
    tileset->capacity = 1;
    return tileset;
}

void tile_delete_tileset(struct tileset *tileset) {
    free(tileset->tiles);
    free(tileset);
}

void tile_print_tileset(FILE *stream,
                        const struct tileset *tileset,
                        const char *prefix) {
    fprintf(stream, "%sTileset of %d tile%s%s\n",
            prefix, tileset->num_tiles,
            tileset->num_tiles <= 1 ? "" : "s",
            tileset->num_tiles >= 1 ? ":" : "");
    for (unsigned int i = 0; i < tileset->num_tiles; ++i) {
        tile_print(stream, tileset->tiles + i, prefix);
    }
}

struct tile *tile_add_to_tileset(struct tileset *tileset,
                                 tile_id id,
                                 char *filename) {
    unsigned int i;
    for (i = 0;
         i < tileset->num_tiles && tileset->tiles[i].id < id;
         ++i);
    if (i < tileset->num_tiles && tileset->tiles[i].id == id)
        return NULL;
    if (tileset->num_tiles == tileset->capacity) {
        tileset->capacity *= 2;
        tileset->tiles = realloc(tileset->tiles,
                                 tileset->capacity * sizeof(struct tile));
    }
    for (unsigned int j = tileset->num_tiles; j > i; --j) {
        tileset->tiles[j] = tileset->tiles[j - 1];
    }
    tileset->tiles[i].id = id;
    strncpy(tileset->tiles[i].filename, ROOT_DIR, PATH_LENGTH);
    strncat(tileset->tiles[i].filename, filename, PATH_LENGTH2);
    tileset->tiles[i].surface = NULL;
    tileset->tiles[i].directions = malloc(sizeof(struct vect));
    tileset->tiles[i].num_directions = 0;
    tileset->tiles[i].capacity = 1;
    ++tileset->num_tiles;
    return tileset->tiles + i;
}

void tile_add_direction(struct tileset *tileset, tile_id id,
                        int dx, int dy, int dz) {
    unsigned int i;
    for (i = 0;
         i < tileset->num_tiles && tileset->tiles[i].id < id;
         ++i);
    if (i < tileset->num_tiles && tileset->tiles[i].id == id) {
        struct tile *tile = tileset->tiles + i;
        if (tile->num_directions == tile->capacity) {
            tile->capacity *= 2;
            tile->directions = realloc(tile->directions,
                                       tile->capacity * sizeof(struct vect));
        }
        tile->directions[tile->num_directions] = (struct vect){dx, dy, dz};
        ++tile->num_directions;
    }
}

struct tile *tile_by_id(const struct tileset *tileset,
                        tile_id id) {
    unsigned int i;
    for (i = 0;
         i < tileset->num_tiles && tileset->tiles[i].id < id;
         ++i);
    if (i < tileset->num_tiles && tileset->tiles[i].id == id)
        return tileset->tiles + i;
    else
        return NULL;
}
