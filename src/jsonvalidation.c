#include "jsonvalidation.h"

/**
 * Validation errors
 */
enum status {
    JSONVALIDATION_OK                           = 0,
    JSONVALIDATION_ERROR                        = 1,
    JSONVALIDATION_TOO_MANY_ROOT_OBJECTS        = 2,
    JSONVALIDATION_MISSING_TILEWIDTH_KEY        = 3,
    JSONVALIDATION_MISSING_ZOFFSET_KEY          = 4,
    JSONVALIDATION_MISSING_TILESET_KEY          = 5,
    JSONVALIDATION_MISSING_LAYERS_KEY           = 6,
    JSONVALIDATION_BAD_TILEWIDTH_VALUE          = 7,
    JSONVALIDATION_BAD_ZOFFSET_VALUE            = 8,
    JSONVALIDATION_MISSING_TILE_ID_KEY          = 9,
    JSONVALIDATION_MISSING_TILE_FILENAME_KEY    = 10,
    JSONVALIDATION_MISSING_INCOMING_KEY         = 11,
    JSONVALIDATION_MISSING_OUTGOING_KEY         = 12,
    JSONVALIDATION_BAD_TILE_ID_VALUE            = 13,
    JSONVALIDATION_BAD_TILE_FILENAME_VALUE      = 14,
    JSONVALIDATION_BAD_TILE_INCOMING_VALUE      = 15,
    JSONVALIDATION_BAD_TILE_OUTGOING_VALUE      = 16,
    JSONVALIDATION_MISSING_LAYER_NUMROWS_KEY    = 17,
    JSONVALIDATION_MISSING_LAYER_NUMCOLS_KEY    = 18,
    JSONVALIDATION_MISSING_LAYER_OFFSET_KEY     = 19,
    JSONVALIDATION_MISSING_LAYER_DATA_KEY       = 20,
    JSONVALIDATION_BAD_LAYER_NUMROWS_VALUE      = 21,
    JSONVALIDATION_BAD_LAYER_NUMCOLS_VALUE      = 22,
    JSONVALIDATION_BAD_LAYER_OFFSET_VALUE       = 23,
    JSONVALIDATION_BAD_LAYER_DATA_VALUE         = 24
};

// Validation functions //
// -------------------- //


