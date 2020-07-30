#include "jsonvalidation.h"
#include <unistd.h>

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
    JSONVALIDATION_BAD_LAYER_DATA_VALUE         = 29,
    
    JSONVALIDATION_NONUNIQUE_TILE_ID            = 30,
    JSONVALIDATION_NONEXISTENT_TILE_FILE        = 31,
    JSONVALIDATION_BAD_DIRECTION_VALUE          = 32,
    JSONVALIDATION_NONRECTANGULAR_DATA          = 33
};

// Validation functions //
// -------------------- //

unsigned int jsonvalidation_validate_file(FILE *file) {
    unsigned int error_no = JSONVALIDATION_OK;
    
    json_error_t error;
    json_t *json_root = json_loadf(file, 0, &error);
    
    error_no = jsonvalidation_validate_root(json_root);
    
    free(json_root);
    
    return error_no;
}

unsigned int jsonvalidation_validate_root(json_t *json_root) {
    unsigned int error_no = JSONVALIDATION_OK;
    
    if ((json_root != NULL) && (json_is_object(json_root))) {
        error_no = jsonvalidation_validate_isomap(json_root);
    } else if (json_root == NULL) {
        error_no = JSONVALIDATION_MISSING_ISOMAP;
    } else if (!json_is_object(json_root)) {
        error_no = JSONVALIDATION_BAD_ISOMAP_VALUE;
    }
  
    return error_no;    
}

unsigned int jsonvalidation_validate_isomap(const json_t *isomap) {
    unsigned int error_no = JSONVALIDATION_OK;
    unsigned int validations_no = 4;
    unsigned int validations[4] = {
        jsonvalidation_validate_isomap_tilewidth(isomap),
        jsonvalidation_validate_isomap_zoffset(isomap),
        jsonvalidation_validate_isomap_tileset(isomap),
        jsonvalidation_validate_isomap_layers(isomap)
    };
        
    for (int i = 0; i < validations_no; ++i) {
        if ((error_no = validations[i]) != JSONVALIDATION_OK) { 
            break;
        }
    }
    
    return error_no;
}

unsigned int jsonvalidation_validate_isomap_tilewidth(const json_t *isomap) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(isomap, "tile-width");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_ISOMAP_TILEWIDTH_KEY;
    } else if (!json_is_integer(key)) {
        error_no = JSONVALIDATION_BAD_ISOMAP_TILEWIDTH_VALUE;
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_isomap_zoffset(const json_t *isomap) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(isomap, "z-offset");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_ISOMAP_ZOFFSET_KEY;
    } else if (!json_is_integer(key)) {
        error_no = JSONVALIDATION_BAD_ISOMAP_ZOFFSET_VALUE;
    }

    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_isomap_tileset(const json_t *isomap) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(isomap, "tileset");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_ISOMAP_TILESET_KEY;
    } else if (!json_is_array(key)) {
        error_no = JSONVALIDATION_BAD_ISOMAP_TILESET_VALUE;
    } else {
        const size_t array_size = json_array_size(key);
        json_t *tile;
        int id_list[array_size];
        
        for (int i = 0; i < array_size; ++i) {
            tile = json_array_get(key, i);
            if ((error_no = jsonvalidation_validate_tile(tile, &id_list[i])) 
                    != JSONVALIDATION_OK) {
                break;
            }
        }
        
        // Validation des 'id' uniques
        for (int i = 0; i < array_size; ++i) {
            for (int j = 0; j < array_size; ++j) {
                if ((i != j) && (id_list[i] == id_list[j])) {
                    error_no = JSONVALIDATION_NONUNIQUE_TILE_ID;
                }                
            }
        }

        free(tile);
    }

    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_tile(const json_t *tile, int *id) {
    unsigned int error_no = JSONVALIDATION_OK;
    
    if (!json_is_object(tile)) {
        error_no = JSONVALIDATION_BAD_TILE_VALUE;
    } else {
        unsigned int validations_no = 4;
        unsigned int validations[4] = {
            jsonvalidation_validate_tile_id(tile, id),
            jsonvalidation_validate_tile_filename(tile),
            jsonvalidation_validate_tile_incoming(tile),
            jsonvalidation_validate_tile_outgoing(tile)
        };
    
        for (int i = 0; i < validations_no; ++i) {
            if ((error_no = validations[i]) != JSONVALIDATION_OK) {
                break;
            }
        }
    }
    
    return error_no;
}

