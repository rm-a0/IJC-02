// htab_erase.c
// Solution IJC-DU2, Task B, 22.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdlib.h>
#include "htab.h"
#include "htab_structs.h"

// Function that erases given item from hash table
bool htab_erase(htab_t *t, htab_key_t key) {
    // Calculate hash value for the key
    size_t index = htab_hash_function(key) % t->arr_size;

    htab_item_t *prev = NULL;
    htab_item_t *current = t->arr[index];
    while (current != NULL) {
        if (strcmp(current->pair.key, key) == 0) {
            // Remove item
            if (prev == NULL) {
                t->arr[index] = current->next;
            } 
            else {
                prev->next = current->next;
            }
            // Free memory
            free(current);
            t->size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;   // Removal failed
}