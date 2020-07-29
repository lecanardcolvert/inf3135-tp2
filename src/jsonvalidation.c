#include "jsonvalidation.h"

/**
 * Validation errors
 */
enum status {
    JSONVALIDATION_OK                           = 0,
    JSONVALIDATION_OTHER_ERROR                  = 1,
    JSONVALIDATION_MISSING_ISOMAP               = 2,
    JSONVALIDATION_BAD_ISOMAP_VALUE             = 3,
    
    JSONVALIDATION_MISSING_ISOMAP_TILEWIDTH_KEY = 4,
    JSONVALIDATION_BAD_ISOMAP_TILEWIDTH_VALUE   = 5,
    JSONVALIDATION_MISSING_ISOMAP_ZOFFSET_KEY   = 6,
    JSONVALIDATION_BAD_ISOMAP_ZOFFSET_VALUE     = 7,
    JSONVALIDATION_MISSING_ISOMAP_TILESET_KEY   = 8,
    JSONVALIDATION_BAD_ISOMAP_TILESET_VALUE     = 9,
    JSONVALIDATION_MISSING_ISOMAP_LAYERS_KEY    = 10,
    JSONVALIDATION_BAD_ISOMAP_LAYERS_VALUE      = 11,
    
    JSONVALIDATION_BAD_TILE_VALUE               = 12,
    JSONVALIDATION_MISSING_TILE_ID_KEY          = 13,
    JSONVALIDATION_BAD_TILE_ID_VALUE            = 14,
    JSONVALIDATION_MISSING_TILE_FILENAME_KEY    = 15,
    JSONVALIDATION_BAD_TILE_FILENAME_VALUE      = 16,
    JSONVALIDATION_MISSING_TILE_INCOMING_KEY    = 17,
    JSONVALIDATION_BAD_TILE_INCOMING_VALUE      = 18,
    JSONVALIDATION_MISSING_TILE_OUTGOING_KEY    = 19,
    JSONVALIDATION_BAD_TILE_OUTGOING_VALUE      = 20,
    
    JSONVALIDATION_BAD_LAYER_VALUE              = 21,
    JSONVALIDATION_MISSING_LAYER_NUMROWS_KEY    = 22,
    JSONVALIDATION_BAD_LAYER_NUMROWS_VALUE      = 23,
    JSONVALIDATION_MISSING_LAYER_NUMCOLS_KEY    = 24,
    JSONVALIDATION_BAD_LAYER_NUMCOLS_VALUE      = 25,
    JSONVALIDATION_MISSING_LAYER_OFFSET_KEY     = 26,
    JSONVALIDATION_BAD_LAYER_OFFSET_VALUE       = 27,
    JSONVALIDATION_MISSING_LAYER_DATA_KEY       = 28,
    JSONVALIDATION_BAD_LAYER_DATA_VALUE         = 29
};

// Validation functions //
// -------------------- //

const unsigned int jsonvalidation_validate_file(FILE *file) {
}

const unsigned int jsonvalidation_validate_root(json_t *json_root) {
}

const unsigned int jsonvalidation_validate_isomap(const json_t *isomap) {
}

const unsigned int jsonvalidation_validate_isomap_tilewidth(const json_t *isomap) {
}

const unsigned int jsonvalidation_validate_isomap_zoffset(const json_t *isomap) {
}

const unsigned int jsonvalidation_validate_isomap_tileset(const json_t *isomap) {
}

const unsigned int jsonvalidation_validate_tile(const json_t *tile) {
}

const unsigned int jsonvalidation_validate_tile_id(const json_t *tile) {
}

const unsigned int jsonvalidation_validate_tile_filename(const json_t *tile) {
}

const unsigned int jsonvalidation_validate_tile_incoming(const json_t *tile) {
}

const unsigned int jsonvalidation_validate_tile_outgoing(const json_t *tile) {
}

const unsigned int jsonvalidation_validate_isomap_layers(const json_t *layers) {
}

const unsigned int jsonvalidation_validate_layer(const json_t *layer) {
}

const unsigned int jsonvalidation_validate_layer_numrows(const json_t *layer) {
}

const unsigned int jsonvalidation_validate_layer_numcols(const json_t *layer) {
}

const unsigned int jsonvalidation_validate_layer_offset(const json_t *layer) {
}

const unsigned int jsonvalidation_validate_layer_data(const json_t *layer) {
}
