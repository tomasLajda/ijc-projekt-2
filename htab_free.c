// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Frees hash table

#include "htab.h"
#include "htab_private.h"

void htab_free(htab_t * t) {
    htab_clear(t);
    
    free(t->arr);
    t->arr_size = 0;
    free(t);
    t = NULL;
}