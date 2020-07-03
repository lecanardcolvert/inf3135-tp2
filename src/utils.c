#include "utils.h"

#include <stdlib.h>
#include <string.h>

char *utils_strdup(const char *s) {
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p) {
        memcpy(p, s, size);
    }
    return p;
}
