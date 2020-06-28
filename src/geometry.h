#ifndef GEOMETRY_H
#define GEOMETRY_H

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

#endif
