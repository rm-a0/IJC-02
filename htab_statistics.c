// htab_statistics.c
// Solution IJC-DU2, Task B, 23.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <stdint.h>
#include "htab.h"
#include "htab_structs.h"

// Function that prints hash table statistics to stderr
void htab_statistics(const htab_t *t) {
    size_t min_items = SIZE_MAX;
    size_t max_items = 0;

    for (size_t i = 0; i < t->arr_size; ++i) {
        size_t bucket_length = 0;
        htab_item_t *item = t->arr[i];

        while (item != NULL) {
            bucket_length++;
            item = item->next;
        }

        if (bucket_length > max_items) {
            max_items = bucket_length;
        }
        if (bucket_length < min_items) {
            min_items = bucket_length;
        }
    }

    if (t->size > 0) {
        double avg_items = (double)t->size / t->arr_size;
        fprintf(stderr, "Minimum items per bucket: %zu\n", min_items);
        fprintf(stderr, "Maximum items per bucket: %zu\n", max_items);
        fprintf(stderr, "Average items per bucket: %.2f\n", avg_items);
    }
    else {
        fprintf(stderr,"Hash table is empty.\n");
    }
}