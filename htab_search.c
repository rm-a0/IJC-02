// htab_search.c
// Solution IJC-DU2, Task B, 23.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <string.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"

// Function that searches for item in a hash table based on its key
htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    unsigned index = (htab_hash_function(key) % t->arr_size);
    htab_item_t *item = t->arr[index];

    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            return &(item->pair);
        }
        item = item->next;
    }

    return NULL;
}

// Function that searches for item in hash table based on its key
// If the item is found return pointer, otherwise add the item to the table
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    // Check if the item already exists
    htab_pair_t *existing_pair = htab_find(t, key);
    if (existing_pair != NULL) {
        return existing_pair;
    }

    unsigned index = htab_hash_function(key) % t->arr_size;

    htab_item_t *new_pair = malloc(sizeof(htab_item_t));
    if (new_pair == NULL) {
        return NULL;
    }

    new_pair->pair.key = malloc(strlen(key) + 1);
    if (new_pair->pair.key == NULL) {
        return NULL;
    }

    strcpy((char *)new_pair->pair.key, key);
    new_pair->pair.value = 0;
    new_pair->next = t->arr[index];
    t->arr[index] = new_pair;
    t->size++;

    // Return a pointer to the newly added item
    return &(new_pair->pair);
}