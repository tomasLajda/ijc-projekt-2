// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Looks up item in hash table and adds it if it does not exist

#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    htab_item_t *item = t->arr[index];

    // Find item
    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            return &item->pair;
        }

        item = item->next;
    }

    htab_item_t *newItem = malloc(sizeof(htab_item_t));
    if (newItem == NULL) {
        return NULL;
    }

    char* keyCopy = calloc(strlen(key) + 1, sizeof(char));
    if(keyCopy == NULL) {
        free(newItem);
        return NULL;
    }

    // Add item
    keyCopy = strcpy(keyCopy, key);
    newItem->pair.key = keyCopy;
    newItem->pair.value = 0;
    // Insert to the beginning of the list
    newItem->next = t->arr[index];
    t->arr[index] = newItem;
    t->size++;

    return &newItem->pair;
}