// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Clears values of hash table

#include "htab.h"
#include "htab_private.h"

void htab_clear(htab_t * t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item = t->arr[i];
        htab_item_t *nextItem = NULL;

        while (item != NULL) {
            nextItem = item->next;
            free((char *)item->pair.key);
            free(item);
            item = nextItem;
        }

        t->arr[i] = NULL;
    }

    t->size = 0;
}