#include "geometry.h"
#include <stdio.h>

void geometry_print_vect(const struct vect *v) {
    printf("(%d,%d,%d)", v->dx, v->dy, v->dz);
}

bool geometry_equal_vect(const struct vect *v1,
                         const struct vect *v2) {
    return v1->dx == v2->dx &&
           v1->dy == v2->dy &&
           v1->dz == v2->dz;
}
