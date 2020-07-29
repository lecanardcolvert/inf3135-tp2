/**
 * jsonvalidation.h
 *
 * Validates a JSON file based on the logic of an isomap object
 *
 * @author  Alexandre H. Bourdeau (HAMA12128907)
 */
#ifndef JSONVALIDATION_H
#define JSONVALIDATION_H

#include <stdio.h>

// Types //
// ----- //

struct jsonvalidation {
    const FILE *file;
    int status;
};

// Functions //
// --------- //

/**
 * Validates the entire JSON file
 */


/**
 * Validates that the JSON file has only 1 object in root
 */


/** 
 * Validates that the JSON file has 4 mandatory keys :
 * 'tile-width', 'z-offset', 'tileset', 'layers'
 */


/**
 * Validates the 'tile-width' key
 * It is the width of a single tile
 * It must be an int (usually a power of 2)
 */


/**
 * Validates the 'z-offset' key
 * It is the vertical offset between two layers
 * It must be an int
 */


/**
 * Validates the 'tileset' key and its 'tile' objects
 * It contains the information about the different tiles
 */


/**
 * Validates the 'id' key of a 'tile' object
 * It must be unique
 */


/**
 * Validates the 'filename' key of a 'tile' object
 * If the path is relative then it must be relative of the directory
 * where the program is run
 */


/**
 * Validates the 'incoming' key of a 'tile' object
 * It is a list of valid incoming moves from another tile
 * It must be of the [x,y,z] format. Each coordinate must be an int
 */


/**
 * Validates the 'outgoing' key of a 'tile' object
 * It is a list of valid outgoing moves to another tile
 * It must be of [x,y,z] format. Each coordinate must be an int
 */


/**
 * Validates the 'layers' key and its 'layer' objects
 * It contains the information about the different tiles
 */


/**
 * Validates the 'num-rows' key of a 'layer' object
 * It is the number of rows of the layer
 * It must be an int
 */

/**
 * Validates the 'num-col' key of a 'layer' object
 * It is the number of columns of the layer
 * It must be an int
 */


/** 
 * Validates the 'offset' key of a 'layer' object
 * It is the offset between this layer and the origin
 * It must be of [x,y,z] format. Each coordinate must be an int
 */


/**
 * Validates the 'data' key of a 'layer' object
 * It is a unidimensional array which contains the information about the tiles
 * in the layer. 
 * Each tile must either match with '0' or with a tile id
 */


#endif
