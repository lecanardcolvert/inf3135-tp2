#include "map.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

// Help functions //
// -------------- //

/**
 * Delete a layer
 *
 * @param tile  The layer
 */
void map_delete_layer(struct layer *layer) {
    if (layer != NULL) {
        for (unsigned int i = 0; i < layer->num_rows; ++i) {
            free(layer->tiles[i]);
            free(layer->highlight[i]);
        }
        free(layer->tiles);
        free(layer->highlight);
    }
}

/**
 * Delete a tile
 *
 * @param tile  The tile
 */
void map_delete_tile(struct tile *tile) {
    if (tile != NULL) {
        if (tile->name != NULL)     free(tile->name);
        if (tile->filename != NULL) free(tile->filename);
        if (tile->image != NULL)    cairo_surface_destroy(tile->image);
    }
}

/**
 * Print a tile to stdout
 *
 * @param layer  The tile
 */
void map_print_tile(const struct tile *tile) {
    printf("Tile \"%s\" (filename: %s) ", tile->name, tile->filename);
    printf("with %d directions : ", tile->num_directions);
    for (unsigned int i = 0; i < tile->num_directions; ++i) {
        printf("(%d,%d,%d)",
               tile->directions[i].delta_row,
               tile->directions[i].delta_column,
               tile->directions[i].delta_layer);
        if (i != tile->num_directions - 1) printf(", ");
    }
    printf("\n");
}
/**
 * Print a layer to stdout
 *
 * @param layer  The layer
 */
void map_print_layer(const struct layer *layer) {
    printf("A layer of %d rows and %d columns\n",
           layer->num_rows, layer->num_columns);
    for (unsigned int i = 0; i < layer->num_rows; ++i) {
        printf("  ");
        for (unsigned int j = 0; j < layer->num_columns; ++j) {
            printf("%d ", layer->tiles[i][j]);
        }
        printf("\n");
    }
}

// Functions //
// --------- //

struct map *map_create_map(unsigned int num_rows,
                           unsigned int num_columns,
                           unsigned int max_layers,
                           unsigned int max_tiles) {
    struct map *map = malloc(sizeof(struct map));
    map->layers = malloc(max_layers * sizeof(struct layer));
    map->num_layers = 0;
    map->max_layers = max_layers;
    map->num_rows = num_rows;
    map->num_columns = num_columns;
    map->tiles = malloc(max_tiles * sizeof(struct tile));
    map->tiles[0].name = strdup("empty");
    map->tiles[0].filename = strdup("empty");
    map->tiles[0].image = NULL;
    map->num_tiles = 1;
    map->max_tiles = max_tiles;
    map->solution = NULL;
    return map;
}

void map_delete_map(struct map *map) {
    if (map != NULL) {
        for (unsigned int i = 0; i < map->num_layers; ++i) {
            map_delete_layer(&map->layers[i]);
        }
        free(map->layers);
        map->layers = NULL;
        for (unsigned int i = 0; i < map->num_tiles; ++i) {
            map_delete_tile(&map->tiles[i]);
        }
        free(map->tiles);
        map->tiles = NULL;
        free(map);
    }
}

void map_addDirection(struct tile *tile,
                      const struct direction *direction) {
    tile->directions[tile->num_directions] = *direction;
    ++tile->num_directions;
}

bool map_has_direction(const struct tile *tile,
                       const struct direction *direction) {
    for (unsigned int i = 0; i < tile->num_directions; ++i) {
        if (tile->directions[i].delta_row    == direction->delta_row &&
            tile->directions[i].delta_column == direction->delta_column &&
            tile->directions[i].delta_layer  == direction->delta_layer) {
            return true;
        }
    }
    return false;
}

struct tile *map_add_tile(struct map *map, const char *name, const char *filename) {
    if (map->num_tiles < map->max_tiles + 1) {
        struct tile *tile = &map->tiles[map->num_tiles];
        tile->name = strdup(name);
        tile->filename = strdup(filename);
        tile->image = cairo_image_surface_create_from_png(filename);
        tile->num_directions = 0;
        ++map->num_tiles;
        return tile;
    } else {
        return NULL;
    }
}

