#include "htab.h"
#include "htab_private.h"

bool htab_erase(htab_t * t, htab_key_t key) {
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    htab_item_t *item = t->arr[index];
    htab_item_t *prev = NULL;

    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            if (prev == NULL) {
                t->arr[index] = item->next;
            } else {
                prev->next = item->next;
            }

            free(item->pair.key);
            item->pair.value = 0;
            
            free(item);
            t->size--;
            
            return true;
        }
        
        prev = item;
        item = item->next;
    }

    return false;
}