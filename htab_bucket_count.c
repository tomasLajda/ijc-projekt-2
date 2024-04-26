// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Returns number of buckets in hash table

#include "htab.h"
#include "htab_private.h"

size_t htab_bucket_count(const htab_t * t) {
    return t->arr_size;
}