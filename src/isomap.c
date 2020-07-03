#include "isomap.h"
#include "map.h"
#include "tile.h"
#include "utils.h"
#include <jansson.h>
#include <cairo.h>

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
        json_t *json_filename = json_object_get(json_tile, "filename");
        char *filename = utils_strdup(json_string_value(json_filename));
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

struct isomap *isomap_create_from_json_file(FILE *file) {
    struct isomap *isomap;

    json_t *json_root, *json_tileset, *json_layers;
    json_error_t error;
    json_root = json_loadf(file, 0, &error);
    json_tileset = json_object_get(json_root, "tileset");
    json_layers = json_object_get(json_root, "layers");
    isomap = malloc(sizeof(struct isomap));
    isomap->tile_width
        = json_integer_value(json_object_get(json_root, "tile-width"));
    isomap->z_offset
        = json_integer_value(json_object_get(json_root, "z-offset"));
    isomap->tileset = tile_create_tileset();
    isomap->map = map_create();
    isomap_load_tileset(isomap, json_tileset);
    isomap_load_map(isomap, json_layers);
    json_decref(json_root);
    return isomap;
}

void isomap_delete(struct isomap *isomap) {
    tile_delete_tileset(isomap->tileset);
    map_delete(isomap->map);
    free(isomap);
}

void isomap_draw_to_png(const struct isomap *isomap,
                        const char *output_filename) {
    struct box bounding_box = map_get_bounding_box(isomap->map);
    struct vect box_vect = geometry_box_to_vect(&bounding_box);
    int h_step = isomap->tile_width / 2;
    int v_step = isomap->tile_width / 4;
    int l_step = isomap->z_offset;

    unsigned int surface_width
        = h_step * (box_vect.dx + box_vect.dy + 3);
    unsigned int surface_height
        = v_step * (box_vect.dx + box_vect.dy + 2) + l_step * (box_vect.dz + 2);
    cairo_surface_t *output_image =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                   surface_width, surface_height);
    cairo_t *cr = cairo_create(output_image);
    cairo_set_source_rgb(cr, 0, 0.1, 0);
    cairo_rectangle(cr, 0, 0, surface_width, surface_height);
    cairo_fill(cr);
    const struct location *location;
    for (location = map_get_occupied_location(isomap->map, true);
         location != NULL;
         location = map_get_occupied_location(isomap->map, false)) {
        int origin_x = h_step * (box_vect.dx + 0.5);
        int origin_y = (box_vect.dz - location->z) * l_step;
        int x = origin_x - location->x * h_step + location->y * h_step;
        int y = origin_y + location->x * v_step + location->y * v_step;
        tile_id id = map_get_tile_by_location(isomap->map, location->x,
                                              location->y, location->z);
        struct tile *tile = tile_by_id(isomap->tileset, id);
        cairo_surface_t *surface = cairo_image_surface_create_from_png(tile->filename);
        cairo_set_source_surface(cr, surface, x, y);
        cairo_paint(cr);
        cairo_surface_destroy(surface);
    }
    cairo_surface_write_to_png(output_image, output_filename);
    cairo_surface_destroy(output_image);
}

void isomap_print(FILE *stream, const struct isomap *isomap, const char *prefix) {
    tile_print_tileset(stream, isomap->tileset, prefix);
    map_print(stream, isomap->map, prefix);
}
