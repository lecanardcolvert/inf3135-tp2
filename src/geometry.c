#include "geometry.h"
#include <stdio.h>

void geometry_print_location(const struct location *l) {
    printf("location(%d,%d,%d)", l->x, l->y, l->z);
}

void geometry_print_vect(const struct vect *v) {
    printf("vect(%d,%d,%d)", v->dx, v->dy, v->dz);
}

void geometry_print_box(const struct box *v) {
    printf("box(%d,%d,%d;%d,%d,%d)",
           v->xmin, v->ymin, v->zmin,
           v->xmax, v->ymax, v->zmax);
}

bool geometry_equal_vect(const struct vect *v1,
                         const struct vect *v2) {
    return v1->dx == v2->dx &&
           v1->dy == v2->dy &&
           v1->dz == v2->dz;
}
