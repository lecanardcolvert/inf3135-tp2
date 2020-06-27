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
 * Return the layer at given height.
 *
 * If no such layer exists, return -1.
 *
 * @param map  The map containing the layer
 * @return     The layer index if it exists
 *             -1 otherwise
 */
int map_layer_by_height(const struct map *map,
                        int h) {
    for (int l = 0; l < (int)map->num_layers; ++l) {
        int dh = map->layers[l].offset.dh;
        if (dh == h)
            return l;
        else if (dh > h)
            return -1;
    }
    return -1;
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
    struct layer *layer;
    for (layer = map->layers;
         layer < map->layers + map->num_layers && layer->offset.dh < dh;
         ++layer);
    if (layer < map->layers && layer->offset.dh == dh)
        return NULL;
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

void map_set_tile_by_indices(struct map *map,
                             unsigned int l,
                             unsigned int r,
                             unsigned int c,
                             tile_id tile) {
    assert(l < map->num_layers);
    assert(r < map->layers[l].num_rows);
    assert(c < map->layers[l].num_columns);
    map->layers[l].tiles[r][c] = tile;
}

tile_id map_get_tile_by_indices(const struct map *map,
                                unsigned int l,
                                unsigned int r,
                                unsigned int c) {
    if (l < map->num_layers &&
        r < map->layers[l].num_rows &&
        c < map->layers[l].num_columns)
        return map->layers[l].tiles[r][c];
    else
        return -1;
}

tile_id map_get_tile_by_location(const struct map *map,
                                 int h,
                                 int r,
                                 int c) {
    int l = map_layer_by_height(map, h);
    if (l != -1) {
        int r2 = r - map->layers[l].offset.dr;
        int c2 = c - map->layers[l].offset.dc;
        if (r2 >= 0 && r2 < (int)map->layers[l].num_rows &&
            c2 >= 0 && c2 < (int)map->layers[l].num_columns) {
            return map->layers[l].tiles[r2][c2];
        }
    }
    return -1;
}

bool map_is_location_top_free(const struct map *map,
                              unsigned int h,
                              unsigned int r,
                              unsigned int c) {
    return map_get_tile_by_location(map, h, r, c) > 0 &&
           map_get_tile_by_location(map, h + 1, r, c) <= 0;
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
