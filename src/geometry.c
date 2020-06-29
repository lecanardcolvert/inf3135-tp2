#include "geometry.h"
#include <stdio.h>

struct vect geometry_box_to_vect(const struct box *b) {
    return (struct vect){b->xmax - b->xmin,
                         b->ymax - b->ymin,
                         b->zmax - b->zmin};
}

void geometry_print_location(FILE *stream, const struct location *l) {
    fprintf(stream, "location(%d,%d,%d)", l->x, l->y, l->z);
}

void geometry_print_vect(FILE *stream, const struct vect *v) {
    fprintf(stream, "vect(%d,%d,%d)", v->dx, v->dy, v->dz);
}

void geometry_print_box(FILE *stream, const struct box *v) {
    fprintf(stream, "box(%d,%d,%d;%d,%d,%d)",
            v->xmin, v->ymin, v->zmin,
            v->xmax, v->ymax, v->zmax);
}

bool geometry_equal_vect(const struct vect *v1,
                         const struct vect *v2) {
    return v1->dx == v2->dx &&
           v1->dy == v2->dy &&
           v1->dz == v2->dz;
}
