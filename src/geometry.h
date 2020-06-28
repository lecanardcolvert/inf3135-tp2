#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>

/**
 * A location in the 3D space
 */
struct location {
    int x; // The x-coordinate
    int y; // The y-coordinate
    int z; // The z-coordinate
};

/**
 * A direction in the 3D space
 */
struct vect {
    int dx; // The x variation
    int dy; // The y variation
    int dz; // The z variation
};

// Functions //
// --------- //

/**
 * Print a vector to stdout
 *
 * @param v  The vector to print
 */
void geometry_print_vect(const struct vect *v);

/**
 * Indicate if two vectors are equal
 *
 * @param v1  The first vector
 * @param v2  The second vector
 * @return    true if the two vectors are the same
 *            false otherwise
 */
bool geometry_equal_vect(const struct vect *v1,
                         const struct vect *v2);

#endif
