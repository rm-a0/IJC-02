// htab_structs.c
// Solution IJC-DU2, Task B, 22.4.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#ifndef HTAB_STRUCTS_H__
#define HTAB_STRUCTS_H__

#include "htab.h" // size_t, htab_pair_t

// Forward declaration to prevent compiling issues
typedef struct htab_item htab_item_t;

// Hash table
struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **arr;
};

// Item in hash table 
typedef struct htab_item {
    htab_pair_t pair;
    htab_item_t *next;
} htab_item_t;

#endif // HTAB_STRUCTS_H__