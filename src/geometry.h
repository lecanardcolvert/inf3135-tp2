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

/**
 * A box in the 3D space
 */
struct box {
    int xmin; // The minimum x-coordinate
    int ymin; // The minimum y-coordinate
    int zmin; // The minimum z-coordinate
    int xmax; // The maximum x-coordinate
    int ymax; // The maximum y-coordinate
    int zmax; // The maximum z-coordinate
};

// Functions //
// --------- //

/**
 * Print a location to stdout
 *
 * @param v  The location to print
 */
void geometry_print_location(const struct location *l);

/**
 * Print a vector to stdout
 *
 * @param v  The vector to print
 */
void geometry_print_vect(const struct vect *v);

/**
 * Print a box to stdout
 *
 * @param b  The box
 */
void geometry_print_box(const struct box *b);

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
