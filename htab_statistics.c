// htab_statistics.c
// Solution IJC-DU2, Task B, 23.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include "htab.h"
#include "htab_structs.h"

// Function that prints hash table statistics to stderr
void htab_statistics(const htab_t *t) {
    fprintf(stderr, "Hash table statistics \n");
    fprintf(stderr, "Bucket count: %zu\n", t->arr_size);
    fprintf(stderr, "Items in total: %zu\n", t->size);

    double avg_items = (double)t->size / t->arr_size;
    fprintf(stderr, "Average items in bucket: %.2f\n", avg_items);

    for (size_t i = 0; i < t->arr_size; ++i) {
        size_t bucket_length = 0;
        htab_item_t *item = t->arr[i];

        while (item != NULL) {
            bucket_length++;
            item = item->next;
        }
        fprintf(stderr, "Bucket %zu: %zu\n", i, bucket_length);
    }
}