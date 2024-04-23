// htab_destroy.c
// Solution IJC-DU2, Task B, 22.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"

// Function that clears all items from hash table
void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *current = t->arr[i];
        while (current != NULL) {
            htab_item_t *temp = current;
            current = current->next;
            free(temp);
        }
        t->arr[i] = NULL;
    }
    t->size = 0;
}

// Function that frees allocated memory for hash table
void htab_free(htab_t *t) {
    htab_clear(t);
    free(t);
}