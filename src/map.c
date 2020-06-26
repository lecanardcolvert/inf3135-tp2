#include "map.h"
#include <stdio.h>
#include <assert.h>

// Help functions //
// -------------- //

/**
 * Compare two layers by their heights
 *
 * @param layer1  The first layer
 * @param layer2  The second layer
 * @return        0  if the two layers have the same height
 *                <0 if the first layer is lower than the second
 *                >0 if the first layer is higher than the second
 */
int map_compare_layers(const void *layer1, const void *layer2) {
    return ((struct layer*)layer1)->offset.dh -
           ((struct layer*)layer2)->offset.dh;
}

/**
 * Delete a layer
 *
 * @param tile  The layer
 */
void map_delete_layer(struct layer *layer);

/**
 * Print a layer to stdout
 *
 * @param layer   The layer
 * @param indent  The indentation when printing
 */
void map_print_layer(const struct layer *layer,
                     const char *prefix);

// Functions //
// --------- //

struct map *map_create(void) {
    struct map *map = malloc(sizeof(struct map));
    map->layers = malloc(sizeof(struct layer));
    map->num_layers = 0;
    map->capacity = 1;
    return map;
}

void map_delete_layer(struct layer *layer) {
    for (unsigned int i = 0; i < layer->num_rows; ++i) {
        free(layer->tiles[i]);
    }
    free(layer->tiles);
}

void map_delete(struct map *map) {
    for (unsigned int l = 0; l < map->num_layers; ++l)
        map_delete_layer(map->layers + l);
    free(map->layers);
    free(map);
}

struct layer *map_add_layer(struct map *map,
                            unsigned int num_rows,
                            unsigned int num_columns,
                            int dh,
                            int dr,
                            int dc) {
    struct layer *layer =
        bsearch(&dh, map->layers, map->num_layers,
                sizeof(struct layer), map_compare_layers);
    if (layer != NULL) return NULL;
    if (map->num_layers == map->capacity) {
        map->capacity *= 2;
        map->layers = realloc(map->layers,
                              map->capacity * sizeof(struct layer));
    }
    for (layer = map->layers + map->num_layers;
         layer > map->layers && (layer - 1)->offset.dh > dh;
         --layer)
        *layer = *(layer - 1);
    layer->num_rows = num_rows;
    layer->num_columns = num_columns;
    layer->offset = (struct direction){dh, dr, dc};
    layer->tiles = malloc(num_rows * sizeof(tile_id*));
    for (unsigned int i = 0; i < num_rows; ++i)
        layer->tiles[i] = calloc(num_columns, sizeof(tile_id));
    ++map->num_layers;
    return layer;
}

tile_id map_tile_by_indices(const struct map *map,
                            unsigned int l,
                            unsigned int r,
                            unsigned int c) {
    // TODO: not implemented
}

tile_id map_tile_by_location(const struct map *map,
                             unsigned int h,
                             unsigned int r,
                             unsigned int c) {
    // TODO: not implemented
}

bool map_has_empty_tile_above(const struct map *map,
                              unsigned int row,
                              unsigned int column,
                              unsigned int layer) {
    // TODO: not implemented
}

void map_print_layer(const struct layer *layer,
                     const char *prefix) {
    printf("A layer of %d row%s and %d column%s",
           layer->num_rows, layer->num_rows <= 1 ? "" : "s",
           layer->num_columns, layer->num_columns <= 1 ? "" : "s");
    printf(" (offset = (%d,%d,%d))\n",
           layer->offset.dh, layer->offset.dr, layer->offset.dc);
    for (unsigned int i = 0; i < layer->num_rows; ++i) {
        printf("%s    ", prefix);
        for (unsigned int j = 0; j < layer->num_columns; ++j) {
            printf("%d ", layer->tiles[i][j]);
        }
        printf("\n");
    }
}

void map_print(const struct map *map, const char *prefix) {
    printf("%sA map of %d layer%s\n", prefix, map->num_layers,
            map->num_layers <= 1 ? "" : "s");
    for (unsigned int i = 0; i < map->num_layers; ++i) {
        printf("%s  Layer %d: ", prefix, i);
        map_print_layer(&map->layers[i], prefix);
    }
}
