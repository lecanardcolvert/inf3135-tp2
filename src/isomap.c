#include "isomap.h"
#include "map.h"
#include "tile.h"
#include <jansson.h>

// Help functions //
// -------------- //

/**
 * Load directions for a given tile in an isomap
 *
 * @param isomap           The isomap
 * @param id               The id of the tile
 * @param json_directions  The JSON object containing the directions
 */
void isomap_load_directions(struct isomap *isomap,
                            tile_id id,
                            const json_t *json_directions) {
    unsigned int i;
    json_t *json_direction;
    json_array_foreach(json_directions, i, json_direction) {
        int dx, dy, dz;
        dx = json_integer_value(json_array_get(json_direction, 0));
        dy = json_integer_value(json_array_get(json_direction, 1));
        dz = json_integer_value(json_array_get(json_direction, 2));
        tile_add_direction(isomap->tileset, id, dx, dy, dz);
    }
}

/**
 * Load tiles from a JSON array into the given isomap
 *
 * @param map           The map into which the tiles are loaded
 * @param json_tileset  The JSON array containing the tiles
 */
void isomap_load_tileset(struct isomap *isomap, const json_t *json_tileset) {
    for (unsigned int i = 0; i < json_array_size(json_tileset); ++i) {
        json_t *json_tile = json_array_get(json_tileset, i);
        tile_id id = json_integer_value(json_object_get(json_tile, "id"));
        const char *filename = json_string_value(json_object_get(json_tile, "filename"));
        tile_add_to_tileset(isomap->tileset, id, filename);
        isomap_load_directions(isomap, id, json_object_get(json_tile, "directions"));
    }
}

/**
 * Loads layers into the given isomap
 *
 * @param isomap       The isomap
 * @param json_layers  The JSON array containing the layers
 */
void isomap_load_map(struct isomap *isomap, const json_t *json_layers) {
    unsigned int i;
    json_t *json_layer;
    json_array_foreach(json_layers, i, json_layer) {
        unsigned int num_rows, num_columns;
        int dx, dy, dz;
        num_rows = json_integer_value(json_object_get(json_layer, "num-rows"));
        num_columns = json_integer_value(json_object_get(json_layer, "num-cols"));
        json_t *json_offset = json_object_get(json_layer, "offset");
        dx = json_integer_value(json_array_get(json_offset, 0));
        dy = json_integer_value(json_array_get(json_offset, 1));
        dz = json_integer_value(json_array_get(json_offset, 2));
        struct layer *layer = map_add_layer(isomap->map, num_rows, num_columns, dx, dy, dz);
        json_t *data = json_object_get(json_layer, "data");
        unsigned int j;
        json_t *data_tile;
        json_array_foreach(data, j, data_tile) {
            unsigned int id = json_integer_value(data_tile);
            layer->tiles[j / num_columns][j % num_columns] = id;
        }
    }
}

// Functions //
// --------- //

struct isomap *isomap_create_from_json_file(const char *filename) {
    struct isomap *isomap;

    json_t *json_root, *json_tileset, *json_layers;
    json_error_t error;
    json_root = json_load_file(filename, 0, &error);
    json_tileset = json_object_get(json_root, "tileset");
    json_layers = json_object_get(json_root, "layers");
    isomap = malloc(sizeof(struct isomap));
    isomap->tileset = tile_create_tileset();
    isomap->map = map_create();
    isomap_load_tileset(isomap, json_tileset);
    isomap_load_map(isomap, json_layers);
    return isomap;
}

void isomap_delete(struct isomap *isomap) {
    tile_delete_tileset(isomap->tileset);
    map_delete(isomap->map);
    free(isomap);
}