struct layer *map_add_layer(struct map *map, double offsetx, double offsety) {
    if (map->num_layers < map->max_layers + 1) {
        struct layer *layer = &map->layers[map->num_layers];
        layer->map = map;
        layer->num_rows = map->num_rows;
        layer->num_columns = map->num_columns;
        layer->offsetx = offsetx;
        layer->offsety = offsety;
        layer->tiles = malloc(layer->num_rows * sizeof(unsigned int*));
        layer->highlight = malloc(layer->num_rows * sizeof(bool*));
        for (unsigned int i = 0; i < layer->num_rows; ++i) {
            layer->tiles[i] = malloc(layer->num_columns * sizeof(unsigned int));
            layer->highlight[i] = malloc(layer->num_columns * sizeof(bool));
            for (unsigned int j = 0; j < layer->num_columns; ++j) {
                layer->tiles[i][j] = 0;
                layer->highlight[i][j] = false;
            }
        }
        ++map->num_layers;
        return layer;
    } else {
        return NULL;
    }
}

void map_add_solution(struct map *map, struct map_path *path) {
    map->solution = path;
    while (path != NULL) {
        map->layers[path->head.layer].highlight[path->head.row][path->head.column]
            = true;
        path = path->tail;
    }
}

bool map_hasTileAbove(const struct map *map,
                      unsigned int row,
                      unsigned int column,
                      unsigned int layer) {
    assert(layer  < map->num_layers);
    assert(row    < map->num_rows);
    assert(column < map->num_columns);
    assert(map->layers[layer].tiles[row][column] != 0);
    return layer < map->num_layers - 1 &&
        map->layers[layer + 1].tiles[row][column] != 0;
}

void map_printMap(const struct map *map, bool withSolution) {
    printf("A map of %d layers of %d rows and %d columns using %d tiles\n",
           map->num_layers, map->num_rows, map->num_columns, map->num_tiles);
    for (unsigned int i = 0; i < map->num_tiles; ++i) {
        printf("  Tile %d: ", i);
        map_print_tile(&map->tiles[i]);
    }
    for (unsigned int i = 0; i < map->num_layers; ++i) {
        printf("  Layer %d: ", i);
        map_print_layer(&map->layers[i]);
    }
    if (withSolution && map->solution != NULL) {
        printf("  Solution: ");
        mapgraph_print_path(map->solution);
    }
}

void map_to_png(const struct map *map, const char *outputFilename) {
    unsigned int width  = 128 * (map->num_rows + map->num_columns + 1);
    unsigned int height = 64  * (map->num_rows + map->num_columns + map->num_layers + 2);
    cairo_surface_t *outputImage =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create(outputImage);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);
    cairo_translate(cr, 128 * (map->num_rows - 0.5), (map->num_layers - 1) * 78);
    for (unsigned int k = 0; k < map->num_layers; ++k) {
        cairo_save(cr);
        cairo_translate(cr, map->layers[k].offsetx,
                            map->layers[k].offsety);
        for (unsigned int i = 0; i < map->num_rows; ++i) {
            cairo_save(cr);
            for (unsigned int j = 0; j < map->num_columns; ++j) {
                unsigned int tileID = map->layers[k].tiles[i][j];
                if (tileID != 0) {
                    cairo_surface_t *image = map->tiles[tileID].image;
                    cairo_pattern_t *imagePattern =
                        cairo_pattern_create_for_surface(image);
                    cairo_set_source(cr, imagePattern);
                    cairo_paint(cr);
                    cairo_pattern_destroy(imagePattern);
                    if (map->layers[k].highlight[i][j]) {
                        cairo_save(cr);
                        cairo_set_operator(cr, CAIRO_OPERATOR_ADD);
                        cairo_set_source(cr, imagePattern);
                        cairo_paint(cr);
                        cairo_restore(cr);
                    }
                }
                cairo_translate(cr, 128, 64);
            }
            cairo_restore(cr);
            cairo_translate(cr, -128, 64);
        }
        cairo_restore(cr);
    }
    cairo_destroy(cr);
    cairo_surface_write_to_png(outputImage, outputFilename);
    cairo_surface_destroy(outputImage);
}
