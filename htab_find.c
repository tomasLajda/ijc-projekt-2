// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Finds item in hash table

#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    htab_item_t *item = t->arr[index];

    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            return &item->pair;
        }

        item = item->next;
    }

    return NULL;
}