// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Header file for private hash table members

#ifndef HTAB_H_PRIVATE__
#define HTAB_H_PRIVATE__

#include "htab.h"

struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
};

typedef struct htab_item htab_item_t;

struct htab {
    size_t arr_size;
    size_t size;
    htab_item_t *arr[];
};

#endif // HTAB_H__