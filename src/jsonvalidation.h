/**
 * jsonvalidation.h
 *
 * Validates a JSON file based on the logic of an isomap object.
 *
 * @author  Alexandre H. Bourdeau (HAMA12128907)
 */
#ifndef JSONVALIDATION_H
#define JSONVALIDATION_H

#include <stdio.h>
#include <jansson.h>

// Validation functions //
// -------------------- //

/**
 * Validates the entire JSON file
 * If the file passes all validations, then error code 0 is returned
 * 
 * @param  file  The input stream
 * @return 0 if the file is valid
 *         A number between 2 to 24 depending on the error
 */
const unsigned int jsonvalidation_validate_file(const FILE *file);

/**
 * Validates that the JSON file has only 1 object in root
 * 
 * @param  json_root The root of the JSON file
 * @return 0 if it has only 1 object in root
 *         2 if there is more than 1 object
 */
const unsigned int jsonvalidation_validate_single_root_key(json_t *json_root);

/**
 * Validates the data of the 4 mandatory keys :
 * 'tile-width', 'z-offset', 'tileset', 'layers'
 * 
 * @param  json_root The root of the JSON file
 * @return 0 if the 4 keys are valid
 *         Either 4, 5, 8, 9 if there is an invalid key
 */
const unsigned int jsonvalidation_validate_mandatory_keys(json_t *json_root);

/**
 * Validates the 'tile-width' key. It is the width of a single tile
 * It must be an int (usually a power of 2)
 * 
 * @param  json_root The root of the JSON file
 * @return 0 if tile-width is valid,
 *         7 if tile-width in invalid 
 */
const unsigned int jsonvalidation_validate_tilewidth(json_t *json_root);

/**
 * Validates the 'z-offset' key. It is the vertical offset between two layers
 * It must be an int
 * 
 * @param  json_root The root of the JSON file
 * @return 0 if z-offset is valid
 *         8 if z-offset is invalid
 */
const unsigned int jsonvalidation_validate_zoffset(const json_t *json_root);

/**
 * Validates the 'tileset' key and its 'tile' objects
 * It contains the information about the different tiles
 * 
 * @param  json_tileset The root of the JSON tileset object array
 * @return              0 if all the tiles are valid
 *                      A number between 9 to 16 depending on the error
 */
const unsigned int jsonvalidation_validate_tileset(const json_t *json_tileset);

/**
 * Validates the 'id' key of a 'tile' object
 * It must be unique
 * 
 * @param  json_tile The root of the JSON tile object
 * @return           0 if id is valid
 *                   9 if key is missing, 13 if id is invalid
 */
const unsigned int jsonvalidation_validate_tile_id(const json_t *json_tile);

/**
 * Validates the 'filename' key of a 'tile' object
 * If the path is relative then it must be relative of the directory
 * where the program is run
 * 
 * @param  json_tile The root of the JSON tile object
 * @return           0 if filename is valid
 *                   10 if key is missing, 14 if filename is invalid
 */
const unsigned int jsonvalidation_validate_tile_filename(const json_t *json_tile);

/**
 * Validates the 'incoming' key of a 'tile' object
 * It is a list of valid incoming moves from another tile
 * It must be of the [x,y,z] format. Each coordinate must be an int
 * 
 * @param  json_tile The root of the JSON tile object
 * @return           0 if incoming is valid
 *                   11 if key is missing, 15 if incoming is invalid
 */
const unsigned int jsonvalidation_validate_tile_incoming(const json_t *json_tile);

/**
 * Validates the 'outgoing' key of a 'tile' object
 * It is a list of valid outgoing moves to another tile
 * It must be of [x,y,z] format. Each coordinate must be an int
 * 
 * @param  json_tile The root of the JSON tile object
 * @return           0 if outgoing is valid
 *                   12 if key is missing, 16 if outgoing is invalid
 */
const unsigned int jsonvalidation_validate_tile_outgoing(const json_t *json_tile);

/**
 * Validates the 'layers' key and its 'layer' objects
 * It contains the information about the different tiles
 * 
 * @param  json_layers The root of the JSON layers object array
 * @return             0 if all the layers are valid
 *                     A number between 17 to 24 depending on the error
 */
const unsigned int jsonvalidation_validate_layers(const json_t *json_layers);

/**
 * Validates the 'num-rows' key of a 'layer' object It is the number of rows of 
 * the layer
 * It must be an int
 * 
 * @param  json_layer The root of the JSON layer object
 * @return            0 if num-rows is valid
 *                    17 if key is missing, 21 if num-rows is invalid
 */
const unsigned int jsonvalidation_validate_layer_numrows(const json_t *json_layer);

/**
 * Validates the 'num-cols' key of a 'layer' object. Iis the number of columns
 * of the layer
 * It must be an int
 * 
 * @param  json_layer The root of the JSON layer object
 * @return            0 if num-cols is valid
 *                    18 if key is missing, 22 if num-cols is invalid
 */
const unsigned int jsonvalidation_validate_layer_numcols(const json_t *json_layer);

/**
 * Validates the 'offset' key of a 'layer' object. It is the offset between 
 * this layer and the origin
 * It must be of [x,y,z] format. Each coordinate must be an int
 * 
 * @param  json_layer The root of the JSON layer object
 * @return            0 if offset is valid
 *                    19 if key is missing, 23 if offset is invalid
 */
const unsigned int jsonvalidation_validate_layer_offset(const json_t *json_layer);

/**
 * Validates the 'data' key of a 'layer' object. It is a unidimensional array
 * which contains the information about the tiles in the layer.
 * Each tile must either match with '0' or with a tile id
 * 
 * @param  json_layer The root of the JSON layer object
 * @return            0 if data is valid
 *                    20 if key is missing, 24 if data is invalid
 */
const unsigned int jsonvalidation_validate_layer_data(const json_t *json_layer);

#endif