unsigned int jsonvalidation_validate_tile_id(const json_t *tile, int *id) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(tile, "id");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_TILE_ID_KEY;
    } else if (!json_is_integer(key)) {
        error_no = JSONVALIDATION_BAD_TILE_ID_VALUE;
    } else {
        *id = json_integer_value(key);
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_tile_filename(const json_t *tile) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(tile, "filename");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_TILE_FILENAME_KEY;
    } else if (!json_is_string(key)) {
        error_no = JSONVALIDATION_BAD_TILE_FILENAME_VALUE;
    } else {        
        const char* filename = json_string_value(key);
        if (access(filename, R_OK) != -1) {
            error_no = JSONVALIDATION_NONEXISTENT_TILE_FILE;
        }
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_tile_incoming(const json_t *tile) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(tile, "incoming");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_TILE_INCOMING_KEY;
    } else if (!json_is_array(key)) {
        error_no = JSONVALIDATION_BAD_TILE_INCOMING_VALUE;
    } else {
        const size_t array_size = json_array_size(key);
        json_t *incoming;
        
        for (int i = 0; i < array_size; ++i) {
            incoming = json_array_get(key, i);
            if ((error_no = jsonvalidation_validate_tile_direction(incoming)) 
                    != JSONVALIDATION_OK) {
                error_no = JSONVALIDATION_BAD_TILE_INCOMING_VALUE;
                break;
            }
        }
        free(incoming);
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_tile_outgoing(const json_t *tile) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(tile, "outgoing");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_TILE_OUTGOING_KEY;
    } else if (!json_is_array(key)) {
        error_no = JSONVALIDATION_BAD_TILE_OUTGOING_VALUE;
    } else {
        const size_t array_size = json_array_size(key);
        json_t *outgoing;
        
        for (int i = 0; i < array_size; ++i) {
            outgoing = json_array_get(key, i);
            if ((error_no = jsonvalidation_validate_tile_direction(outgoing)) 
                    != JSONVALIDATION_OK) {
                error_no = JSONVALIDATION_BAD_TILE_OUTGOING_VALUE;
                break;
            }
        }
        free(outgoing);
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_tile_direction(const json_t *direction) {
    unsigned int error_no = JSONVALIDATION_OK;
    
    if (!json_is_array(direction)) {
        error_no = JSONVALIDATION_OTHER_ERROR;
    } else {
        const size_t array_size = json_array_size(direction);
        json_t *variation;
        
        for (int i = 0; i < array_size; ++i) {
            variation = json_array_get(direction, i);
            
            if (!json_is_integer(variation)) {
                error_no = JSONVALIDATION_OTHER_ERROR;
            } else {
                int variation_value = json_integer_value(variation);
                if ((-1 > variation_value) || (1 < variation_value)) {
                    error_no = JSONVALIDATION_BAD_DIRECTION_VALUE;
                }
            }
        }
        
        free(variation);
    }
    
    return error_no;
}

unsigned int jsonvalidation_validate_isomap_layers(const json_t *isomap) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(isomap, "layers");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_ISOMAP_LAYERS_KEY;
    } else if (!json_is_array(key)) {
        error_no = JSONVALIDATION_BAD_ISOMAP_LAYERS_VALUE;
    } else {
        const size_t array_size = json_array_size(key);
        json_t *layer;
        
        for (int i = 0; i < array_size; ++i) {
            layer = json_array_get(key, i);
            if ((error_no = jsonvalidation_validate_layer(layer)) 
                    != JSONVALIDATION_OK) {
                break;
            }
        }
        free(layer);
    }

    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_layer(const json_t *layer) {
    unsigned int error_no = JSONVALIDATION_OK;
    
    if (!json_is_object(layer)) {
        error_no = JSONVALIDATION_BAD_LAYER_VALUE;
    } else {
        int numrows, numcols;
        unsigned int validations_no = 4;
        unsigned int validations[4] = {
            jsonvalidation_validate_layer_numrows(layer, &numrows),
            jsonvalidation_validate_layer_numcols(layer, &numcols),
            jsonvalidation_validate_layer_offset(layer),
            jsonvalidation_validate_layer_data(layer, numrows*numcols)
        };
        
        for (int i = 0; i < validations_no; ++i) {
            if ((error_no = validations[i]) != JSONVALIDATION_OK) {
                break;
            }
        }
    }
    
    return error_no;
}

unsigned int jsonvalidation_validate_layer_numrows(const json_t *layer, 
                                                   int *numrows) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(layer, "num-rows");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_LAYER_NUMROWS_KEY;
    } else if (!json_is_integer(key)) {
        error_no = JSONVALIDATION_BAD_LAYER_NUMROWS_VALUE;
    } else {
        *numrows = json_integer_value(key);
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_layer_numcols(const json_t *layer,
                                                   int *numcols) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(layer, "num-cols");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_LAYER_NUMCOLS_KEY;
    } else if (!json_is_integer(key)) {
        error_no = JSONVALIDATION_BAD_LAYER_NUMCOLS_VALUE;
    } else {
        *numcols = json_integer_value(key);
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_layer_offset(const json_t *layer) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(layer, "offset");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_LAYER_OFFSET_KEY;
    } else if (!json_is_array(key)) {
        error_no = JSONVALIDATION_BAD_LAYER_OFFSET_VALUE;
    } else {
        const size_t array_size = json_array_size(key);
        json_t *offset_pos;
        
        for (int i = 0; i < array_size; ++i) {
            offset_pos = json_array_get(key, i);
            if (!json_is_integer(offset_pos)) {
                error_no = JSONVALIDATION_BAD_LAYER_OFFSET_VALUE;
                break;
            }
        }
        
        free(offset_pos);
    }
    
    free(key);
    return error_no;
}

unsigned int jsonvalidation_validate_layer_data(const json_t *layer, 
                                                int dimensions) {
    unsigned int error_no = JSONVALIDATION_OK;
    json_t *key = json_object_get(layer, "data");
    
    if (key == NULL) {
        error_no = JSONVALIDATION_MISSING_LAYER_DATA_KEY;
    } else if (!json_is_array(key)) {
        error_no = JSONVALIDATION_BAD_LAYER_DATA_VALUE;
    } else {
        const size_t array_size = json_array_size(key);
        json_t *data = NULL;
        
        if (array_size != dimensions) {
            error_no = JSONVALIDATION_NONRECTANGULAR_DATA;
        } else {
            for (int i = 0; i < array_size; ++i) {
                data = json_array_get(key, i);
                if (!json_is_integer(data)) {
                    error_no = JSONVALIDATION_BAD_LAYER_DATA_VALUE;
                    break;
                }
            }
        }
 
        free(data);
    }

    free(key);
    return error_no;
}
