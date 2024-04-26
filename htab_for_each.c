// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Calls function f for each item in hash table

#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < htab_bucket_count(t); i++) {
        htab_item_t *item = t->arr[i];

        while (item != NULL) {
            f(&item->pair);
            item = item->next;
        }
    }
}