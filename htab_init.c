// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Implementation of htab_init function

#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t n) {
  htab_t *t = malloc(sizeof(htab_t) + n * sizeof(htab_item_t *));
  if (t == NULL) {
    exit(EXIT_FAILURE);
  }

  t->arr_size = n;
  t->size = 0;
  for (size_t i = 0; i < n; i++) {
    t->arr[i] = NULL;
  }

  return t;
}