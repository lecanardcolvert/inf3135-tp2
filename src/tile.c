#include "tile.h"
#include <stdio.h>
#include <string.h>

#ifndef ROOT_DIR
#define ROOT_DIR "."
#endif
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
    fprintf(stream, "%s  Tile id=%d\n", prefix, tile->id);
    for (unsigned int o = 0; o <= 1; ++o) {
        fprintf(stream, "%s    %s directions: ", prefix,
                o == 0 ? "incoming" : "outgoing");
        for (unsigned int d = 0; d < tile->num_directions[o]; ++d) {
            if (d > 0) fprintf(stream, ",");
            geometry_print_vect(stream, tile->directions[o] + d);
        }
        fprintf(stream, "\n");
    }
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
                                 const char *filename) {
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
    tileset->tiles[i].directions[0] = malloc(sizeof(struct vect));
    tileset->tiles[i].num_directions[0] = 0;
    tileset->tiles[i].capacity[0] = 1;
    tileset->tiles[i].directions[1] = malloc(sizeof(struct vect));
    tileset->tiles[i].num_directions[1] = 0;
    tileset->tiles[i].capacity[1] = 1;
    ++tileset->num_tiles;
    return tileset->tiles + i;
}

void tile_add_direction(struct tileset *tileset, tile_id id,
                        int dx, int dy, int dz, bool incoming) {
    unsigned int i;
    for (i = 0;
         i < tileset->num_tiles && tileset->tiles[i].id < id;
         ++i);
    if (i < tileset->num_tiles && tileset->tiles[i].id == id) {
        unsigned int o = incoming ? 0 : 1;
        struct tile *tile = tileset->tiles + i;
        if (tile->num_directions[o] == tile->capacity[o]) {
            tile->capacity[o] *= 2;
            tile->directions[o]
                = realloc(tile->directions[o],
                          tile->capacity[o] * sizeof(struct vect));
        }
        tile->directions[o][tile->num_directions[o]] = (struct vect){dx, dy, dz};
        ++tile->num_directions[o];
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
