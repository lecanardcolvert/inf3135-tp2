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
 *         A number between 2 to 29 depending on the error (see jsonvalidation.c
 *         for the error codes meanings) 
 */
const unsigned int jsonvalidation_validate_file(FILE* file);

/**
 * Validates the root of the JSON file
 * There must be only one 'isomap' object per file
 * 
 * @param  json_root The root of the JSON file
 * @return 0 if there are no errors,
 *         2 if there is no 'isomap' object, 
 *         3 if it is another type than an object
 */
const unsigned int jsonvalidation_validate_root(json_t *json_root);

/**
 * Validates the keys and values of the 'isomap' object
 * 
 * @param  isomap The root of the 'isomap' object
 * @return 0 if the keys and values are valid
 *         A number from 4 to 29 if something is invalid
 */
const unsigned int jsonvalidation_validate_isomap(const json_t *isomap);

/**
 * Validates the 'tile-width' key of a 'isomap' object
 * It must be an int (usually a power of 2)
 * 
 * @param  isomap The root of the 'isomap' object
 * @return 0 if tile-width key and value are valid,
 *         4 if tile-width key is missing, 
 *         5 if tile-width value is invalid
 */
const unsigned int jsonvalidation_validate_isomap_tilewidth(const json_t *isomap);

/**
 * Validates the 'z-offset' key of a 'isomap' object
 * It must be an int
 * 
 * @param  isomap The root of the 'isomap' object
 * @return 0 if z-offset key and value are valid,
 *         6 if z-offset key is missing, 
 *         7 if z-offset value is invalid
 */
const unsigned int jsonvalidation_validate_isomap_zoffset(const json_t *isomap);

/**
 * Validates the 'tileset' key of a 'isomap' object and its 'tile' objects
 * 
 * @param  isomap The root of the 'isomap' object
 * @return 0 if tileset and its 'tile' objects are valid,
 *         8 if tileset key is missing,
 *         9 if tileset value is invalid, 
 *         A number from 12 to 20 if there is an error with a tile
 */
const unsigned int jsonvalidation_validate_isomap_tileset(const json_t *isomap);

/**
 * Validates a 'tile' object of a 'tileset' object
 * It must be an object
 * 
 * @param  tile The root of the JSON tile object
 * @return 0 if tile keys and values are valid,
 *         12 if tile value is invalid,
 *         A number from 13 to 20 if there is an error with a key or value
 */
const unsigned int jsonvalidation_validate_tile(const json_t *tile);

/**
 * Validates the 'id' key of a 'tile' object
 * It must be unique
 * 
 * @param  tile The root of the JSON tile object
 * @return 0 if id key and value are valid,
 *         13 if id key is missing,
 *         14 if id value is invalid 
 */
const unsigned int jsonvalidation_validate_tile_id(const json_t* tile)
;

/**
 * Validates the 'filename' key of a 'tile' object
 * If the path is relative then it must be relative of the directory
 * where the program is run
 * 
 * @param  tile The root of the JSON tile object
 * @return 0 if filename key and value are valid,
 *         15 if filename key is missing,
 *         16 if filename value is invalid 
 */
const unsigned int jsonvalidation_validate_tile_filename(const json_t *tile);

/**
 * Validates the 'incoming' key of a 'tile' object
 * It must be of the [x,y,z] format. Each coordinate must be an int
 * 
 * @param  tile The root of the JSON tile object
 * @return 0 if incoming key and values are valid,
 *         17 if incoming key is missing,
 *         18 if incoming value is invalid  
 */
const unsigned int jsonvalidation_validate_tile_incoming(const json_t *tile);

/**
 * Validates the 'outgoing' key of a 'tile' object
 * It must be of [x,y,z] format. Each coordinate must be an int
 * 
 * @param  tile The root of the JSON tile object
 * @return 0 if outgoing key and values are valid,
 *         19 if outgoing key is missing,
 *         20 if outgoing value is invalid
 */
const unsigned int jsonvalidation_validate_tile_outgoing(const json_t *tile);

/**
 * Validates the 'layers' key of a 'isomap' object and its 'layer' objects
 * 
 * @param  isomap The root of the 'isomap' object
 * @return 0 if layers and its 'layer' objects are valid,
 *         10 if layers key is missing,
 *         11 if layers value is invalid, 
 *         A number from 21 to 29 if there is an error with a layer
 */
const unsigned int jsonvalidation_validate_isomap_layers(const json_t *layers);

/**
 * Validates a 'layer' object of a 'layers' object
 * It must be an object
 * 
 * @param  layer The root of the JSON layer object
 * @return 0 if layer keys and values are valid,
 *         21 if layer value is invalid,
 *         A number from 22 to 29 if there is an error with a key or value
 */
const unsigned int jsonvalidation_validate_layer(const json_t *layer);

/**
 * Validates the 'num-rows' key of a 'layer' object
 * It must be an int
 * 
 * @param  layer The root of the JSON layer object
 * @return 0 if num-rows key and values are valid,
 *         22 if num-rows key is missing,
 *         23 if num-rows value is invalid
 */
const unsigned int jsonvalidation_validate_layer_numrows(const json_t *layer);

/**
 * Validates the 'num-cols' key of a 'layer' object.
 * It must be an int
 * 
 * @param  layer The root of the JSON layer object
 * @return 0 if num-cols key and values are valid,
 *         24 if num-cols key is missing,
 *         25 if num-cols value is invalid
 */
const unsigned int jsonvalidation_validate_layer_numcols(const json_t *layer);

/**
 * Validates the 'offset' key of a 'layer' object.
 * It must be of [x,y,z] format. Each coordinate must be an int
 * 
 * @param  layer The root of the JSON layer object
 * @return 0 if offset key and values are valid,
 *         26 if offset key is missing,
 *         27 if offset value is invalid
 */
const unsigned int jsonvalidation_validate_layer_offset(const json_t *layer);

/**
 * Validates the 'data' key of a 'layer' object. It is a unidimensional array
 * which contains the information about the tiles in the layer.
 * Each tile must either match with '0' or with a tile id
 * 
 * @param  layer The root of the JSON layer object
 * @return 0 if data key and values are valid,
 *         28 if data key is missing,
 *         29 if data value is invalid
 */
const unsigned int jsonvalidation_validate_layer_data(const json_t *layer);

#endif
