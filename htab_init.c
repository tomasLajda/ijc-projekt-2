// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Initializes hash table

#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(const size_t n) {
  htab_t *t = malloc(sizeof(htab_t));
  if (t == NULL) {
    return NULL;
  }

  t->arr_size = n;
  t->size = 0;
  
  t->arr = calloc(n, sizeof(htab_item_t*));
  if (t->arr == NULL) {
    free(t);
    return NULL;
  }

  return t;
}