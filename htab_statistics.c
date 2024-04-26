// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Prints statistics of hash table

#include "htab.h"
#include "htab_private.h"

void htab_statistics(const htab_t *t) {
    size_t totalBuckets = htab_bucket_count(t);
    size_t totalItems = htab_size(t);
    size_t listCount = 0;
    size_t maxItem = 0;
    size_t minItem = totalItems;

    for (size_t i = 0; i < totalBuckets; i++) {
        size_t count = 0;
        htab_item_t *item = t->arr[i];

        if(item == NULL) {
            continue;
        }

        while (item != NULL) {
            count++;
            item = item->next;
        }
        
        listCount++;
        maxItem = count > maxItem ? count : maxItem;
        minItem = count < minItem ? count : minItem;
    }

    double avgItem = 0;
    if(totalItems != 0) {
        avgItem = (double) totalItems / listCount;
    }

    fprintf(stderr, "Statistics of hash table:\n");
    fprintf(stderr ,"\t- number of buckets: %zu\n", totalBuckets);
    fprintf(stderr ,"\t- number of items: %zu\n", totalItems);
    fprintf(stderr ,"\t- average length of list: %f\n", avgItem);
    fprintf(stderr ,"\t- maximum length of list: %zu\n", maxItem);
    fprintf(stderr ,"\t- minimum length of list: %zu\n", minItem);
}