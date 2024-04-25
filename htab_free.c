#include "htab.h"
#include "htab_private.h"

void htab_free(htab_t * t) {
    htab_clear(t);
    t->arr_size = 0;
    t->size = 0;
    free(t);
    t = NULL;
}