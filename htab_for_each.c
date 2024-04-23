// htab_for_each.c
// Solution IJC-DU2, Task B, 23.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include "htab.h"
#include "htab_structs.h"

// Function that applies given function to each item in hash table
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *item = t->arr[i];
        while (item != NULL) {
            f(&(item->pair));
            item = item->next;
        }
    }
}