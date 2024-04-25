// htab_create.c
// Solution IJC-DU2, Task B, 22.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"

// Function that allocates and initializes hash table
htab_t *htab_init(const size_t n) {
    htab_t *htab = malloc(sizeof(htab_t));
    if (htab == NULL) {
        return NULL;
    }

    htab->size = 0;
    htab->arr_size = n;

    htab->arr = malloc(n * sizeof(htab_item_t*));
    if (htab->arr == NULL) {
        free(htab);
        return NULL;
    }

    return htab;
}

// Function that returns number of items in hash table
size_t htab_size(const htab_t *t) {
    return t->size;
}

// Function that returns number of buckets in hash table
size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}
