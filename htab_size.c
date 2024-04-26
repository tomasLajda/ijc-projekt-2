// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Returns number of items in hash table

#include "htab.h"
#include "htab_private.h"

size_t htab_size(const htab_t * t) {
    return t->size;
}